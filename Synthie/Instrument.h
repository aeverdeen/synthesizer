#pragma once
#include "audionode.h"
#include "Note.h"

class CInstrument :
	public CAudioNode
{
public:
	CInstrument(void);
	virtual ~CInstrument(void);

	virtual void SetNote(CNote *note) = 0;

	void SetMeasure(int measure) {m_curMeasure = measure;}
	void SetBeat(double beat) {m_curBeat = beat;}

protected:
	int m_curMeasure;
	double m_curBeat;
};

