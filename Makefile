TARGET		= hdb

SRC_DIR		= src
OBJ_DIR		= obj
OUT_DIR		= dist

SOURCES		= $(wildcard $(SRC_DIR)/*.cpp)
HEADERS		= $(wildcard $(SRC_DIR)/*.h)
_OBJS		= $(SOURCES:$(SRC_DIR)/%.cpp=%.o)
OBJS		= $(patsubst %,$(OUT_DIR)/%,$(_OBJS))
LIBS		= -lncurses

WARNINGS	= -Wall
CXXFLAGS	+= $(WARNINGS)


# if `clang' is specified, use it
ifdef ($(CLANG))
	CXX		= clang++
else
	# set to `g++' if nothing set
	ifndef ($(CXX))
		CXX		= g++
	endif
endif
# use ccache if specified
ifdef ($(CCACHE))
	CXX 	= CCACHE_CPP2=1 ccache $(CROSS)$(CXX)
	LD		= CCACHE_CPP2=1 ccache $(CROSS)$(CXX)
endif
# debugging flags
ifdef ($(DEBUG))
	# if specified, produce extra info
	ifeq ($(DEBUG), 2)
		CXXFLAGS	+= -ggdb
	else
		# extra info if g++
		ifeq ($(CXX), g++)
			CXXFLAGS	+= -ggdb
		else
			CXXFLAGS	+= -g
		endif
	endif
endif

.PHONY: clean
$(TARGET): $(OUT_DIR) $(OBJ_DIR) $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(DEFINES) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OUT_DIR) $(OBJ_DIR)
