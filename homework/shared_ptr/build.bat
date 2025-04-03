RMDIR build /S /Q
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
MinGW32-make

shared_ptr_tests.exe

cd ..

