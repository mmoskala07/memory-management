RMDIR build /S /Q
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
MinGW32-make

List.exe

cd ..