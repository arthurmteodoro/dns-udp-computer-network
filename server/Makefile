TARGET = server.out

CFLAGS = -static -g -Wall -std=c99
LDFLAGS =  -g -Wall
CC = gcc

C_FILES := $(wildcard src/*.c)
OBJ_FILES := $(addprefix build/,$(notdir $(C_FILES:.c=.o)))

.PHONY : all
all : $(TARGET)

build: $(TARGET)
$(TARGET): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^
$(OBJ_FILES): build/%.o : src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(TARGET) build/*.a build/*.o build/*~ 