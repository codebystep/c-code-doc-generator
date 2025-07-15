CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LDFLAGS = $(CFLAGS)

BUILD_DIR = build
BIN = ccdoc.exe

all: clean $(BUILD_DIR) $(BIN)

$(BIN): $(BUILD_DIR)/main.o $(BUILD_DIR)/data_structures.o $(BUILD_DIR)/file_processing.o $(BUILD_DIR)/documentation_processing.o $(BUILD_DIR)/latex_formatting.o $(BUILD_DIR)/utility.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/main.o: main.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/data_structures.o: data_structures.c data_structures.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/file_processing.o: file_processing.c file_processing.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/documentation_processing.o: documentation_processing.c documentation_processing.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/latex_formatting.o: latex_formatting.c latex_formatting.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/utility.o: utility.c utility.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR):
	mkdir $@

clean:
	rm -rf $(BUILD_DIR)
