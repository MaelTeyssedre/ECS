mkdir build
cd build
cmake ..
cmake --build . --config Release
mv libECS.a ..
cd ..