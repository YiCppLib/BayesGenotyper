#ifndef YICPPLIB_IGENOTYPELIST_H_
#define YICPPLIB_IGENOTYPELIST_H_

#include <vector>
#include <unordered_set>

namespace YiCppLib {

	/** The Genotype type
	 *  A genotype is defined as a multiset of alleles in numerical space
	 */
	using T_Genotype = std::unordered_multiset<int>;

	/** A Genotype Generator
	 *  This class represent an iterable object with an underlying
	 *  list of all possible genotypes. They are accessed through
	 *  a linear forward-only iterator
	 */
	class IGenotypeList {
		public:

			/** Constructor
			 *  
			 * @param alphabetSize The size of the underlying allele alphabet
			 */
			IGenotypeList(size_t alphabetSize) : m_alphabetSize(alphabetSize) {}

			/** Copy Constructor
			 */
			IGenotypeList(const IGenotypeList& rhs) : m_alphabetSize(rhs.m_alphabetSize) {}

			/** The size of the underlying allele alphabet
			 * 
			 * @return the size of the underlying allele alphabet
			 */
			size_t alphabetSize() const noexcept {return m_alphabetSize;}


			/** The first genotype
			 * The function returns an iterator pointing to the very first genotype
			 *
			 * @return Iterator to the first genotype
			 */
			virtual std::vector<T_Genotype>::const_iterator cbegin() const noexcept = 0;

			/** The end of genotypes
			 * The function returns an iterator pointing to the position that
			 * is after the last genotype.
			 *
			 * @return Iterator to after the last genotype
			 */
			virtual std::vector<T_Genotype>::const_iterator cend() const noexcept = 0;

			/** Compatible begin() for range enumeration
			 */
			std::vector<T_Genotype>::const_iterator begin() const noexcept {return cbegin();}
			std::vector<T_Genotype>::const_iterator end() const noexcept {return cend();}

		protected:
			size_t m_alphabetSize; //!<The size of the underlying allele alphabet
	};
}

#endif
