from setuptools import setup, Extension

# Define the extension module
cpp_extension = Extension(
    'myCoolCArray',              
    sources=['src/myCoolCArrayModule.cpp'],
    include_dirs=["src"],             
    extra_compile_args=["-std=c++17"],       
    language='c++',              
)

# Setup function
setup(
    name='myCoolCArray',
    version='1.0',
    description='A simple c++ array list extension for python',
    ext_modules=[cpp_extension],
)
