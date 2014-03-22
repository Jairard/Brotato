CC = g++
CFLAGS = -W -ansi -g
EXE = test

# Getting OS
ifeq ($(OS),Windows_NT)
        LDFLAGS += -mwindows
        SFML_DIR = D:/lib/SFML
        BOX2D_DIR = D:/lib/Box2D
        BOX2D_LIB_DIR = $(BOX2D_DIR)/Box2D
        BOX2D_INCLUDE_DIR = $(BOX2D_DIR)
		RM = del /s
		test += .exe
else
        LDFLAGS +=
		SFML_DIR = /usr/local
		BOX2D_DIR = /usr/local
		BOX2D_LIB_DIR = $(BOX2D_DIR)/lib
        BOX2D_INCLUDE_DIR = $(BOX2D_DIR)/include
		RM = rm -rf
#    UNAME_S := $(shell uname -s)
#    ifeq ($(UNAME_S),Linux)
#    endif
#    ifeq ($(UNAME_S),Darwin)
#    endif
endif

# SFML
SFML_STATIC =
SFML_DEBUG = 

LSFML_SYSTEM = -lsfml-system
LSFML_WINDOW = -lsfml-window
LSFML_GRAPHICS = -lsfml-graphics
LSFML_AUDIO = -lsfml-audio
LSFML_NETWORK = -lsfml-network
LSFML_ALL =  $(LSFML_GRAPHICS) $(LSFML_WINDOW) $(LSFML_SYSTEM)
LSFML = -L$(SFML_DIR)/lib $(LSFML_ALL:-l%=-l%$(SFML_STATIC)$(SFML_DEBUG))
LDFLAGS += $(LSFML)

# BOX2D
LBOX2D = -L$(BOX2D_LIB_DIR) -lBox2D
LDFLAGS += $(LBOX2D)

#INCLUDE
INC = -I$(SFML_DIR)/include -I$(BOX2D_INCLUDE_DIR)

# SRC files
SRC_DIR = ../src
PHYSICS_DIR = Physics
GRAPHICS_DIR = Graphics
GAME_OBJECTS_DIR = GameObjects

PHYSICS_SRC = $(wildcard $(SRC_DIR)/$(PHYSICS_DIR)/*.cpp)
GRAPHICS_SRC = $(wildcard $(SRC_DIR)/$(GRAPHICS_DIR)/*.cpp)
GAME_OBJECTS_SRC = $(wildcard $(SRC_DIR)/$(GAME_OBJECTS_DIR)/*.cpp)
SRC = $(wildcard $(SRC_DIR)/*.cpp) 
SRC += $(PHYSICS_SRC)
SRC += $(GRAPHICS_SRC)
SRC += $(GAME_OBJECTS_SRC)

# OBJ files
OBJ_DIR = ../obj
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# BIN files
BIN_DIR = ../bin

ALL: $(OBJ)
	$(CC) -o $(BIN_DIR)/$(EXE) $^ $(LDFLAGS)
	@echo 'Executable' $(EXE) 'successfully compiled !'
	
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@ echo 'Source file' $< 'compiled with header'

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@ echo 'Source file' $< 'compiled'

clean:
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(OBJ_DIR)/$(PHYSICS_DIR)/*.o
	@ echo 'Object files removed'

mrproper: clean
	@ $(RM) $(BIN_DIR)/$(EXE)
	@ echo 'Executable file removed'

test:
	@echo $(OS)
