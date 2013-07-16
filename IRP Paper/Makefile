FILEBASE=main

all: pdf
	
pdf: clean
	
	pdflatex $(FILEBASE)
	bibtex   $(FILEBASE)
	pdflatex $(FILEBASE)
	pdflatex $(FILEBASE)

	
clean:
	
	rm -f *aux *spl *out *log *bbl *blg *dvi *ps *pdf
	
