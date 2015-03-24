#include <gmock/gmock.h>
#include "IAlleleAlphabet.h"
#include "SingleNtAlleleAlphabet.h"
#include "IGenotypeList.h"
#include "PloidyMultisetGenotypeList.h"
#include <set>

using namespace YiCppLib;
using namespace ::testing;

class TestFixture : public Test {
	protected:
		TestFixture() : alleles(nullptr), gtList(nullptr) {
			alleles = std::dynamic_pointer_cast<IAlleleAlphabet<char>>(
					std::make_shared<SingleNtAlleleAlphabet>()
					);

			gtList = std::dynamic_pointer_cast<IGenotypeList>(
					std::make_shared<PloidyMultisetGenotypeList>(alleles->count(), 2)
					);
		}

		std::shared_ptr<IAlleleAlphabet<char>> alleles;
		std::shared_ptr<IGenotypeList> gtList;

};

TEST_F(TestFixture, CanCreateObject) {
	ASSERT_THAT(alleles.get(), Not(Eq(nullptr)));
	ASSERT_THAT(gtList.get(), Not(Eq(nullptr)));
}

TEST_F(TestFixture, HasProperNumberOfGenotypes) {
	size_t count = 0;
	for(auto i = gtList->cbegin(); i != gtList->cend(); i++) count++;
	ASSERT_THAT(count, Eq(10));
}

TEST_F(TestFixture, CanReturnProperGenotypes) {
	std::vector<std::string> expectedGenotypes;

	expectedGenotypes.push_back("AA");
	expectedGenotypes.push_back("AC");
	expectedGenotypes.push_back("AG");
	expectedGenotypes.push_back("AT");
	expectedGenotypes.push_back("CC");
	expectedGenotypes.push_back("CG");
	expectedGenotypes.push_back("CT");
	expectedGenotypes.push_back("GG");
	expectedGenotypes.push_back("GT");
	expectedGenotypes.push_back("TT");

	for(auto i = gtList->cbegin(); i != gtList->cend(); i++) {
		std::string gt;
		std::multiset<int> ordered_gt(i->cbegin(), i->cend());
		for(auto j = ordered_gt.cbegin(); j != ordered_gt.cend(); j++)
			gt = gt + alleles->actual(*j);

		std::cerr<<"Locating genotype "<<gt<<std::endl;

		ASSERT_THAT(std::find(expectedGenotypes.cbegin(), expectedGenotypes.cend(), gt), Not(Eq(expectedGenotypes.cend())));
	}

}

TEST(TestPloidyMultisetGenotypeList, ThrowProperExceptionWithInvalidPloidy) {
	ASSERT_THROW(auto follyObj = std::make_shared<PloidyMultisetGenotypeList>(4, 0), std::shared_ptr<Exceptions::InvalidPloidy>);
	ASSERT_THROW(auto follyObj = std::make_shared<PloidyMultisetGenotypeList>(0, 2), std::shared_ptr<Exceptions::InvalidAlphabetSize>);
	ASSERT_ANY_THROW(auto follyObj = std::make_shared<PloidyMultisetGenotypeList>(0, 0));

}
