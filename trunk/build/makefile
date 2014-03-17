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

# LIBS
#BOX2D_LIB = -lBox2D
#SYSTEM_LIB = -lsfml-system
#WINDOW_LIB = -lsfml-window
#GRAPHICS_LIB = -lsfml-graphics
#AUDIO_LIB = -lsfml-audio
#NETWORK_LIB = -lsfml-network
#SFML_LIB =  $(GRAPHICS_LIB) $(WINDOW_LIB) $(SYSTEM_LIB)
##$(SYSTEM_LIB) $(WINDOW_LIB) $(GRAPHICS_LIB) $(AUDIO_LIB) $(NETWORK_LIB)
#LDFLAGS = -L$(SFML_DIR)/lib $(BOX2D_LIB) $(SFML_LIB)
##LDFLAGS = -L$(BOX2D_DIR)/lib $(BOX2D_LIB)

#INCLUDE
INC = -I$(SFML_DIR)/include -I$(BOX2D_INCLUDE_DIR)
#INC = -I$(BOX2D_DIR)/include

# SRC files
SRC_DIR = ../src
SRC = $(wildcard $(SRC_DIR)/*.cpp)

# OBJ files
OBJ_DIR = ../obj
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# BIN files
BIN_DIR = ../bin

#ALL: ../obj/main.o
#	$(CC) $(LDFLAGS) -o $(BIN_DIR)/$(EXE) $^
#	@ echo 'Executable' $(EXE) 'successfully compiled !'

ALL: $(OBJ)
	$(CC) -o $(BIN_DIR)/$(EXE) $^ $(LDFLAGS)
	@echo 'Executable' $(EXE) 'successfully compiled !'

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@ $(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@ echo 'Source file' $< 'compiled'

clean:
	$(RM) $(OBJ_DIR)/*.o
	@ echo 'Object files removed'

mrproper: clean
	@ $(RM) $(BIN_DIR)/$(EXE)
	@ echo 'Executable file removed'

test:
	@echo $(OS)
