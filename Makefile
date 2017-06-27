CC=g++
CFLAGS=-std=c++11

PROGRAM_NAME=joint-purchases

SRC_DIR=src
OUT_DIR=out
INSTALL_DIR=/usr/bin/

install: compile
	chmod 755 $(OUT_DIR)/$(PROGRAM_NAME)
	cp $(OUT_DIR)/$(PROGRAM_NAME) $(INSTALL_DIR)
	
compile:
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/* -o $(OUT_DIR)/$(PROGRAM_NAME)

clean:
	rm -rf $(OUT_DIR)
