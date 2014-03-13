#pragma once
#include "audioprocessnode.h"
#include <vector>

class CDelay :
	public CAudioProcessNode
{
protected:
	std::vector<double> m_writequeue;
	int m_rloc;
	int m_queuesize;
	double m_delayseconds;
	double m_dry;
	double m_wet;
	double m_steps;

public:
	CDelay(void);
	~CDelay(void);

	virtual void Start();
	virtual bool Generate();
	virtual void Process(double*, double*);

	virtual void setQueueSize(int size) { m_queuesize = size; m_writequeue.resize(size); }
	virtual void setDelaySeconds(double sec) { m_delayseconds = sec; }
	virtual void setDryWet(double d, double w) { m_dry = d; m_wet = w; }
	virtual void setSteps(double s) { m_steps = s; } 
};

