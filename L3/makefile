###Makefile
CC=clang
CFLAGS=-Wall -pedantic -Werror -g
LDFLAGS=-lm -lpthread
MATR = multiply_matrix.c matrix.c
TAR = mthread work matrix gitversion.c
.PHONY: clean all mthread work matrix gitversion.c 

all: $(TAR)

mthread: mthread.c gitversion.c $(HEAD)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

work: work.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

matrix: $(MATR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

gitversion.c: ../.git/HEAD ../.git/index
	echo "const char *gitversion = \"$(shell git rev-parse HEAD)\";" > $@

# CleanUp .......................................#

clean:
	rm -f *.o $(TAR) *.log
