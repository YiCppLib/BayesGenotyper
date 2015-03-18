#ifndef YICPPLIB_FBGENOTYPER_H
#define YICPPLIB_FBGENOTYPER_H

#include <string>
#include <vector>
#include <tuple>

namespace YiCppLib {

	class Genotyper {
		public:

			// An allelic observation is a two-element tuple with
			// the first being the allele, and second being the count
			using AllelicObs = std::tuple<std::string, unsigned int>;

			using u_ptr = std::unique_ptr<Genotyper>;
			using s_ptr = std::shared_ptr<Genotyper>;

			// A genotyper is instanciated with a set of allelic observations
			Genotyper(const std::vector<AllelicObs>& obs);

			std::vector<std::string> getAllAlleles() const noexcept;
			std::vector<std::string> getAllGenotypes(unsigned int ploidy) const noexcept;

			double dataLikelihood(const std::string& genotype) const noexcept;

		protected:
			const std::vector<AllelicObs> m_obs;

			double homoRefDataLikelihood() const;
			double homoAltDataLikelihood() const;
			double hetDataLikelihood() const;
	};
}

#endif
