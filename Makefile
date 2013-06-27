OBJDIR  = obj
LIBDIR  = lib
LIBNAME = libStat.a

all:
	cd Histogram; make; cd -
	ar rvs $(LIBDIR)/$(LIBNAME) $(OBJDIR)/*.o
	cd test;      make; cd -
	
clean:
	cd Histogram; make clean; cd -
	cd test;      make clean; cd -
	rm -f $(OBJDIR)/*.o $(LIBDIR)/*.a

	
