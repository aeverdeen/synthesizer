#pragma once
#include "instrument.h"
#include "WavePlayer.h"
#include "AR.h"

class Car;
class CWaveInstrument :
	public CInstrument
{
public:
	CWaveInstrument(void);
	virtual ~CWaveInstrument(void);

	    virtual void Start();
    virtual bool Generate();
    virtual void SetNote(CNote *note);

    CWavePlayer *GetPlayer() {return &m_wavePlayer;}
	//	CAR	m_ar;

private:
    CWavePlayer m_wavePlayer;
	double m_time;

};

