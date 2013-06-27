IDIR =../include
CC=g++
LDIR =../lib
CFLAGS=-I$(IDIR) -L$(LDIR)

LIBS=-lStat

all:
	$(CC) $(CFLAGS) $(LIBS) test.cxx -o test.exe
	
clean:
	rm -f test.exe
