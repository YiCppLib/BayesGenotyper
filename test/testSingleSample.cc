#include <gmock/gmock.h>
#include "Genotyper.h"

#include <set>
#include <algorithm>

using namespace YiCppLib;
using namespace ::testing;

class GenotyperFixture : public Test {
	protected:
		GenotyperFixture() {
			std::vector<Genotyper::AllelicObs> observations;
			Genotyper::AllelicObs obs1("A", 30);
			observations.push_back(obs1);
			Genotyper::AllelicObs obs2("C", 50);
			observations.push_back(obs2);

			gter = Genotyper::s_ptr(new Genotyper(observations));
		}

	protected:
		Genotyper::s_ptr gter;
};

TEST_F(GenotyperFixture, CanReturnProperNumberOfAlleles) {

	std::set<std::string> alleles;
	
	for(auto a : gter->getAllAlleles()) alleles.insert(a);

	ASSERT_THAT(alleles.size(), Eq(2));
}

TEST_F(GenotyperFixture, CanReturnAllAlleles) {
	auto alleles = gter->getAllAlleles();
	auto aIter = std::find(alleles.cbegin(), alleles.cend(), "A");
	ASSERT_THAT(aIter, Not(Eq(alleles.cend())));

	aIter = std::find(alleles.cbegin(), alleles.cend(), "C");
	ASSERT_THAT(aIter, Not(Eq(alleles.cend())));
}

TEST_F(GenotyperFixture, CanReturnProperNumberOfGenotypes) {

	auto genotypes = gter->getAllGenotypes(2);
	ASSERT_THAT(genotypes.size(), Eq(3));
}

TEST_F(GenotyperFixture, CanReturnAllGenotypes) {
	auto alleles = gter->getAllGenotypes(2);
	auto aIter = std::find(alleles.cbegin(), alleles.cend(), "AA");
	ASSERT_THAT(aIter, Not(Eq(alleles.cend())));

	aIter = std::find(alleles.cbegin(), alleles.cend(), "AC");
	ASSERT_THAT(aIter, Not(Eq(alleles.cend())));

	aIter = std::find(alleles.cbegin(), alleles.cend(), "CC");
	ASSERT_THAT(aIter, Not(Eq(alleles.cend())));
}

TEST_F(GenotyperFixture, CanComputeDataLikelihood) {
	auto homoRefDataLikelihood = gter->dataLikelihood("AA");
	auto homoAltDataLikelihood = gter->dataLikelihood("CC");
	auto hetDataLikelihood = gter->dataLikelihood("AC");

	auto sum = homoRefDataLikelihood + homoAltDataLikelihood + hetDataLikelihood;

	homoRefDataLikelihood = homoRefDataLikelihood / sum;
	homoAltDataLikelihood = homoAltDataLikelihood / sum;
	hetDataLikelihood = hetDataLikelihood / sum;

	ASSERT_THAT(homoRefDataLikelihood, Ge(0.0));
	ASSERT_THAT(homoRefDataLikelihood, Le(1.0));
	std::cerr<<"homoRefDL: "<<homoRefDataLikelihood<<std::endl;

	ASSERT_THAT(homoAltDataLikelihood, Ge(0.0));
	ASSERT_THAT(homoAltDataLikelihood, Le(1.0));
	std::cerr<<"homoAltDL: "<<homoAltDataLikelihood<<std::endl;


	ASSERT_THAT(hetDataLikelihood, Ge(0.0));
	ASSERT_THAT(hetDataLikelihood, Le(1.0));
	std::cerr<<"hetDL: "<<hetDataLikelihood<<std::endl;
}

TEST_F(GenotyperFixture, CanGenotype) {
	auto genotypes = gter->getAllGenotypes(2);

	std::string bestGenotype;
	double bestDataLikelihood = 0;
	double sum = 0;;

	for(auto gtIter = genotypes.cbegin(); gtIter != genotypes.cend(); gtIter++) {
		auto dataLikelihood = gter->dataLikelihood(*gtIter);
		if(dataLikelihood > bestDataLikelihood) {
			bestGenotype = *gtIter;
			bestDataLikelihood = dataLikelihood;
		}
		sum += dataLikelihood;
	}

	bestDataLikelihood /= sum;

	ASSERT_THAT(bestDataLikelihood, Ge(0.0));
	ASSERT_THAT(bestDataLikelihood, Le(1.0));

	std::cerr<<"Best Genotype: "<<bestGenotype<<"; Best Data Likelihood: "<<bestDataLikelihood<<std::endl;
}
