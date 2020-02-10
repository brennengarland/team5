# csce693-2020
Repo for student to clone and use for class homework

### deps folder contains Lua 5.3, sol 2 v3.0.3, and SDL2
The src folder contains original source code, the include and lib folders contain header and compiled static versions of these libraries

### Compiling SDL2:
configure --prefix=[install location] --enable-static

make

make install

### Compiling Lua:
make linux
