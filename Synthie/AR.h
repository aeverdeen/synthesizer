#pragma once
#include "audionode.h"


class CToneInstrument;
class CWaveInstrumentB;
class CAR :
	public CAudioNode
{
public:
	CAR(void);
	virtual ~CAR(void);

	void SetSource(CAudioNode *source) {m_source = source;}
	void SetDuration(double d) {m_duration = d;}
	void SetToneInstrument(CToneInstrument *tone) {m_toneInstr = tone;}
	void SetWaveInstrument(CWaveInstrumentB *wave) {m_waveInstr = wave;}
	void SetAttack(double a) {m_attack = a;}
	void SetRelease(double r) {m_release = r;}
	void SetDecay(double D) {m_decay = D;}
	void SetSustain(double s) {m_sustain = s;}
	virtual void Start();
	virtual bool Generate();

	double Frame(int i);

private:
	CAudioNode *m_source;
	CToneInstrument *m_toneInstr;
	CWaveInstrumentB *m_waveInstr;

	double m_attack;
	double m_release;
	double m_decay;
	double m_sustain;
	double m_duration;
	double m_durationInTime;
	double m_time;
	double m_amp;
};

