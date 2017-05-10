CC=g++
CFLAGS=-std=c++11

PROGRAM_NAME=joint-purchases
SRC_DIR=src
BUILD_DIR=build
OUT_DIR=out

SRC_NAMES=$(SRC_DIR)/main.cpp
OBJ_NAMES=$(BUILD_DIR)/main.o
MAIN_OBJECT_NAME=main.o

install: compile clean-out
	mkdir $(OUT_DIR)
	mv $(BUILD_DIR)/$(MAIN_OBJECT_NAME) $(OUT_DIR)/$(PROGRAM_NAME)
	make clean-build
	

compile: clean-build
	mkdir $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_NAMES) -o $(OBJ_NAMES)

clean-out:
	rm -rf $(OUT_DIR)

clean-build:
	rm -rf $(BUILD_DIR)

clean: clean-out clean-build
