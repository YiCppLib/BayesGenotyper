#ifndef YICPPLIB_IGENOTYPER_H_
#define YICPPLIB_IGENOTYPER_H_

#include "IGenotypeList.h"
#include "IEvidence.h"

#include <vector>
#include <tuple>
#include <algorithm>

namespace YiCppLib {

	using T_GenotypeRanked = std::tuple<T_Genotype, double>;


	/** The Genotyper Interface
	 *  This interface defines common behaviors that should be present in all
	 *  concrete genotyper classes.
	 */
	class IGenotyper {
		public:
			/** Constructor
			 *  The constructor initializes the member field m_gtList with the
			 *  provided parameter. All the genotypings will be based on the
			 *  given genotype list as the entire set of possible genotypes
			 *
			 *  @param gtList The IGenotypeList object on which genotyping are based on
			 */
			IGenotyper(const IGenotypeList& gtList) : 
				m_gtList(gtList), 
				m_gtListSize(std::count_if(gtList.cbegin(), gtList.cend(), [](const T_Genotype& g){return true;})) {};

			virtual ~IGenotyper() {}

			/** Genotype based on evidence
			 *  This method will evaluate the evidences provided as the parameter,
			 *  and determine the likelihood of each genotype among all the 
			 *  possibilities that is described by the member field m_gtList being
			 *  the actual underlying genotype.
			 *
			 *  @param evidence The evidences to be based on for genotyping
			 *  @return A vector of (genotype, likelihood) tuples, sorted by likelihood in descending order
			 */

			virtual std::vector<T_GenotypeRanked> genotype(const IEvidence& evidences) const noexcept = 0;

		protected:
			const IGenotypeList& m_gtList; //!< All possible genotypes 
			const size_t m_gtListSize; //!< Number of all possible genotypes
	};
}

#endif
