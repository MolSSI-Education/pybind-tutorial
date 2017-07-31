cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(molssi_sss_pybind)

# This must be run using a conda environment
if("$ENV{CONDA_PREFIX}" STREQUAL "")
    message(FATAL_ERROR "This must be run within the MolSSI SSS conda prefix. "
                        "Delete the build directory and try again")
endif()

# CMake will sometimes find the conda python version
# (rather the the python inside the sss environment)
set(PYTHON_EXECUTABLE $ENV{CONDA_PREFIX}/bin/python3)

# Find the pybind11 in the conda path
set(PYBIND11_CPP_STANDARD -std=c++11)
find_package(pybind11 CONFIG REQUIRED
             PATHS $ENV{CONDA_PREFIX}
             NO_DEFAULT_PATH)

message(STATUS "Found pybind11: ${pybind11_CONFIG}")

# Creates a python module named "basic_mod"
pybind11_add_module(basic_mod MODULE basic_mod.cpp)

# Creates a python module named "numpy_mod"
pybind11_add_module(numpy_mod MODULE numpy_mod.cpp)
