OS := $(shell uname -s)

DLL := 

ifeq ($(OS),Linux)
    CXX = g++
    CC = gcc
    LIBS = 
    ARGS = -lGL -lglfw -lGLEW -I"../libs/include" -DENGINE_CORE_EXPORTS
    SHARED_ARGS = -fPIC
    DLL_EXT = .so
    DLL_ARGS = -shared

    DLL := ../bin/libConstantEngine$(DLL_EXT)
endif

ifeq ($(OS),Windows_NT)
    CXX = g++
    CC = gcc
    LIBS = 
    ARGS = -L"../libs/lib" -I"../libs/include" -lglew32s -limgui -lopengl32 -lgdi32 -ldwmapi -lvulkan-1 -luser32 -lcomdlg32 -limm32 -DGLEW_STATIC -DENGINE_CORE_EXPORTS -DUNICODE -D_UNICODE
    SHARED_ARGS = 
    LIB_EXT = .lib
    DLL_EXT = .dll

    DLL_ARGS = -shared -Wl,--out-implib,bin/ConstantEngine$(LIB_EXT)
    DLL := ../bin/ConstantEngine$(DLL_EXT)
endif

SRC_DIR := src
OBJ_DIR := build

SOURCES_CPP := $(shell find $(SRC_DIR) -type f -name "*.cpp")
SOURCES_C := $(shell find $(SRC_DIR) -type f -name "*.c")
SOURCES := $(SOURCES_CPP) $(SOURCES_C)

OBJECTS_CPP := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SOURCES_CPP:.cpp=.o))
OBJECTS_C := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SOURCES_C:.c=.o))
OBJECTS := $(OBJECTS_CPP) $(OBJECTS_C)

$(shell mkdir -p $(OBJ_DIR) bin)

$(DLL): $(OBJECTS)
	$(CXX) $(DLL_ARGS) $^ -o $@ $(ARGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(ARGS) $(SHARED_ARGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(ARGS) $(SHARED_ARGS) -c $< -o $@

all: $(DLL)

clean:
	rm -rf $(OBJ_DIR) bin/*$(DLL_EXT) bin/*$(LIB_EXT)

.PHONY: all clean
