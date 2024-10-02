# Makefile for the "Lightning-Fast Password Check" project

# Compiler variables.
CC := gcc
CFLAGS=-I$(INC_DIR)

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

# Path variables.
INC_DIR := ./include
SRC_DIR := ./src
OFILES := $(OBJ_PATH)/auxfunc.o $(OBJ_PATH)/main.o

# Make all.
all: final

# Compiling .o files with messages:
$(OBJ_PATH)/auxfunc.o: $(SRC_DIR)/auxfunc.c
	$(info Compiling auxiliary functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/auxfunc.c -o $(OBJ_PATH)/auxfunc.o

$(OBJ_PATH)/main.o: $(SRC_DIR)/main.c
	$(info Compiling main function object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_PATH)/main.o -lssl -lcrypto -lcurl

# Final linking:

final: $(OFILES)
	$(info Linking and producing executable.)
	@$(CC) $(CFLAGS) $(OFILES) -o $(OUT_FILE) -lssl -lcrypto -lcurl

# Clean:

clean: 
	$(info Removing object files.)
	@$(RM) $(OBJ_PATH)/*.o

bincl:	
	$(info Removing binary.)
	@$(RM) $(OUT_FILE)

allcl: clean bincl
