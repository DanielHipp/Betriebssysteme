#makefile
CC=clang
CFLAGS=-Wall -pedantic -Werror -g	
LDFLAGS=-lm
OBJECTS = ulMenuStack.c ulstack.c 
TARGET = ulMenuStack

all: ulMenuStack

$(TARGET):$(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

clean:
	rm -f *.o (TARGET)