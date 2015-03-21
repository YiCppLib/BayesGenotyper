#include "Genotyper.h"

#include <iostream>
#include <algorithm>
#include <gsl/gsl_math.h>
#include <gsl/gsl_multiset.h>
#include <gsl/gsl_randist.h>

using namespace YiCppLib;

Genotyper::Genotyper(const std::vector<AllelicObs>& obs) :
	m_obs(obs) 
{}

std::vector<std::string> Genotyper::getAllAlleles() const noexcept {
	std::vector<std::string> alleles;
	for(const AllelicObs& obs : m_obs) {
		alleles.push_back(std::get<0>(obs));
	}

	std::sort(alleles.begin(), alleles.end());

	return alleles;
}

std::vector<std::string> Genotyper::getAllGenotypes(unsigned int ploidy) const noexcept {
	std::vector<std::string> alleles = getAllAlleles();

	std::vector<std::string> genotypes;

	gsl_multiset * gtCbnt = gsl_multiset_calloc(alleles.size(), ploidy);

	do {
		std::string genotype ="";
		for(size_t i=0; i<ploidy; i++) genotype+=alleles[gtCbnt->data[i]];
		genotypes.push_back(genotype);
	} while (gsl_multiset_next(gtCbnt) == GSL_SUCCESS);

	gsl_multiset_free(gtCbnt);

	return genotypes;
}

double Genotyper::dataLikelihood(const std::string& genotype) const noexcept {

	if(genotype[0] == genotype[1] && genotype[0] == std::get<0>(m_obs[0])[0]) {
		return homoRefDataLikelihood();
	}
	else if(genotype[0] == genotype[1]) {
		return homoAltDataLikelihood();
	}
	else {
		return hetDataLikelihood();
	}
}


double Genotyper::homoRefDataLikelihood() const {
	double p[4] = {0.91, 0.03, 0.03, 0.03};
	unsigned int n[4] = {std::get<1>(m_obs[0]), std::get<1>(m_obs[1]), 0, 0};

	return gsl_ran_multinomial_pdf(4, p, n);
}

double Genotyper::homoAltDataLikelihood() const {
	double p[4] = {0.03, 0.91, 0.03, 0.03};
	unsigned int n[4] = {std::get<1>(m_obs[0]), std::get<1>(m_obs[1]), 0, 0};

	return gsl_ran_multinomial_pdf(4, p, n);
}

double Genotyper::hetDataLikelihood() const {
	double p[4] = {0.47, 0.47, 0.03, 0.03};
	unsigned int n[4] = {std::get<1>(m_obs[0]), std::get<1>(m_obs[1]), 0, 0};

	return gsl_ran_multinomial_pdf(4, p, n);
}
