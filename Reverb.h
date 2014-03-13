#pragma once
#include "delay.h"

class CReverb :
	public CDelay
{
public:
	CReverb(void);
	virtual ~CReverb(void);

	virtual void Start();
	virtual void Process(double *, double *);
};

