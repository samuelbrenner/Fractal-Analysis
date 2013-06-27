IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)

ODIR =../obj
LDIR =../lib

LIBS=-lm

#_DEPS = hellomake.h
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = HistObj.o Histogram.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cxx
	$(CC) -c -o $@ $< $(CFLAGS)
	
all: $(OBJ)
		
.PHONY: clean
		
clean:
	rm -f $(ODIR)/*.o
