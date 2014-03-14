#pragma once
#include "Instrument.h"
#include "WavePlayerB.h"
#include "audio/DirSoundSource.h"
#include "AR.h"


class CWaveInstrumentB :
    public CInstrument
{
public:
    CWaveInstrumentB(void);
    ~CWaveInstrumentB(void);

    virtual void Start();
    virtual bool Generate();
    virtual void SetNote(CNote *note);
	void SetDuration(double d) {m_duration = d;}

    CWavePlayerB *GetPlayer() {return &m_wavePlayer;}

private:
    CWavePlayerB m_wavePlayer;
	CAR m_ar;
	double m_duration;
	double m_time;
	double m_durationInTime;
};