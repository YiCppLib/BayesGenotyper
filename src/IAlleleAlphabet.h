#ifndef BAYESGENOTYPE_IALPHABETALLELE_H
#define BAYESGENOTYPE_IALPHABETALLELE_H

#include <stdexcept>

namespace YiCppLib {

	/** The allele alphabet interface
	 *  An allele alphabet provides information regarding all possible alleles for any genotyping task
	 */

	template<class T>
	class IAlleleAlphabet {
		public:
			virtual ~IAlleleAlphabet() {}

			/** Size of the alphabet
			 *  The total number of different alleles in the alphabet. E.g. a single nucleotide site
			 *  will have 4 possible alleles, "A", "C", "G", and "T".
			 *
			 *  @return the total number of different alleles
			 */
			virtual size_t count() const noexcept = 0;

			/** Map a number to its corresponding allele
			 *  All alleles in the alphabet are represented by an integer number that ranges from 0 to
			 *  the total number of possible alleles - 1. This function provides a mapping between a
			 *  number to its corresponding allele in their repsective types
			 *
			 *  @param allele The numeric representation of an allele
			 *  @return The actual allele
			 */
			virtual T actual(size_t allele) const = 0;
	};

	namespace Exceptions {
		class InvalidAlleleException : public std::runtime_error {public: InvalidAlleleException(const char * msg) : std::runtime_error(msg) {}};
	}
}

#endif

