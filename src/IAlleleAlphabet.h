#ifndef BAYESGENOTYPE_IALPHABETALLELE_H
#define BAYESGENOTYPE_IALPHABETALLELE_H

#include <stdexcept>

namespace YiCppLib {
	template<class T>
	class IAlleleAlphabet {
		public:
			virtual ~IAlleleAlphabet() {}
			virtual size_t count() const noexcept = 0;
			virtual T actual(size_t allele) const = 0;
	};

	namespace Exceptions {
		class InvalidAlleleException : public std::runtime_error {public: InvalidAlleleException(const char * msg) : std::runtime_error(msg) {}};
	}
}

#endif

