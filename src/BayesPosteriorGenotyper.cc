#include "BayesPosteriorGenotyper.h"
#include "IGenotypeList.h"

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_randist.h>

#include <algorithm>

using namespace YiCppLib;

static auto delGslMatrix = [](gsl_matrix * m) -> void {gsl_matrix_free(m);};
static auto delGslVector = [](gsl_vector * v) -> void {gsl_vector_free(v);};
static auto delGslVectorUint = [](gsl_vector_uint * v) -> void {gsl_vector_uint_free(v);};

struct BayesPosteriorGenotyper::Impl {
	static double UniformPrior(size_t gtSize) {
		return 1.0 / double(gtSize);
	}

	static double DataLikelihood(const IEvidence& evidences, const T_Genotype& gt, size_t gtSize, size_t alphabetSize) {
		std::unique_ptr<gsl_matrix, decltype(delGslMatrix)> srcProb(gsl_matrix_alloc(alphabetSize, 2), delGslMatrix);
		std::unique_ptr<gsl_vector_uint, decltype(delGslVectorUint)> samplingCount(gsl_vector_uint_alloc(alphabetSize), delGslVectorUint);

		for(size_t allele = 0; allele < alphabetSize; allele++) {
			size_t alleleCount = gt.count(allele);

			// The probability of sampling from a particular allele
			// equals the fraction of the allele among all alleles
			// in the given genotype
			double sourcingProb = double(alleleCount) / double(gt.size());
			gsl_matrix_set(srcProb.get(), allele, 0, sourcingProb);
			gsl_matrix_set(srcProb.get(), allele, 1, 1-sourcingProb);

			// Also count the number of observations conferring this allele
			size_t obsCount = evidences.observationsForAllele(allele).size();
			gsl_vector_uint_set(samplingCount.get(), allele, obsCount);
		}

		std::unique_ptr<gsl_vector, decltype(delGslVector)> readProb(gsl_vector_alloc(2), delGslVector);
		gsl_vector_set(readProb.get(), 0, 0.9);
		gsl_vector_set(readProb.get(), 1, 0.1);

		std::unique_ptr<gsl_vector, decltype(delGslVector)> samplingProb(gsl_vector_alloc(alphabetSize), delGslVector);
		gsl_blas_dgemv(CblasNoTrans, 1.0, srcProb.get(), readProb.get(), 0.0, samplingProb.get());

		double multinomial_pdf = gsl_ran_multinomial_pdf(alphabetSize, samplingProb->data, samplingCount->data);

		return multinomial_pdf;
	}
};

std::vector<T_GenotypeRanked> BayesPosteriorGenotyper::genotype(const IEvidence& evidences) const noexcept {

	std::vector<T_GenotypeRanked> result;

	for(auto genotype : m_gtList) {
		result.push_back(T_GenotypeRanked(genotype, Impl::UniformPrior(m_gtListSize) * Impl::DataLikelihood(evidences, genotype, m_gtListSize, m_gtList.alphabetSize())));
	}

	std::sort(std::begin(result), std::end(result), 
			[](T_GenotypeRanked const &v1, T_GenotypeRanked const &v2) {
				return std::get<1>(v1) > std::get<1>(v2);
			}
			);

	return result;
}
