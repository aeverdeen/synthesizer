#pragma once
#include "waveinstrument.h"
#include <vector>

class CWaveInstrumentFactory :

	public CWaveInstrument
{
public:
	CWaveInstrumentFactory(void);
	virtual ~CWaveInstrumentFactory(void);
	void SetNote(CNote *note);
    CWaveInstrument *CreateInstrument();
	virtual bool LoadFile(const char *filename);

private:
    std::vector<short> m_wave;
};

