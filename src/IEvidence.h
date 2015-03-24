#ifndef YICPPLIB_IEVIDENCE_H_
#define YICPPLIB_IEVIDENCE_H_

#include "IObservation.h"
#include <vector>

namespace YiCppLib {

	/** Evidence for genotyping
	 * The object of this class contains all evidences for a single 
	 * genotyping operation
	 */
	class IEvidence {
		public:
			/** All observations for a specific allele
			 *  This function should return a vector of constant references to
			 *  observations that are confirming a specific allele. If an allele
			 *  has not been observed at all, retunr an empty vector
			 *
			 *  @param allele The allele in numerical space for which the observations are requested
			 *  @return A vector of constant references to observations confirming the allele (could be empty)
			 */
			virtual std::vector<const IObservation*> observationsForAllele(size_t allele) const noexcept = 0;
	};
}

#endif
