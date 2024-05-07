# CType tic-tac-toe

An exploration of writing C extensions for Python using the [Python/C API](https://docs.python.org/3/c-api/index.html)

# Getting Started

1. Make sure you have `cpython` and not `pypy`.
2. Install `GCC` or `clang`.
3. Install python dependenies using your favorite dependency manager (I like poetry).
   ```
   $poetry install
   ```
4. Build the cextension with
   ```
   $./build_extension.sh
   ```
5. Ball

   ```
   $ python tic_tac_toe/main.py
   ```

# Motivation

I wanted to better understand the C/Python ecosystem and stumbled across an old project of mine which implemented a vector using [PyBind11](https://github.com/pybind/pybind11). I decided to implement a C Extension which provides a datatype that can serve as a drop in replacement for the built-in Python list. This datatype uses `PyObject` pointers so is probably slower than the built-in Python list, but gives a good overview of how to implement operators, methods, and attributes on a c-implemented datatype.

Implementing C extenion datatypes gives maximum control over data, but forces manual reference counting which is tedious and easy to break. I can't imagine ever needing this level of control over the Python/C interface so if I were to actaually need to implement a performant datatype with a Python interface I would probably choose PyBind11 which makes it dramatically easier to pass memory between Python and C.

## Resources

[Extending the Python Interpreter](https://docs.python.org/3/extending/index.html#extending-index)
