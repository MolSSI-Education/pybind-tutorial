#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <iostream>

namespace py = pybind11;

double dot_product(py::buffer a, py::buffer b)
{
    py::buffer_info a_info = a.request(); 
    py::buffer_info b_info = b.request(); 

    //std::cout << a_info.format << " " << b_info.format << std::endl;
    //std::cout << a_info.ndim << " " << b_info.ndim << std::endl;

    // Check if both arguments are vectors of the same length
    if(a_info.ndim != 1)
        throw std::runtime_error("a is not a vector!");
    if(b_info.ndim != 1)
        throw std::runtime_error("b is not a vector!");
    if(a_info.shape[0] != b_info.shape[0])
        throw std::runtime_error("a and b are vectors of different lengths");


    double dot_prod = 0.0;

    size_t len = a_info.shape[0];

    const double * a_data = static_cast<double *>(a_info.ptr);
    const double * b_data = static_cast<double *>(b_info.ptr);

    for(size_t i = 0; i < len; i++)
        dot_prod += a_data[i] * b_data[i];

    return dot_prod;
}


py::array dgemm(double alpha, py::buffer a, py::buffer b)
{
    py::buffer_info a_info = a.request(); 
    py::buffer_info b_info = b.request(); 

    // Check if both arguments are matrices, and that the number
    // of columns of 'a' is the same as the number of rows of 'b'
    if(a_info.ndim != 2)
        throw std::runtime_error("a is not a matrix!");
    if(b_info.ndim != 2)
        throw std::runtime_error("b is not a matrix!");
    if(a_info.shape[1] != b_info.shape[0])
        throw std::runtime_error("incompatible matrix dimensions");

    size_t c_nrows = a_info.shape[0];
    size_t c_ncols = b_info.shape[1];
    size_t n_k = a_info.shape[1]; 
    double * c_data = new double[c_nrows * c_ncols];

    const double * a_data = static_cast<double *>(a_info.ptr);
    const double * b_data = static_cast<double *>(b_info.ptr);

    // perform the gemm
    for(size_t i = 0; i < c_nrows; i++)
    for(size_t j = 0; j < c_ncols; j++)
    {
        double value = 0.0;
        for(size_t k = 0; k < n_k; k++)
            value += a_data[i*n_k + k] * b_data[k*c_ncols + j];
 
        c_data[i*c_ncols+j] = value * alpha;
    }

    // create a new buffer
    py::buffer_info c_info = {
        c_data,           // pointer to the data we just allocated
        sizeof(double),   // size of a single element
        py::format_descriptor<double>::format(), // type of data held
        2,                // number of dimensions (2 = matrix)
        { c_nrows, c_ncols },  // shape of the matrix
        { sizeof(double) * c_ncols,    // Stride between two rows (in bytes)
          sizeof(double) }             // Stride between two cols (in bytes)
    };

    return py::array(c_info); 
}


PYBIND11_PLUGIN(numpy_mod)
{
    py::module m("numpy_mod", "Ben's basic numpy module");

    m.def("dot_product", dot_product);
    m.def("dgemm", dgemm);

    return m.ptr();
}

