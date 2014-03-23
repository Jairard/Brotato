LOCAL_SRC_DIR = ../$(SRC_DIR)/$(DIR)
LOCAL_OBJ_DIR = ../$(OBJ_DIR)/$(DIR)

SRC = $(wildcard $(LOCAL_SRC_DIR)/*.cpp)
OBJ = $(SRC:$(LOCAL_SRC_DIR)/%.cpp=$(LOCAL_OBJ_DIR)/%.o)

ALL: $(OBJ)
	
$(LOCAL_OBJ_DIR)/%.o: $(LOCAL_SRC_DIR)/%.cpp $(LOCAL_SRC_DIR)/%.hpp
	@$(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@ echo 'Source file' $< 'compiled with header'

$(LOCAL_OBJ_DIR)/%.o: $(LOCAL_SRC_DIR)/%.cpp
	@$(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@ echo 'Source file' $< 'compiled'
	
clean:
	$(RM) $(LOCAL_OBJ_DIR)/*.o

