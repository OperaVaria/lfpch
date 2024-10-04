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

# Libraries.
LIBS := -lcrypto -lcurl

# Path variables.
INC_DIR := ./include
#LIB_DIR := ./lib
SRC_DIR := ./src
OFILES := $(OBJ_PATH)/hashing.o $(OBJ_PATH)/main.o $(OBJ_PATH)/requests.o $(OBJ_PATH)/strop.o

# Make all.
all: final

# Compiling .o files with messages:

$(OBJ_PATH)/hashing.o: $(SRC_DIR)/hashing.c
	$(info Compiling hashing functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/hashing.c -o $(OBJ_PATH)/hashing.o

$(OBJ_PATH)/main.o: $(SRC_DIR)/main.c
	$(info Compiling main function object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_PATH)/main.o

$(OBJ_PATH)/requests.o: $(SRC_DIR)/requests.c
	$(info Compiling request functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/requests.c -o $(OBJ_PATH)/requests.o

$(OBJ_PATH)/strop.o: $(SRC_DIR)/strop.c
	$(info Compiling auxiliary functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/strop.c -o $(OBJ_PATH)/strop.o

# Final linking:

final: $(OFILES)
	$(info Linking and producing executable.)
	@$(CC) $(CFLAGS) $(OFILES) -o $(OUT_FILE) $(LIBS)

# Clean:

clean: 
	$(info Removing object files.)
	@$(RM) $(OBJ_PATH)/*.o

bincl:	
	$(info Removing binary.)
	@$(RM) $(OUT_FILE)

allcl: clean bincl
