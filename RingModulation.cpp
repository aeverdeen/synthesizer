#include "StdAfx.h"
#include "RingModulation.h"
#include <cmath>


CRingModulation::CRingModulation(void)
{
	m_time = 0;
	m_frequency = 440;
	m_amplitude = 0.7;
	m_gain = 0.7;
}


CRingModulation::~CRingModulation(void)
{
}

bool CRingModulation::Generate()  
{
	return false;
}

void CRingModulation::Start()  
{
	m_time = 0;
}

void CRingModulation::Process(double * inframe, double * outframe)
{
	double wave_sample = m_amplitude * sin(2 * PI * m_frequency * m_time);

	outframe[0] += m_gain * inframe[0] * wave_sample;
	outframe[1] += m_gain * inframe[1] * wave_sample;

	m_time += m_samplePeriod;
}
