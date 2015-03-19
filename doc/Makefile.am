.dot.pdf:
	@dot -Tpdf -o $@ $<

EXTRA_DIST = design.dot

DOCUMENTS=design.pdf

if FOUND_DOT
all: $(DOCUMENTS)

else !FOUND_DOT
all:
	@echo "Document compilation is disabled due to missing dot utility"

endif !FOUND_DOT

.PHONY: all

clean-local: 
	@rm -f $(DOCUMENTS)

.PHONY: clean
