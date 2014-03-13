#include "StdAfx.h"
#include "Reverb.h"


CReverb::CReverb(void)
{
}


CReverb::~CReverb(void)
{
}

void CReverb::Start()  
{
	m_writequeue.clear();          
	m_rloc = 0;
	m_steps = 3;
	m_queuesize = (44100+1)*2;
	m_delayseconds = 0.075;
	m_dry = 1;
	m_wet = 0.4;

	m_writequeue.resize(m_queuesize);  
}

void CReverb::Process(double *inframe, double *outframe)
{
	int delayframe = (int)(m_delayseconds * m_sampleRate);

	for (int i = 1; i <= m_steps; i++)
	{
		outframe[0] += m_wet/i * m_writequeue[(m_rloc - (delayframe*i) + m_queuesize) % m_queuesize];
		outframe[1] += m_wet/i * m_writequeue[((m_rloc+1) - (delayframe*i) + m_queuesize) % m_queuesize];
	}

	m_writequeue[m_rloc] = outframe[0];
	m_writequeue[m_rloc] = outframe[1];

	m_rloc = (m_rloc + 2) % m_queuesize;
}
