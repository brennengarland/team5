all: lua luac liblua

#lua

lua: lua.o lauxlib.o
	g++ lua.o lauxlib.o -o lua

lua.o: lua.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h
	g++ -c lua.c


lauxlib.o: lauxlib.c lprefix.h lua.h luaconf.h lauxlib.h
	g++ -c lauxlib.c

