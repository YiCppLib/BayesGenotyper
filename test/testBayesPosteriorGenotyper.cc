#include <gmock/gmock.h>
#include "IGenotyper.h"
#include "BayesPosteriorGenotyper.h"
#include "PloidyMultisetGenotypeList.h"
#include "SamtoolsPileupEvidence.h"

using namespace YiCppLib;
using namespace ::testing;

class TestFixture: public Test {
	protected:
		TestFixture() : m_gtList(nullptr), m_gter(nullptr) {
			m_gtList = std::unique_ptr<IGenotypeList>(new PloidyMultisetGenotypeList(4, 2));
			m_gter = std::unique_ptr<IGenotyper>(new BayesPosteriorGenotyper(*m_gtList));
		}

		std::unique_ptr<IGenotypeList> m_gtList;
		std::unique_ptr<IGenotyper> m_gter;
};

TEST_F(TestFixture, CanCreateObjects) {
	ASSERT_THAT(m_gtList.get(), Not(Eq(nullptr)));
	ASSERT_THAT(m_gter.get(), Not(Eq(nullptr)));
}

TEST_F(TestFixture, GenotypeProbabilityInDescendingOrder) {

	SamtoolsPileupEvidence evidence("cccCCAAaAAcAAAC$ACCCccaaCCC^!C");

	auto genotypes = m_gter->genotype(evidence);

	double currentProbability = 1.0;

	for(auto gt : genotypes) {
		ASSERT_THAT(std::get<1>(gt), Le(currentProbability));
		currentProbability = std::get<1>(gt);
	}
}

TEST_F(TestFixture, CorrectGenotypeRankedHighest1) {

	SamtoolsPileupEvidence evidence("cccCCAAaAAcAAAC$ACCCccaaCCC^!C");

	auto genotypes = m_gter->genotype(evidence);

	auto mostProbGt = std::get<0>(*genotypes.begin());

	ASSERT_THAT(mostProbGt.size(), Eq(2));
	
	ASSERT_THAT(mostProbGt.count(0), Eq(1));
	ASSERT_THAT(mostProbGt.count(1), Eq(1));
	ASSERT_THAT(mostProbGt.count(2), Eq(0));
	ASSERT_THAT(mostProbGt.count(3), Eq(0));
}

TEST_F(TestFixture, CorrectGenotypeRankedHighest2) {

	SamtoolsPileupEvidence evidence("TTTtTTTTTt");

	auto genotypes = m_gter->genotype(evidence);

	auto mostProbGt = std::get<0>(*genotypes.begin());

	ASSERT_THAT(mostProbGt.size(), Eq(2));
	
	ASSERT_THAT(mostProbGt.count(0), Eq(0));
	ASSERT_THAT(mostProbGt.count(1), Eq(0));
	ASSERT_THAT(mostProbGt.count(2), Eq(0));
	ASSERT_THAT(mostProbGt.count(3), Eq(2));
}

TEST_F(TestFixture, CorrectGenotypeRankedHighest3) {

	SamtoolsPileupEvidence evidence("CCCc^IC^!C");

	auto genotypes = m_gter->genotype(evidence);

	auto mostProbGt = std::get<0>(*genotypes.begin());

	ASSERT_THAT(mostProbGt.size(), Eq(2));
	
	ASSERT_THAT(mostProbGt.count(0), Eq(0));
	ASSERT_THAT(mostProbGt.count(1), Eq(2));
	ASSERT_THAT(mostProbGt.count(2), Eq(0));
	ASSERT_THAT(mostProbGt.count(3), Eq(0));
}
