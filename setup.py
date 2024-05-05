from setuptools import setup, Extension

# Define the extension module
cpp_extension = Extension(
    'ArrayList',              
    sources=['src/ArrayListModule.cpp', "src/ArrayList.cpp"],
    include_dirs=["src"],             
    libraries=[],                
    library_dirs=[],             
    extra_compile_args=["-std=c++17"],       
    extra_link_args=['-lstdc++'],
    language='c++',              
)

# Setup function
setup(
    name='ArrayList',
    version='1.0',
    description='A simple c++ array list extension for python',
    ext_modules=[cpp_extension],
)
