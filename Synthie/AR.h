#pragma once
#include "audionode.h"


class CToneInstrument;
class CAR :
	public CAudioNode
{
public:
	CAR(void);
	virtual ~CAR(void);

	void SetSource(CAudioNode *source) {m_source = source;}
	void SetDuration(double d) {m_duration = d;}
	void SetToneInstrument(CToneInstrument *tone) {m_toneInstr = tone;}

	virtual void Start();
	virtual bool Generate();

	double Frame(int i);

private:
	CAudioNode *m_source;
	CToneInstrument *m_toneInstr;

	double m_attack;
	double m_release;
	double m_duration;
	double m_durationInTime;
	double m_time;
};

