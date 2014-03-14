#include "StdAfx.h"
#include "Delay.h"


CDelay::CDelay(void)
{
}


CDelay::~CDelay(void)
{
}

void CDelay::Start()  
{
	m_writequeue.clear();
	m_rloc = 0;
	m_steps = 5; 
	m_queuesize = (int)((44100+1)*2*m_steps); 
	m_delayseconds = 1;
	m_dry = 0.8;
	m_wet = 0.4;

	m_writequeue.resize(m_queuesize);  
}

bool CDelay::Generate()  
{
	return false;
}

void CDelay::Process(double *inframe, double *outframe)
{
	m_writequeue[m_rloc] = inframe[0];
	m_writequeue[m_rloc+1] = inframe[1];  

	int delayframe = (int)(m_delayseconds * m_sampleRate);

	for (int i = 1; i <= m_steps; i++)
	{
		outframe[0] += m_wet/i * m_writequeue[(m_rloc - (delayframe * 2 * i) + m_queuesize) % m_queuesize];
		outframe[1] += m_wet/i * m_writequeue[((m_rloc+1) - (delayframe * 2 * i) + m_queuesize) % m_queuesize];
	}

	m_rloc = (m_rloc + 2) % m_queuesize;
}