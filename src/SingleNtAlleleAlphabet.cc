#include "SingleNtAlleleAlphabet.h"
#include <memory>

using namespace YiCppLib;

SingleNtAlleleAlphabet::SingleNtAlleleAlphabet() {
	nt[0] = 'A'; 
	nt[1] = 'C'; 
	nt[2] = 'G'; 
	nt[3] = 'T';
}

size_t SingleNtAlleleAlphabet::count() const noexcept {
	return 4;
}

char SingleNtAlleleAlphabet::actual(size_t allele) const {
	if(allele >= 4) throw std::make_shared<Exceptions::InvalidAllele>();
	return nt[allele];
}
