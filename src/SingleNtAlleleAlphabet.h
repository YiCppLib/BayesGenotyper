#ifndef BAYESGENOTYPE_SINGLENTALLELEALPHABET_H
#define BAYESGENOTYPE_SINGLENTALLELEALPHABET_H

#include "IAlleleAlphabet.h"

namespace YiCppLib {
	class SingleNtAlleleAlphabet : public IAlleleAlphabet<char> {
		public:
			SingleNtAlleleAlphabet();
			virtual size_t count() const noexcept override;
			virtual char actual(size_t allele) const override;

		private:
			char nt[4];
	};
}

#endif
