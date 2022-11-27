from glob import glob
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "ArrayList",
        glob("src/*.cpp")
    )
]

setup(
    name="ArrayList",
    python_requires=">=3.7",
    cmdclass={"build_ext": build_ext},
    ext_modules=ext_modules
)

