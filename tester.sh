cd src/Tests
make clean
rm cmake_install.cmake CMakeCache.txt Makefile
cmake . 
make 
./test.out
cd ../..