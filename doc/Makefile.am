if FOUND_DOT

doc_DATA = design.pdf

design.pdf: design.dot
	dot $(top_srcdir)/doc/design.dot -Tpdf > $@

else !FOUND_DOT
all:
	@echo "Document compilation is disabled due to missing dot utility"

.PHONY: all
endif !FOUND_DOT
