#include "PloidyMultisetGenotypeList.h"
#include <gsl/gsl_multiset.h>
#include <memory>

namespace YiCppLib {
	struct PloidyMultisetGenotypeList::Impl {
		std::vector<T_Genotype> genotypes;
	};
}

using namespace YiCppLib;

static auto delGslMultiset = [](gsl_multiset * ms) {gsl_multiset_free(ms);};

PloidyMultisetGenotypeList::PloidyMultisetGenotypeList(size_t alphabetSize, int ploidy) :
	IGenotypeList(alphabetSize),
	m_pImpl(new struct Impl())
{
	if(alphabetSize == 0) throw std::make_shared<Exceptions::InvalidAlphabetSize>();
	if(ploidy == 0) throw std::make_shared<Exceptions::InvalidPloidy>();

	std::unique_ptr<gsl_multiset, decltype(delGslMultiset)> c(gsl_multiset_calloc(alphabetSize, ploidy), delGslMultiset);
	do {
		T_Genotype genotype;
		for(int i=0; i<ploidy; i++) 
			genotype.insert(gsl_multiset_get(c.get(), i));

		m_pImpl->genotypes.push_back(genotype);
	} while(gsl_multiset_next(c.get()) == GSL_SUCCESS);
}

PloidyMultisetGenotypeList::PloidyMultisetGenotypeList(const PloidyMultisetGenotypeList& rhs) :
	IGenotypeList(rhs),
	m_pImpl(new struct Impl(*rhs.m_pImpl))
{}

PloidyMultisetGenotypeList& PloidyMultisetGenotypeList::operator=(const PloidyMultisetGenotypeList& rhs) {
	if (this != &rhs) {
		*m_pImpl = *rhs.m_pImpl;
	}
	return *this;
}

PloidyMultisetGenotypeList::~PloidyMultisetGenotypeList() = default;
PloidyMultisetGenotypeList::PloidyMultisetGenotypeList(PloidyMultisetGenotypeList&& rhs) = default;
PloidyMultisetGenotypeList& PloidyMultisetGenotypeList::operator=(PloidyMultisetGenotypeList&& rhs) = default;

std::vector<T_Genotype>::const_iterator PloidyMultisetGenotypeList::cbegin() const noexcept {
	return m_pImpl->genotypes.cbegin();
}

std::vector<T_Genotype>::const_iterator PloidyMultisetGenotypeList::cend() const noexcept {
	return m_pImpl->genotypes.cend();
}
