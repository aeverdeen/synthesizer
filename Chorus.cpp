#include "StdAfx.h"
#include "Chorus.h"
#include <cmath>


CChorus::CChorus(void)
{
	m_queuesize = (44100 + 1) * 2;
	m_time = 0;
	m_rloc = 0;
	m_queue.resize(m_queuesize);
	m_numVoices = 2;
	m_voiceAmp =  0.5;
}


CChorus::~CChorus(void)
{
}

void CChorus::Start()
{
	m_queue.resize(m_queuesize);
}

bool CChorus::Generate()
{
	return false;
}

void CChorus::Process(double * inframe, double * outframe)
{
	double mediandelay = 25./1000;
	double delayvariance = 5./1000;
	double delayrate[] = {0.3, 0.5, 0.15};

	m_queue[m_rloc] = inframe[0];
	m_queue[m_rloc+1] = inframe[1];

	double delayseconds;
	int delayframe;

	for(int i = 0; i < m_numVoices; i++)
	{
		delayseconds = mediandelay + delayvariance * sin(2 * PI * m_time * delayrate[i]);
		delayframe = (int)(delayseconds * m_sampleRate); 

		outframe[0] += m_voiceAmp * m_queue[(m_rloc - delayframe * 2 + m_queuesize) % m_queuesize] ;
		outframe[1] += m_voiceAmp * m_queue[(m_rloc - delayframe * 2 + m_queuesize + 1) % m_queuesize];
	}

	m_rloc = (m_rloc + 2) % m_queuesize;
	m_time += 1./m_sampleRate;
}


