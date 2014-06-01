CC = g++
CFLAGS = -W -ansi -g
LDFLAGS =
TARGET_NAME = Brotato
TARGET_EXTENSION = 
SFML_LIB_EXTENSION =
BOX2D_LIB_EXTENSION =
RM =
CREATE_DIR =
ECHO =

OS_LDFLAGS = 
OS_DIR =

TRUNK_DIR = ..
LIB_DIR = $(TRUNK_DIR)/lib
INCLUDE_DIR = $(TRUNK_DIR)/include

SFML_LIB_DIR = $(LIB_DIR)/$(OS_DIR)/SFML
BOX2D_LIB_DIR = $(LIB_DIR)/$(OS_DIR)/Box2D
LDFLAGS = $(OS_LDFLAGS)

TARGET = $(TARGET_NAME)$(TARGET_EXTENSION)

# SFML
SFML_STATIC =
SFML_DEBUG = 

LSFML_SYSTEM = $(SFML_LIB_DIR)/libsfml-system.$(SFML_LIB_EXTENSION)
LSFML_WINDOW = $(SFML_LIB_DIR)/libsfml-window.$(SFML_LIB_EXTENSION)
LSFML_GRAPHICS = $(SFML_LIB_DIR)/libsfml-graphics.$(SFML_LIB_EXTENSION)
LSFML_AUDIO = $(SFML_LIB_DIR)/libsfml-audio.$(SFML_LIB_EXTENSION)
LSFML_NETWORK = $(SFML_LIB_DIR)/libsfml-network.$(SFML_LIB_EXTENSION)
LSFML_ALL =  $(LSFML_GRAPHICS) $(LSFML_WINDOW) $(LSFML_SYSTEM)
LSFML = $(LSFML_ALL:-l%=-l%$(SFML_STATIC)$(SFML_DEBUG))
LDFLAGS += $(LSFML)

# BOX2D
LBOX2D = $(BOX2D_LIB_DIR)/libBox2D.$(BOX2D_LIB_EXTENSION)
LDFLAGS += $(LBOX2D)

#INCLUDE
INC = -I$(INCLUDE_DIR)

# SRC files
SRC_DIR = ../src
SRC = $(wildcard $(SRC_DIR)/*.cpp) 

# OBJ files
OBJ_DIR = ../obj
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# BIN files
BIN_DIR = ../bin

# Subdirectories
PHYSICS_SUBDIR = Physics
SRC += $(wildcard $(SRC_DIR)/$(PHYSICS_SUBDIR)/*.cpp) 

GRAPHICS_SUBDIR = Graphics
SRC += $(wildcard $(SRC_DIR)/$(GRAPHICS_SUBDIR)/*.cpp) 

GAMEOBJECTS_SUBDIR = GameObjects
SRC += $(wildcard $(SRC_DIR)/$(GAMEOBJECTS_SUBDIR)/*.cpp) 

WINDOWS_SUBDIR = Windows
SRC += $(wildcard $(SRC_DIR)/$(WINDOWS_SUBDIR)/*.cpp) 

CORE_SUBDIR = Core
SRC += $(wildcard $(SRC_DIR)/$(CORE_SUBDIR)/*.cpp) 

DEBUG_SUBDIR = Debug
SRC += $(wildcard $(SRC_DIR)/$(DEBUG_SUBDIR)/*.cpp) 

# OBJ files
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Delete targets
DELETE_TARGETS = $(OBJ:%=delete_%)

all: $(OBJ)
	$(CC) -o $(BIN_DIR)/$(TARGET) $^ $(LDFLAGS) 
	@ $(ECHO) 'Target' $(TARGET) 'successfully compiled !'

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	@ $(CREATE_DIR) $(@D)
	@ $(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@ $(ECHO) 'Source file' $< 'compiled with header'

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@ $(CREATE_DIR) $(@D)
	@ $(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@ $(ECHO) 'Source file' $< 'compiled'

delete_$(OBJ_DIR)/%:
	@if [ -e $(@:delete_%=%) ]; \
		then $(RM) $(@:delete_%=%); \
		$(ECHO) $(@:delete_%=%) "deleted"; \
	fi

clean: $(DELETE_TARGETS)
	@ $(ECHO) 'Object files removed'

mrproper: clean
	@ $(RM) $(BIN_DIR)/$(TARGET)
	@ $(ECHO) 'TARGETcutable file removed'

