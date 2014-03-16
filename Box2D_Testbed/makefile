EXE = testbed
CC = g++
CFLAGS = -W
LDFLAGS = 
IFLAGS = 

# Getting OS
ifeq ($(OS),Windows_NT)
	LDFLAGS = -mwindows
	SFML_DIR = C:/Library/SFML-2.1
	BOX2D_DIR = C:/Library/Box2D-2.2.1
	RM = del /s
else
	LDFLAGS = 
	SFML_DIR = /usr/local
	BOX2D_DIR = /usr/local
	RM = rm -rf
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
IFLAGS += -I$(SFML_DIR)/include

# BOX2D
LDFLAGS += -L$(BOX2D_DIR)/lib -lBox2D
IFLAGS += -I$(BOX2D_DIR)/include

# SRC files
TEST_DIR = tests
FRAMEWORK_DIR = framework
SRC = $(wildcard $(FRAMEWORK_DIR)/*.cpp) $(wildcard $(TEST_DIR)/*.cpp)

# OBJ files
OBJ_DIR = obj
OBJ_DIRS = $(OBJ_DIR) $(OBJ_DIR)/$(FRAMEWORK_DIR) $(OBJ_DIR)/$(TEST_DIR)
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o) 

# BIN files
BIN_DIR = bin

# archive
SOURCE_FILES = $(FRAMEWORK_DIR)/*.cpp $(FRAMEWORK_DIR)/*.hpp $(TEST_DIR)/*.cpp $(TEST_DIR)/*.h 
OTHER = makefile arial.ttf
ARCHIVE_FILES = $(SOURCE_FILES) $(OTHER)

ALL: create_dirs $(EXE)

$(EXE): $(OBJ)
	@$(CC) $(IFLAGS) -o $(BIN_DIR)/$(EXE) $^ $(LDFLAGS)
	@echo 'Executable' $(EXE) 'successfully compiled !'

$(OBJ_DIR)/$(FRAMEWORK_DIR)/%.o: $(FRAMEWORK_DIR)/%.cpp
	@$(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@echo 'Source file' $< 'compiled'

$(OBJ_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	@$(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@echo 'Source file' $< 'compiled'

exec: create_dirs $(EXE)
	@echo 'Running' $(EXE)
	@$(BIN_DIR)/$(EXE)

create_dirs:
	if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIRS); fi
	if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR); fi

clean:
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(OBJ_DIR)/$(FRAMEWORK_DIR)/*.o
	$(RM) $(OBJ_DIR)/$(TEST_DIR)/*.o
	@ echo 'Object files removed'

mrproper: clean
	@$(RM) $(BIN_DIR)/$(EXE)
	@echo 'Executable file removed'

archive:
	tar cfvz Box2D_interface.tar.gz $(ARCHIVE_FILES)

