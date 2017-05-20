# vimchroma

A Razer Chroma plugin for gVim. See the [demonstration](https://vimeo.com/175987019).

## Building

Build using build.bat
This calls setup.py and also adds the python manifest file to the pyd.
To install, copy the chroma.pyd file to site-packages.

You must build using Visual Studio 2008, this is the only way Python 3.2 will be able to import the module (and gVim was built with Python 3.2)
Do a :version to check for python3/dyn install

chroma.manifest was generated with the mt tool by extracting python.exe's manifest file

Install at C:\Python32\Lib\site-packages
