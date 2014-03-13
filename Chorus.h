#pragma once
#include "audioprocessnode.h"
#include <vector>


class CChorus :
	public CAudioProcessNode
{

protected:
	std::vector<double> m_queue;
	int m_rloc;
	int m_queuesize;
	double m_time;
	int m_numVoices;
	double m_voiceAmp;


public:
	CChorus(void);
	virtual ~CChorus(void);

	virtual void Start();
	virtual bool Generate();
	virtual void Process(double * , double *);
};

