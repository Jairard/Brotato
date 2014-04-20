export CC = g++
export CFLAGS = -W -ansi -g
export LDFLAGS
TARGET_NAME = Brotato
TARGET_EXTENSION = 
LIB_EXTENSION =
RM = rm
CREATE_DIR = mkdir -p

OS_DIR = OSX

TRUNK_DIR = ..
LIB_DIR = $(TRUNK_DIR)/lib
INCLUDE_DIR = $(TRUNK_DIR)/include

SFML_LIB_DIR = $(LIB_DIR)/$(OS_DIR)/SFML
BOX2D_LIB_DIR = $(LIB_DIR)/$(OS_DIR)/Box2D
OS_LDFLAGS = 
LDFLAGS = $(OS_LDFLAGS)

# Getting OS
#ifeq ($(OS),Windows_NT)
#		LDFLAGS += -mwindows
#		SFML_DIR = D:/lib/SFML
#		BOX2D_DIR = D:/lib/Box2D
#		BOX2D_LIB_DIR = $(BOX2D_DIR)/Box2D
#		BOX2D_INCLUDE_DIR = $(BOX2D_DIR)
#		RM = del /s
#		test += .exe
#		CREATE_DIR = echo 'Creating dir'
#else
#		LDFLAGS +=
#		SFML_LIB_DIR = $(LIB_DIR)/OSX/SFML/clang
#		BOX2D_LIB_DIR = $(LIB_DIR)/OSX/Box2D
#		RM = rm -R
#		CREATE_DIR = mkdir -p
#endif

TARGET = $(TARGET_NAME)$(TARGET_EXTENSION)

# SFML
SFML_STATIC =
SFML_DEBUG = 

LSFML_SYSTEM = $(SFML_LIB_DIR)/libsfml-system.$(LIB_EXTENSION)
LSFML_WINDOW = $(SFML_LIB_DIR)/libsfml-window.$(LIB_EXTENSION)
LSFML_GRAPHICS = $(SFML_LIB_DIR)/libsfml-graphics.$(LIB_EXTENSION)
LSFML_AUDIO = $(SFML_LIB_DIR)/libsfml-audio.$(LIB_EXTENSION)
LSFML_NETWORK = $(SFML_LIB_DIR)/libsfml-network.$(LIB_EXTENSION)
LSFML_ALL =  $(LSFML_GRAPHICS) $(LSFML_WINDOW) $(LSFML_SYSTEM)
LSFML = $(LSFML_ALL:-l%=-l%$(SFML_STATIC)$(SFML_DEBUG))
LDFLAGS += $(LSFML)

# BOX2D
LBOX2D = -L$(BOX2D_LIB_DIR) -lBox2D
LDFLAGS += $(LBOX2D)

#INCLUDE
export INC = -I$(INCLUDE_DIR)

# SRC files
export SRC_DIR = ../src
SRC = $(wildcard $(SRC_DIR)/*.cpp) 

# OBJ files
export OBJ_DIR = ../obj
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

# OBJ files
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Delete targets
DELETE_TARGETS = $(OBJ:%=delete_%)
	
all: $(OBJ)
	$(CC) -o $(BIN_DIR)/$(TARGET) $^ $(LDFLAGS) 
	@echo 'Target' $(TARGET) 'successfully compiled !'

link: $(OBJ)
	$(CC) $(LDFLAGS) -o $(BIN_DIR)/$(TARGET) $^
	@echo 'Target' $(TARGET) 'successfully compiled !'
	
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	@ $(CREATE_DIR) $(@D)
	$(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@ echo 'Source file' $< 'compiled with header'

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@ $(CREATE_DIR) $(@D)
	$(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@ echo 'Source file' $< 'compiled'

delete_$(OBJ_DIR)/%:
	@if [ -e $(@:delete_%=%) ]; \
		then $(RM) $(@:delete_%=%); \
		echo $(@:delete_%=%) "deleted"; \
	fi

clean2: $(DELETE_TARGETS)
	@ echo 'Object files removed'

clean: 
	@ $(RM) $(OBJ_DIR)/*.o
	@ $(RM) $(OBJ_DIR)/$(PHYSICS_SUBDIR)/*.o
	@ $(RM) $(OBJ_DIR)/$(GRAPHICS_SUBDIR)/*.o
	@ $(RM) $(OBJ_DIR)/$(GAMEOBJECTS_SUBDIR)/*.o
	@ $(RM) $(OBJ_DIR)/$(WINDOWS_SUBDIR)/*.o
	@ $(RM) $(OBJ_DIR)/$(CORE_SUBDIR)/*.o
	@ echo 'Object files removed'

mrproper: clean
	@ $(RM) $(BIN_DIR)/$(TARGET)
	@ echo 'TARGETcutable file removed'

