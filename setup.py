from setuptools import setup, Extension

# Define the extension module
cpp_extension = Extension(
    'myVec',              
    sources=['src/module/myVecModule.cpp', 'src/myVec.cpp'],
    include_dirs=["src"],             
    extra_compile_args=["-std=c++17"],       
    language='c++',              
)

# Setup function
setup(
    name='myVec',
    version='1.0',
    description='A simple c++ array list extension for python',
    ext_modules=[cpp_extension],
)
