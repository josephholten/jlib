# jlib

A simple library collecting useful software I have written in C++.

## Build
It is easiest to build and use this libary via conan (>=v2.0).
You must have a conan profile setup to build with conan.
This can be setup with `conan profile detect --force` but should be reviewed for proper settings.
Then simply call

`conan install . -s build_type=(Debug|Release) --build=missing`

to download and build missing dependencies.
Use

`conan --prefix conan-(debug|release)`

to configure the build system and

`conan --build --prefix conan-(debug|release)`

to build the library and tests.
