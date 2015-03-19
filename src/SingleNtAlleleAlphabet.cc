#include "SingleNtAlleleAlphabet.h"
#include <memory>

using namespace YiCppLib;

SingleNtAlleleAlphabet::SingleNtAlleleAlphabet() {
	nt[0] = 'A'; 
	nt[1] = 'G'; 
	nt[2] = 'C'; 
	nt[3] = 'T';
}

size_t SingleNtAlleleAlphabet::count() const noexcept {
	return 4;
}

char SingleNtAlleleAlphabet::actual(size_t allele) const {
	if(allele >= 4) throw std::shared_ptr<std::runtime_error>(new Exceptions::InvalidAlleleException("There are only 4 elements in the alphabet"));
	return nt[allele];
}
