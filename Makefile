# Makefile for the "Lightning-Fast Password Check" project

# Compiler.
CC := gcc

# OS dependent variables:
ifeq ($(OS),Windows_NT)
	OBJ_PATH := ./obj/win
	EXE := lfpch.exe
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OBJ_PATH := ./obj/lnx
		EXE := lfpch
	endif
	ifeq ($(UNAME_S),Darwin)
		OBJ_PATH := ./obj/mac
		EXE := lfpch
	endif
endif

# General path variables.
INC_DIR := ./include
LIB_DIR := ./lib
SRC_DIR := ./src
OFILES := $(OBJ_PATH)/backend.o $(OBJ_PATH)/gui.o $(OBJ_PATH)/gui_cb.o $(OBJ_PATH)/hashing.o $(OBJ_PATH)/main.o $(OBJ_PATH)/request.o

# Flags.
CFLAGS := -Wall -g $(shell pkg-config --cflags gtk4) -I$(INC_DIR) -L$(LIB_DIR) # Debug flags on for now.
LDFLAGS := $(shell pkg-config --libs gtk4) -lcrypto -lcurl

# Make all.
all: final

# Create object directory if it doesn't exist.
$(DIR_CHECK):
	@mkdir -p $(OBJ_PATH)

# Compiling .o files with messages:

$(OBJ_PATH)/backend.o: $(DIR_CHECK) $(SRC_DIR)/backend.c
	$(info Compiling the backend functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/backend.c -o $(OBJ_PATH)/backend.o

$(OBJ_PATH)/gui.o: $(DIR_CHECK) $(SRC_DIR)/gui.c
	$(info Compiling the GUI structure object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/gui.c -o $(OBJ_PATH)/gui.o

$(OBJ_PATH)/gui_cb.o: $(DIR_CHECK) $(SRC_DIR)/gui_cb.c
	$(info Compiling the GUI callback functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/gui_cb.c -o $(OBJ_PATH)/gui_cb.o

$(OBJ_PATH)/hashing.o: $(DIR_CHECK) $(SRC_DIR)/hashing.c
	$(info Compiling the hashing functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/hashing.c -o $(OBJ_PATH)/hashing.o

$(OBJ_PATH)/main.o: $(DIR_CHECK) $(SRC_DIR)/main.c
	$(info Compiling the main function object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_PATH)/main.o

$(OBJ_PATH)/request.o: $(DIR_CHECK) $(SRC_DIR)/request.c
	$(info Compiling the request functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/request.c -o $(OBJ_PATH)/request.o

# Final linking:

final: $(OFILES)
	$(info Linking and producing executable.)
	@$(CC) $(OFILES) -o $(EXE) $(LDFLAGS)

# Clean:

clean: 
	$(info Removing object files.)
	@$(RM) $(OBJ_PATH)/*.o

binclean:	
	$(info Removing binary.)
	@$(RM) $(EXE)

allclean: clean bincl

# Declare phony targets.
.PHONY: all clean bincl allcl
