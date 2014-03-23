export CC = g++
export CFLAGS = -W -ansi -g
export LDFLAGS
EXE = test
export RM=

# Getting OS
ifeq ($(OS),Windows_NT)
        LDFLAGS += -mwindows
        SFML_DIR = D:/lib/SFML
        BOX2D_DIR = D:/lib/Box2D
        BOX2D_LIB_DIR = $(BOX2D_DIR)/Box2D
        BOX2D_INCLUDE_DIR = $(BOX2D_DIR)
		RM = del /s
		test += .exe
		CREATE_DIR = echo 'Creating dir'
else
        LDFLAGS +=
		SFML_DIR = /usr/local
		BOX2D_DIR = /usr/local
		BOX2D_LIB_DIR = $(BOX2D_DIR)/lib
        BOX2D_INCLUDE_DIR = $(BOX2D_DIR)/include
		RM = rm -R
		CREATE_DIR = mkdir -p
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
export INC = -I$(SFML_DIR)/include -I$(BOX2D_INCLUDE_DIR)

# SRC files
export SRC_DIR = ../src
SRC = $(wildcard $(SRC_DIR)/*.cpp) 
# TODO test in Windows 
SRC = $(shell find $(SRC_DIR) -type f -name '*.cpp')

# OBJ files
export OBJ_DIR = ../obj
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# BIN files
BIN_DIR = ../bin

# Subdirectories
PHYSICS_SUBDIR = Physics
OBJ += $(wildcard $(OBJ_DIR)/$(PHYSICS_SUBDIR)/*.o)

GRAPHICS_SUBDIR = Graphics
OBJ += $(wildcard $(OBJ_DIR)/$(GRAPHICS_SUBDIR)/*.o)

GAMEOBJECTS_SUBDIR = GameObjects
OBJ += $(wildcard $(OBJ_DIR)/$(GAMEOBJECTS_SUBDIR)/*.o)

SUBDIRS = $(PHYSICS_SUBDIR) $(GRAPHICS_SUBDIR) $(GAMEOBJECTS_SUBDIR)

#
ALL: 
	@$(MAKE) objects
	@$(MAKE) link

# At this step, $(OBJ) does not contain subdirectories files
objects: $(OBJ) $(SUBDIRS)

$(SUBDIRS):
	@#echo 'Entering' $@ '...'
	@#$(MAKE) -C $@ DIR=$@
.PHONY: subdirs $(SUBDIRS)

link: $(OBJ)
	$(CC) $(LDFLAGS) -o $(BIN_DIR)/$(EXE) $^
	@echo 'Executable' $(EXE) 'successfully compiled !'
	
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	@ $(CREATE_DIR) $(@D)
	$(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@ echo 'Source file' $< 'compiled with header'

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@ $(CREATE_DIR) $(@D)
	$(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@ echo 'Source file' $< 'compiled'

clean:
	@ $(RM) $(OBJ_DIR)/*
	@# $(MAKE) clean -C $(PHYSICS_SUBDIR) DIR=$(PHYSICS_SUBDIR)
	@# $(MAKE) clean -C $(GRAPHICS_SUBDIR) DIR=$(GRAPHICS_SUBDIR)
	@# $(MAKE) clean -C $(GAMEOBJECTS_SUBDIR) DIR=$(GAMEOBJECTS_SUBDIR)
	@ echo 'Object files removed'

mrproper: clean
	@ $(RM) $(BIN_DIR)/$(EXE)
	@ echo 'Executable file removed'

