#! /bin/bash

make clean
rm cmake_install.cmake
rm CMakeCache.txt
rm Makefile
cmake .
make