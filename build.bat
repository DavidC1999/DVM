if not exist out mkdir out
cd out
@REM cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
mingw32-make
cd ..