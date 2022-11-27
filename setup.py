from glob import glob
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "arrayList",
        glob("src/*.cpp")
    )
]

setup(
    name="arrayList",
    python_requires=">=3.7",
    cmdclass={"build_ext": build_ext},
    ext_modules=ext_modules
)

