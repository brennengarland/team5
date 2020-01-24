# Make the static linking library liblua.a
liblua: lapi.o lbaselib.o lcode.o lctype.o ldebug.o ldump.o  lgc.o    liolib.o  lmathlib.o  loadlib.o  lopcodes.o  lparser.o  lstring.o  ltable.o   ltm.o  luac.o lutf8lib.o lzio.o lauxlib.o lbitlib.o lcorolib.o ldblib.o ldo.o lfunc.o linit.o llex.o lmem.o lobject.o loslib.o lstate.o lstrlib.o ltablib.o lua.o lundump.o lvm.o
	ar rcs liblua.a lapi.o lbaselib.o lcode.o lctype.o ldebug.o ldump.o lgc.o liolib.o lmathlib.o loadlib.o lopcodes.o lparser.o lstring.o ltable.o ltm.o luac.o lutf8lib.o lzio.o lauxlib.o lbitlib.o lcorolib.o ldblib.o ldo.o lfunc.o linit.o llex.o lmem.o lobject.o loslib.o lstate.o lstrlib.o ltablib.o lua.o lundump.o lvm.o
	ranlib liblua.a

# Make the lua executable
lua: lua.o liblua
	gcc -o lua lua.o liblua.a -lm

# Make the lua compiler
luac: luac.o liblua
	gcc -o luac luac.o liblua.a -lm

# Clean the results of our makefile

all: liblua lua luac



clean:
	rm *.o *.a

#.o files
liblua.o: l*.c l*.h
	gcc -c l*.c l*.h

lua.o: lua.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h
	gcc -c lua.c lprefix.h lua.h luaconf.h lauxlib.h lualib.h

luac.o: luac.c lprefix.h lua.h luaconf.h lauxlib.h lobject.h llimits.h lstate.h ltm.h lzio.h lmem.h lundump.h ldebug.h lopcodes.h
	gcc -c luac.c lprefix.h lua.h luaconf.h lauxlib.h lobject.h llimits.h lstate.h ltm.h lzio.h lmem.h lundump.h ldebug.h lopcodes.h
