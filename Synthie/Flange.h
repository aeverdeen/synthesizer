#pragma once
#include "delay.h"

class CFlange :
	public CDelay
{
protected:
	std::vector<double> m_queue;
	int m_rloc;
	int m_queuesize;
	double m_time;
public:
	CFlange(void);
	virtual ~CFlange(void);


	virtual bool Generate();
	virtual void Start();
	virtual void Process(double *, double *);

};

