# vimchroma

A Razer Chroma plugin for gVim. See the [demonstration](https://vimeo.com/175987019).

## Building

Build using `build.bat`. This calls `setup.py` and also adds the python manifest file to the pyd.

## Installation
To install, copy the chroma.pyd file to Python's site-packages so it will be recognized by Python.

Add the following to your .vimrc:
```
:py3 import chroma
:autocmd InsertEnter * :py3 chroma.insertmode()
:autocmd InsertLeave * :py3 chroma.normalmode()
:py3 chroma.normalmode()
```

## Additional Notes
You must build using Visual Studio 2008, this is the only way Python 3.2 will be able to import the module (and gVim was built with Python 3.2)

Do a :version check in gVim to check for python3/dyn install. You **must** have python3.

chroma.manifest was generated with the mt tool by extracting python.exe's manifest file

