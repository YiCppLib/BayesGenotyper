#ifndef YICPPLIB_IOBSERVATION_H_
#define YICPPLIB_IOBSERVATION_H_

#include <cstddef>

namespace YiCppLib {
	
	/** An actual observation into the genotype
	 *  An object of this class encapsulates an actual observation into the
	 *  genotype of the underlying sample. It records the observed allele, as
	 *  well as how confident that the observation is accurate.
	 */
	class IObservation {
		public:
			/** The observed allele
			 * @return The observed allele in numerical space
			 */
			virtual size_t allele() const noexcept = 0;

			/** The quality of the observation
			 * @return The probability that the observation is accurate
			 */
			virtual double quality() const noexcept = 0;
	};
}

#endif
