# Makefile for the "Lightning-Fast Password Check" project

# Compiler.
CC := gcc

# OS dependent variables:
ifeq ($(OS),Windows_NT)
	OBJ_PATH := ./obj/win
	OUT_FILE := lfpch.exe
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OBJ_PATH := ./obj/lnx
		OUT_FILE := lfpch
	endif
	ifeq ($(UNAME_S),Darwin)
		OBJ_PATH := ./obj/mac
		OUT_FILE := lfpch
	endif
endif

# General path variables.
INC_DIR := ./include
LIB_DIR := ./lib
SRC_DIR := ./src
OFILES := $(OBJ_PATH)/backend.o $(OBJ_PATH)/gui.o $(OBJ_PATH)/hashing.o $(OBJ_PATH)/main.o $(OBJ_PATH)/requests.o $(OBJ_PATH)/strop.o

# Flags.
CFLAGS := -Wall -g `pkg-config --cflags gtk4` -I$(INC_DIR) -L$(LIB_DIR)
LDFLAGS := `pkg-config --libs gtk4` -lcrypto -lcurl

# Make all.
all: final

# Create object directory if it doesn't exist
$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

# Compiling .o files with messages:

$(OBJ_PATH)/backend.o: $(OBJ_PATH) $(SRC_DIR)/backend.c
	$(info Compiling the backend functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/backend.c -o $(OBJ_PATH)/backend.o

$(OBJ_PATH)/gui.o: $(OBJ_PATH) $(SRC_DIR)/gui.c
	$(info Compiling the GUI functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/gui.c -o $(OBJ_PATH)/gui.o

$(OBJ_PATH)/hashing.o: $(OBJ_PATH) $(SRC_DIR)/hashing.c
	$(info Compiling the hashing functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/hashing.c -o $(OBJ_PATH)/hashing.o

$(OBJ_PATH)/main.o: $(OBJ_PATH) $(SRC_DIR)/main.c
	$(info Compiling the main function object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_PATH)/main.o

$(OBJ_PATH)/requests.o: $(OBJ_PATH) $(SRC_DIR)/requests.c
	$(info Compiling the request functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/requests.c -o $(OBJ_PATH)/requests.o

$(OBJ_PATH)/strop.o: $(OBJ_PATH) $(SRC_DIR)/strop.c
	$(info Compiling the string operation functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/strop.c -o $(OBJ_PATH)/strop.o

# Final linking:

final: $(OFILES)
	$(info Linking and producing executable.)
	@$(CC) $(OFILES) -o $(OUT_FILE) $(LDFLAGS)

# Clean:

clean: 
	$(info Removing object files.)
	@$(RM) $(OBJ_PATH)/*.o

bincl:	
	$(info Removing binary.)
	@$(RM) $(OUT_FILE)

allcl: clean bincl

# Declare phony targets
.PHONY: all clean bincl allcl
