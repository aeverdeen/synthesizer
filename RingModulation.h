#pragma once
#include "audioprocessnode.h"
class CRingModulation :
	public CAudioProcessNode
{
protected:
	double m_frequency;
	double m_time;
	double m_amplitude;
	double m_gain;

public:
	CRingModulation(void);
	virtual ~CRingModulation(void);

	virtual void Start();
	virtual bool Generate();
	virtual void Process(double *, double *);

	void setFreq(double f) { m_frequency = f; }
	void setModAmp(double a) { m_amplitude = a; }
	void setOutputGain(double g) { m_gain = g; }
};

