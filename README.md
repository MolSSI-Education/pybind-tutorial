Examples of using Pybind11
==========================

Written for the MolSSI Software Summer School 2017

WARNING: Make sure that you are within the
         Software Summer School (sss) conda environment!

1.) Make a subdirectory for building (common practice) and change into it

    mkdir build
    cd build


2.) Run cmake. This will run some checks of your build environment
    and then create the Makefile for you

    cmake ../


3.) Actually build the python modules

    make


4.) Test the python module

    Simple test:

        python3 -c "import basic_mod; print(basic_mod.factorial(10))"

    This should print 3628800, which according to google, is correct.

    or use the test script:

        PYTHONPATH=./ python3 ../test.py

