make clean
rm -rf *lk *.cdb *.lst *.rel *asm *.lst *.map *.sym *.rst CMakeCache.txt CMakeFiles Makefile
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/sdcc-generic.cmake .
make
