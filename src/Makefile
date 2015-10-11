TARGET		= hsh

#CC			= colorgcc

DEFINES		= 
WARNINGS	= -Wall -Werror
CFLAGS		+= -std=c99 -ggdb
LIBS		=

SOURCES		= $(wildcard *.c)
OBJS		= $(SOURCES:.c=.o)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(DEFINES) $(WARNINGS) $(CFLAGS) $^ $(LIBS)

%.o: %.c
	$(CC) -c $(DEFINES) $(WARNINGS) $(CFLAGS) $< $(LIBS)

.PHONY: clean
clean:
	rm -f *.o $(TARGET)
