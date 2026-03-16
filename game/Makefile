OS := $(shell uname -s)

ifeq ($(OS),Linux)
    CXX = g++
    CC = gcc
    LIBS = 
    ARGS = -lGL -lglfw -lGLEW -I"../libs/include" -I"../engine/src" -L"../bin" -lConstantEngine -Wl,-rpath,'$$ORIGIN'
    RC =
    RCFLAGS =
endif

ifeq ($(OS),Windows_NT)
    CXX = g++
    CC = gcc
    RC = windres
    RCFLAGS = 
    LIBS = 
    ARGS = -L"../libs/lib" -I"../libs/include" -lglew32s -limgui -lopengl32 -lgdi32 -ldwmapi -lvulkan-1 -luser32 -lcomdlg32 -limm32 -I"../engine/src" -L"../engine/bin" -lConstantEngine -DGLEW_STATIC -DUNICODE -D_UNICODE
endif

SRC_DIR := src
OBJ_DIR := build
BIN := ../bin/game

SOURCES_CPP := $(shell find $(SRC_DIR) -type f -name "*.cpp")
SOURCES_C := $(shell find $(SRC_DIR) -type f -name "*.c")
SOURCES_RC := resource.rc
SOURCES := $(SOURCES_CPP) $(SOURCES_C)

OBJECTS_CPP := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SOURCES_CPP:.cpp=.o))
OBJECTS_C := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SOURCES_C:.c=.o))
OBJECTS_RC := $(OBJ_DIR)/$(SOURCES_RC:.rc=.o)
OBJECTS := $(OBJECTS_CPP) $(OBJECTS_C)

$(shell mkdir -p $(OBJ_DIR))

$(BIN): $(OBJECTS)
	$(CXX) $^ -o $@ $(ARGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(ARGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(ARGS) -c $< -o $@

ifeq ($(OS),Windows_NT)
$(OBJ_DIR)/%.o: %.rc
	@mkdir -p $(dir $@)
	$(RC) $(RCFLAGS) -i $< -o $@
endif

clean:
	rm -rf $(OBJ_DIR) $(BIN)