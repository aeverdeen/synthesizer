#pragma once
#include "WaveInstrumentB.h"
#include <vector>

class CWaveInstrumentFactoryB
{
public:
    CWaveInstrumentFactoryB(void);
    ~CWaveInstrumentFactoryB(void);

    void SetNote(CNote *note);
    CWaveInstrumentB *CreateInstrument();
	bool CWaveInstrumentFactoryB::LoadFile(const char *filename);

private:
    std::vector<short> m_wave;
};