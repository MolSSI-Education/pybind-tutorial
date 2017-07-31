import basic_mod as bm
import numpy_mod as nm
import numpy as np


a = np.random.rand(25)
b = np.random.rand(25)

a_list = list(a)
b_list = list(b)

a_mat = a.reshape(5,5)
b_mat = b.reshape(5,5)

print("Basic functions")
bm.print_arg(10)
bm.print_arg(11.123)
bm.print_arg("This is a string")
bm.print_arg([1, 2, 3, 4, 5])
print()

print("Factorials/Binomial Coefficient")
print(bm.factorial(10))
print(bm.factorial(0))
print(bm.double_factorial(20))
print(bm.double_factorial(0))
print(bm.double_factorial(-1))
print(bm.binomial_coefficient(10, 2))
print()

print("Dot product")
print(np.dot(a, b))
print(nm.dot_product(a, b))
print(bm.dot_product(a_list, b_list))
print(np.dot(a.T, b.T))
print(nm.dot_product(a.T, b.T))
print(bm.dot_product(a_list, b_list))
print()

print("Matrix Multiplication")
c1 = np.matmul(a_mat, b_mat)
c2 = nm.dgemm(1.0, a_mat, b_mat)
print(c1)
print(c2)
print(np.allclose(c1, c2))
print()

print("Matrix Multiplication w/ strides (transposes)")
c1 = np.matmul(a_mat.T, b_mat.T)
c2 = nm.dgemm(1.0, a_mat.T, b_mat.T)
print(c1)
print(c2)
print(np.allclose(c1, c2))
print()

