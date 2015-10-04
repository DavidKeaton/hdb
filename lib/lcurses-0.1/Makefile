LUA_VER		= 5.1.5
LUA_LIB		= /usr/lib64/lua
LUA_INC		= /usr/include/lua
LUA_BIN		= /usr/bin/lua

LUA_SRC		= curses.lua curses.panel.lua
LUA_TST		= firework.lua interp.lua requirelib.lua test.lua

WARNINGS	= -Wall -Werror -ansi
DEFINES		=
INCLUDES	=
LIBS 		= -lpanel -lcurses -llua

DEBUG 		=

CFLAGS 		= -O3 -s 
CFLAGS	   += $(WARNINGS) $(DEFINES) $(INCLUDES)

OBJS		= lcurses.o lpanel.o
SOURCES		= lcurses.c lpanel.c
TARGET		= lcurses

lcurses.a: lcurses.o lpanel.o dist
	ar rcs dist/$@ *.o
	cp -f $(LUA_SRC) dist/

lcurses.so: lcurses.o lpanel.o dist
	$(CC) -o $@ $(CFLAGS) lcurses.o lpanel.o $(LIBS)

lcurses.o: lcurses.c
	$(CC) -c -o $@ $(CFLAGS) $^ $(LIBS)

lpanel.o: lpanel.c
	$(CC) -c -o $@ $(CFLAGS) $^ $(LIBS)

dist:
	mkdir -p dist/

.PHONY: clean
clean:
	rm -rf *.o *.so *.a dist/
