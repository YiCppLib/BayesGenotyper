#include <gmock/gmock.h>
#include "IObservation.h"
#include "IlluminaObservation.h"

using namespace YiCppLib;
using namespace ::testing;

class TestFixture : public Test {
	protected:
		TestFixture() : observation(new IlluminaObservation(1)) {

		}

		std::unique_ptr<IObservation> observation;
};

TEST_F(TestFixture, CanCreateObject) {
	ASSERT_THAT(observation.get(), Not(Eq(nullptr)));
}

TEST_F(TestFixture, CanReturnAllele) {
	ASSERT_THAT(observation->allele(), Eq(1));
}

TEST_F(TestFixture, CanReturnQuality) {
	ASSERT_THAT(observation->quality(), DoubleEq(0.9));
}
