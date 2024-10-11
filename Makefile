# Makefile for the "Lightning-Fast Password Check" project

# Compiler.
CC := gcc

# OS dependent variables:
ifeq ($(OS),Windows_NT)
	OBJ_PATH := ./obj/win
	EXE := lfpch.exe
	MFLAGS := -mwindows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OBJ_PATH := ./obj/lnx
		EXE := lfpch
		MFLAGS :=
	endif
	ifeq ($(UNAME_S),Darwin)
		OBJ_PATH := ./obj/mac
		EXE := lfpch
		MFLAGS :=
	endif
endif

# General path variables.
INC_DIR := ./include
LIB_DIR := ./lib
SRC_DIR := ./src
OFILES := $(OBJ_PATH)/callback.o $(OBJ_PATH)/checker.o $(OBJ_PATH)/gui.o $(OBJ_PATH)/generator.o $(OBJ_PATH)/hashing.o $(OBJ_PATH)/main.o $(OBJ_PATH)/request.o

# Flags.
CFLAGS := -Wall -g -I$(INC_DIR) $(shell pkg-config --cflags gtk4)  # Debug flags on for now.
LDFLAGS := -L$(LIB_DIR) -lcrypto -lcurl $(shell pkg-config --libs gtk4)

# Make all.
all: final

# Create object directory if it doesn't exist.
$(DIR_CHECK):
	@mkdir -p $(OBJ_PATH)

# Compiling .o files with messages:

$(OBJ_PATH)/callback.o: $(DIR_CHECK) $(SRC_DIR)/callback.c
	$(info Compiling the GUI callback functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/callback.c -o $(OBJ_PATH)/callback.o

$(OBJ_PATH)/checker.o: $(DIR_CHECK) $(SRC_DIR)/checker.c
	$(info Compiling the password checker backend functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/checker.c -o $(OBJ_PATH)/checker.o

$(OBJ_PATH)/generator.o: $(DIR_CHECK) $(SRC_DIR)/generator.c
	$(info Compiling the password generator backend functions object file.)
	@$(CC) $(CFLAGS) -mrdseed -c $(SRC_DIR)/generator.c -o $(OBJ_PATH)/generator.o

$(OBJ_PATH)/gui.o: $(DIR_CHECK) $(SRC_DIR)/gui.c
	$(info Compiling the GUI structure object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/gui.c -o $(OBJ_PATH)/gui.o

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
	@$(CC) $(OFILES) -o $(EXE) $(MFLAGS) $(LDFLAGS)

# Clean:

clean: 
	$(info Removing object files.)
	@$(RM) $(OBJ_PATH)/*.o

cleanbin:	
	$(info Removing binary.)
	@$(RM) "$(EXE)"

cleanall: clean cleanbin

# Declare phony targets.
.PHONY: all clean bincl allcl
