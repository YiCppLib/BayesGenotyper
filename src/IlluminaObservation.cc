#include "IlluminaObservation.h"

using namespace YiCppLib;

struct YiCppLib::IlluminaObservation::Impl {
	size_t allele;
};

IlluminaObservation::IlluminaObservation(size_t allele) : 
	m_pImpl(new struct Impl()) 
{
	m_pImpl->allele = allele;
}

IlluminaObservation::IlluminaObservation(const IlluminaObservation& rhs) :
	m_pImpl(new struct Impl(*rhs.m_pImpl)) 
{}

IlluminaObservation& IlluminaObservation::operator=(const IlluminaObservation& rhs) {
	if(this != &rhs) {
		*m_pImpl = *rhs.m_pImpl;
	}
	return *this;
}

IlluminaObservation::~IlluminaObservation() = default;
IlluminaObservation::IlluminaObservation(IlluminaObservation&& rhs) = default;
IlluminaObservation& IlluminaObservation::operator=(IlluminaObservation&& rhs) = default;

size_t IlluminaObservation::allele() const noexcept {
	return m_pImpl->allele;
}

double IlluminaObservation::quality() const noexcept {
	return 0.9;
}

