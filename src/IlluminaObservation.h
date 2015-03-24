#ifndef YICPPLIB_ILLUMINAOBSERVATION_H_
#define YICPPLIB_ILLUMINAOBSERVATION_H_

#include "IObservation.h"

#include <memory>

namespace YiCppLib {
	/** Illumina Sequencing Read
	 *  The class models illumina sequencing error
	 */
	class IlluminaObservation : public IObservation {
		public:
			IlluminaObservation(size_t allele);
			~IlluminaObservation();
			IlluminaObservation(const IlluminaObservation& rhs);
			IlluminaObservation& operator=(const IlluminaObservation& rhs);
			IlluminaObservation(IlluminaObservation&& rhs);
			IlluminaObservation& operator=(IlluminaObservation&& rhs);

			virtual size_t allele() const noexcept override;
			virtual double quality() const noexcept override;

		private:
			struct Impl;
			std::unique_ptr<struct Impl> m_pImpl;
	};
}

#endif
