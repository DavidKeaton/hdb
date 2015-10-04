TARGET		= hdb

SRC_DIR		= src
OBJ_DIR		= obj
OUT_DIR		= dist

SOURCES		= $(wildcard $(SRC_DIR)/*.c)
HEADERS		= $(wildcard $(SRC_DIR)/*.h)
_OBJS		= $(SOURCES:$(SRC_DIR)/%.c=%.o)
OBJS		= $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))
LIBS		= -lncurses

WARNINGS	= -Wall
CFLAGS		+= $(WARNINGS)
DEFINES		=


# if `clang' is specified, use it
ifdef ($(CLANG))
	CC		= clang
else
	# set to `g++' if nothing set
	ifndef ($(CC))
		CC	= gcc
	endif
endif
# use ccache if specified
ifdef ($(CCACHE))
	CC	= CCACHE_CPP2=1 ccache $(CROSS)$(CC)
	LD	= CCACHE_CPP2=1 ccache $(CROSS)$(CC)
endif
# debugging flags
ifdef ($(DEBUG))
	# if specified, produce extra info
	ifeq ($(DEBUG), 2)
		CFLAGS		+= -ggdb
	else
		# extra info if g++
		ifeq ($(CC), gcc)
			CFLAGS	+= -ggdb
		else
			CFLAGS	+= -g
		endif
	endif
endif

.PHONY: clean
$(TARGET): $(OUT_DIR) $(OBJ_DIR) $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEFINES) -c $< -o $@

clean:
	rm -rf $(OUT_DIR) $(OBJ_DIR)
