### .........  MAKEFILE .........................####
###                                                         ####
### .......generic Makefile .....................####
CC=clang
CFLAGS=-Wall -pedantic -Werror -g
LDFLAGS=-lm -static -L. -lgenstacklib
AR = ar
ARFLAGS = crs
LIBC = genstacklib.c
TESTC = $(shell ls gentest*.c)
OBJ = ${LIBC:.c=.o}
LIB = genstacklib
EXE = $(patsubst %.c,%, (TESTC))
.PHONY: clean all gentests

all: $(LIB) $(EXE)
gentests: $(EXE)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

%: %.c
	$(CC) -o $@ $< $(LIB) $(CFLAGS)

# CleanUp .......................................#

clean:
	rm -f *.o $(EXE) $(LIB)
	