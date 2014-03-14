#pragma once
#include "audionode.h"

class CAudioProcessNode :
	public CAudioNode
{
public:
	CAudioProcessNode(void);

	virtual ~CAudioProcessNode(void);

	virtual void Process(double *, double *) = 0;
};

short Range(double d);

