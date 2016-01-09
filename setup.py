from distutils.core import setup
from distutils.extension import Extension

mymodule = Extension('chroma', ['chroma.cpp'])

setup (name = 'chroma',
       description = 'Chroma BlackWidow Python API',
       ext_modules = [mymodule],
       )
