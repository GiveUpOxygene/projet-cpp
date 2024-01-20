#! /bin/bash

make clean
rm cmake_install.cmake
rm CMakeCache.txt
cmake .
make