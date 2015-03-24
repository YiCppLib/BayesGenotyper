#ifndef YICPPLIB_BAYESPOSTERIORGENOTYPER_H_
#define YICPPLIB_BAYESPOSTERIORGENOTYPER_H_

#include "IGenotyper.h"

namespace YiCppLib {
	/** Genotyper that Utilizes Bayesian Posterior Probability
	 *  This concrete genotyper class evaluates the bayesian posterior
	 *  probabilities of all possible genotypes conditioned on the given
	 *  observations, and pick the one that has the highest possibility
	 */
	class BayesPosteriorGenotyper : public IGenotyper {
		public:
			BayesPosteriorGenotyper(const IGenotypeList& gtList) : IGenotyper(gtList) {}
			virtual ~BayesPosteriorGenotyper() {}

			virtual std::vector<T_GenotypeRanked> genotype(const IEvidence& evidences) const noexcept override;

		private:
			struct Impl;
	};
}

#endif
