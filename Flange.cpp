#include "StdAfx.h"
#include "Flange.h"


CFlange::CFlange(void)
{
	m_queuesize = (44100 + 1) * 2;
	m_time = 0;
	m_steps = 3;
	m_rloc = 0;
	m_dry = 1;
	m_wet = .4;
	m_queue.resize(m_queuesize);
}


CFlange::~CFlange(void)
{
}

void CFlange::Start()
{
	m_queue.resize(m_queuesize);
}

bool CFlange::Generate()
{
	return false;
}

void CFlange::Process(double * inframe, double * outframe)
{
	double mediandelay = .006;
	double delayvariance = .004;
	double delayrate = .25;

	m_queue[m_rloc] = inframe[0];
	m_queue[m_rloc+1] = inframe[1];

	double delayseconds;
	int delayframe;

	for(int i = 0; i <= m_steps; i++)
	{
		delayseconds = mediandelay + delayvariance * sin(2 * PI * m_time * delayrate);
		delayframe = (int)(delayseconds * m_sampleRate);

		outframe[0] += m_queue[(m_rloc - delayframe * 2 + m_queuesize) % m_queuesize] ;
		outframe[1] += m_queue[(m_rloc - delayframe * 2 + m_queuesize + 1) % m_queuesize];
	}




