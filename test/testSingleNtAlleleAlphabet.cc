#include <gmock/gmock.h>
#include "SingleNtAlleleAlphabet.h"

#include <memory>

using namespace YiCppLib;
using namespace ::testing;


class AlphabetFixture : public Test {
	protected:
		AlphabetFixture() {
			alphabet = std::dynamic_pointer_cast<IAlleleAlphabet<char>>(std::make_shared<SingleNtAlleleAlphabet>());
		}

		~AlphabetFixture() {
		}

		std::shared_ptr<IAlleleAlphabet<char>> alphabet;
};

TEST_F(AlphabetFixture, CanCreateObject) {
	ASSERT_THAT(alphabet, Not(Eq(nullptr)));
}

TEST_F(AlphabetFixture, ReturnsRightAlleleCount) {
	ASSERT_THAT(alphabet->count(), Eq(4));
}

TEST_F(AlphabetFixture, ReturnsRightAllele) {
	ASSERT_THAT(alphabet->actual(0), Eq('A'));
	ASSERT_THAT(alphabet->actual(1), Eq('C'));
	ASSERT_THAT(alphabet->actual(2), Eq('G'));
	ASSERT_THAT(alphabet->actual(3), Eq('T'));
}

TEST_F(AlphabetFixture, CanHandleInvalidArgument) {
	ASSERT_THROW(alphabet->actual(4), std::shared_ptr<Exceptions::InvalidAllele>);
}
