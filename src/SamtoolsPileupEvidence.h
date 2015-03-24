#ifndef YICPPLIB_SAMTOOLSPILEUPEVIDENCE_H_
#define YICPPLIB_SAMTOOLSPILEUPEVIDENCE_H_

#include "IEvidence.h"
#include "IObservation.h"
#include <memory>
#include <string>

namespace YiCppLib {
	/** Class that captures samtools pileup as evidence
	 *  This class takes as constructor parameter a samtools pileup string,
	 *  and creates the evidences for various alleles.
	 */
	class SamtoolsPileupEvidence : public IEvidence {
		public:
			SamtoolsPileupEvidence(const std::string& pileupStr);
			SamtoolsPileupEvidence(const SamtoolsPileupEvidence& rhs);
			//SamtoolsPileupEvidence& operator=(const SamtoolsPileupEvidence& rhs);
			SamtoolsPileupEvidence(SamtoolsPileupEvidence&& rhs);
			SamtoolsPileupEvidence& operator=(SamtoolsPileupEvidence&& rhs);
			~SamtoolsPileupEvidence();

			virtual std::vector<const IObservation*> observationsForAllele(size_t allele) const noexcept override;

		private:
			struct Impl;
			std::unique_ptr<struct Impl> m_pImpl;
	};
}

#endif
