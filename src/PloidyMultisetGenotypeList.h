#ifndef YICPPLIB_PLOIDYMULTISETGENOTYPELIST_H_
#define YICPPLIB_PLOIDYMULTISETGENOTYPELIST_H_

#include "IGenotypeList.h"

#include "IAlleleAlphabet.h"

#include <stdexcept>
#include <memory>

namespace YiCppLib {

	/** Genotype List that is a multiset of alleles
	 * This class models a genotype as a multiset (of size ploidy) on all
	 * possible alleles.
	 */
	class PloidyMultisetGenotypeList : public IGenotypeList {
		public:
			PloidyMultisetGenotypeList(size_t alphabetSize, int ploidy);
			~PloidyMultisetGenotypeList();
			PloidyMultisetGenotypeList(PloidyMultisetGenotypeList&& rhs);
			PloidyMultisetGenotypeList& operator=(PloidyMultisetGenotypeList&& rhs);
			PloidyMultisetGenotypeList(const PloidyMultisetGenotypeList& rhs);
			PloidyMultisetGenotypeList& operator=(const PloidyMultisetGenotypeList& rhs);

			virtual std::vector<T_Genotype>::const_iterator cbegin() const noexcept override;
			virtual std::vector<T_Genotype>::const_iterator cend() const noexcept override;

		private:
			struct Impl;
			std::unique_ptr<struct Impl> m_pImpl;
	};

	namespace Exceptions {
		class InvalidPloidy : public std::runtime_error {
			public:
				InvalidPloidy() : std::runtime_error("Invalid Ploidy Value") {}
		};

		class InvalidAlphabetSize: public std::runtime_error {
			public:
				InvalidAlphabetSize() : std::runtime_error("Invalid Allele Alphabet Size") {}
		};
	}
}

#endif
