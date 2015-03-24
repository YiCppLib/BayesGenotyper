#include "SamtoolsPileupEvidence.h"
#include "IlluminaObservation.h"

#include <vector>
#include <map>

using namespace YiCppLib;

struct SamtoolsPileupEvidence::Impl {
	const std::string pileupStr;
	std::map<size_t, std::vector<IObservation *>> observations;

	Impl(const std::string& pstr) : pileupStr(pstr) {}

	void incrementEvidenceForAllele(size_t allele) {
		if(observations.find(allele) == observations.end()) {
			observations[allele] = std::vector<IObservation *>();
		}

		observations[allele].push_back(new IlluminaObservation(allele));
	}

};

SamtoolsPileupEvidence::SamtoolsPileupEvidence(const std::string& pileupStr) :
	m_pImpl(new struct Impl(pileupStr))
{
	size_t skips = 0;
	char refChar = 'N';

	for(char symbol : m_pImpl->pileupStr) {

		if(skips != 0) {
			skips--;
			continue;
		}

		if(symbol == '.' || symbol == ',') symbol = refChar;

		switch(symbol) {
			case 'A':
			case 'a':
				m_pImpl->incrementEvidenceForAllele(0);
				break;
			case 'C':
			case 'c':
				m_pImpl->incrementEvidenceForAllele(1);
				break;
			case 'G':
			case 'g':
				m_pImpl->incrementEvidenceForAllele(2);
				break;
			case 'T':
			case 't':
				m_pImpl->incrementEvidenceForAllele(3);
				break;
			default:
				break;
		}
	}
}

SamtoolsPileupEvidence::SamtoolsPileupEvidence(const SamtoolsPileupEvidence& rhs) :
	m_pImpl(new struct Impl(*rhs.m_pImpl))
{
}

SamtoolsPileupEvidence::SamtoolsPileupEvidence(SamtoolsPileupEvidence&& rhs) = default;
SamtoolsPileupEvidence& SamtoolsPileupEvidence::operator=(SamtoolsPileupEvidence&& rhs) = default;
SamtoolsPileupEvidence::~SamtoolsPileupEvidence() = default;

std::vector<const IObservation*> SamtoolsPileupEvidence::observationsForAllele(size_t allele) const noexcept {
	static std::vector<const IObservation*> emptyResult;

	if(m_pImpl->observations.find(allele) != m_pImpl->observations.end()) {
		std::vector<const IObservation*> result;
		for(IObservation * obs : m_pImpl->observations[allele])
			result.push_back(obs);
		return result;
	}

	return emptyResult;
}

