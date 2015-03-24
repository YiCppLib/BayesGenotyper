#include <gmock/gmock.h>
#include "SamtoolsPileupEvidence.h"

using namespace YiCppLib;
using namespace ::testing;

class TestFixture : public Test {
	protected:
		TestFixture() : 
			evidence1(new SamtoolsPileupEvidence("TTTtTTTTTt")),
			evidence2(new SamtoolsPileupEvidence("CCCc^IC^!C")),
			evidence3(new SamtoolsPileupEvidence("cccCCAAaAAcAAAC$ACCCccaaCCC^!C"))
		{}

		std::unique_ptr<IEvidence> evidence1;
		std::unique_ptr<IEvidence> evidence2;
		std::unique_ptr<IEvidence> evidence3;
};

TEST_F(TestFixture, CanCreateObjects) {
	ASSERT_THAT(evidence1.get(), Not(Eq(nullptr)));
	ASSERT_THAT(evidence2.get(), Not(Eq(nullptr)));
	ASSERT_THAT(evidence3.get(), Not(Eq(nullptr)));
}

TEST_F(TestFixture, CanReturnProperCountForObsWithEvidence1) {
	auto obsA = evidence1->observationsForAllele(0);
	auto obsC = evidence1->observationsForAllele(1);
	auto obsG = evidence1->observationsForAllele(2);
	auto obsT = evidence1->observationsForAllele(3);

	ASSERT_THAT(obsA.size(), Eq(0));
	ASSERT_THAT(obsC.size(), Eq(0));
	ASSERT_THAT(obsG.size(), Eq(0));
	ASSERT_THAT(obsT.size(), Eq(10));
}

TEST_F(TestFixture, CanReturnProperCountForObsWithEvidence2) {
	auto obsA = evidence2->observationsForAllele(0);
	auto obsC = evidence2->observationsForAllele(1);
	auto obsG = evidence2->observationsForAllele(2);
	auto obsT = evidence2->observationsForAllele(3);

	ASSERT_THAT(obsA.size(), Eq(0));
	ASSERT_THAT(obsC.size(), Eq(6));
	ASSERT_THAT(obsG.size(), Eq(0));
	ASSERT_THAT(obsT.size(), Eq(0));
}

TEST_F(TestFixture, CanReturnProperCountForObsWithEvidence3) {
	auto obsA = evidence3->observationsForAllele(0);
	auto obsC = evidence3->observationsForAllele(1);
	auto obsG = evidence3->observationsForAllele(2);
	auto obsT = evidence3->observationsForAllele(3);

	ASSERT_THAT(obsA.size(), Eq(11));
	ASSERT_THAT(obsC.size(), Eq(16));
	ASSERT_THAT(obsG.size(), Eq(0));
	ASSERT_THAT(obsT.size(), Eq(0));
}

TEST_F(TestFixture, CanReturnProperObsWithEvidence1) {
	auto obsT = evidence1->observationsForAllele(3);
	for(auto obs : obsT) {
		ASSERT_THAT(obs->allele(), Eq(3));
		ASSERT_THAT(obs->quality(), DoubleEq(0.9));
	}
}
