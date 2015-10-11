TARGET		= ui.a

DEFINES		= 
WARNINGS	= -Wall
CFLAGS		+= -std=c99 -g
LIBS		= -lncurses

SOURCES		= $(wildcard *.c)
OBJS		= $(SOURCES:.c=.o)

$(TARGET): $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) -c $(DEFINES) $(WARNINGS) $(CFLAGS) $< $(LIBS)

.PHONY: clean
clean:
	rm -f *.o $(TARGET)
