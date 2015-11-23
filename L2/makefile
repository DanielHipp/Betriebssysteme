### .........  MAKEFILE .........................####
###                                                         ####
### .......generic Makefile .....................####
CC=clang
CFLAGS=-Wall -pedantic -Werror -g
LDFLAGS=-lm -static -L. -lgenstacklib
AR = ar
ARFLAGS = crs
SRCLIB = genstacklib.c
SRCC = $(shell ls gentest*.c)
OBJ = ${SRCLIB:.c=.o}
LIB = genstacklib
EXE = gentest1 gentest2 gentest3 gentest4
.PHONY: clean all gentests

all: $(LIB) $(EXE)
gentests: $(EXE)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

%: %.c
	$(CC) -o $@ $< $(LIB) $(CFLAGS)

# CleanUp .......................................#

clean:
	rm -f *.o *.valtest $(EXE) $(LIB)
	