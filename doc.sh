#!/bin/bash

doxygen Doxyfile
cd latex
make
mv refman.pdf ..
cd ..

pdflatex CompteRendu.tex
pdflatex CompteRendu.tex
bibtex CompteRendu.aux
pdflatex CompteRendu.tex
pdflatex CompteRendu.tex

pdftk CompteRendu.pdf refman.pdf output compteRenduFinal.pdf
rm -r latex
