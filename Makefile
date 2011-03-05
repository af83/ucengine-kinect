EXE_NAME  = bin/UCE-Gestures
SRC_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(foreach src,$(SRC_FILES),obj/$(addsuffix .o, $(notdir $(basename $(src)))))

DEFINES   = USE_GLUT XN_SSE
USED_LIBS = glut OpenNI XnVNite stdc++
INC_DIRS  = . /usr/include/nite /usr/include/ni

INC_DIRS_OPTION  = $(foreach dir,$(INC_DIRS),-I$(dir))
LIB_DIRS_OPTION  = $(foreach dir,$(LIB_DIRS),-L$(dir))
USED_LIBS_OPTION = $(foreach lib,$(USED_LIBS),-l$(lib))
DEFINES_OPTION   = $(foreach def,$(DEFINES),-D$(def))

# Debug
# CFLAGS += -g
CFLAGS += -O3 -fno-tree-pre -fno-strict-aliasing -DNDEBUG
# CFLAGS += -msse2
# CFLAGS += -msse3 -mssse3
CFLAGS  += $(INC_DIRS_OPTION) $(DEFINES_OPTION)
LDFLAGS += $(LIB_DIRS_OPTION) $(USED_LIBS_OPTION)

.PHONY: all clean

all: $(EXE_NAME)

$(EXE_NAME): $(OBJ_FILES)
	$(CC) -o $(EXE_NAME) $(OBJ_FILES) $(LDFLAGS)

obj/%.o: src/%.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	$(RM) $(EXE_NAME)
