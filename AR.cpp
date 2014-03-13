#include "StdAfx.h"
#include "AR.h"
#include "ToneInstrument.h"

CAR::CAR(void)
{
	m_source = NULL;
	m_toneInstr = NULL;
	m_attack = 0.05;
	m_release = 0.05;
	m_duration = 0;
}


CAR::~CAR(void)
{
}

void CAR::Start()
{
	m_source->Start();
	m_time = 0;
}

bool CAR::Generate()
{
	m_source->Generate();

	m_durationInTime = m_duration * (1/(m_toneInstr->GetBpm()/60));

    // Update time
	m_time += GetSamplePeriod();

    // We return true until the time reaches the duration.
    return m_time < m_durationInTime;
}

double CAR::Frame(int i)
{
	if(m_time <= 0.05)
	{
		return m_source->Frame(i) * 20 * m_time;
	}
	else if(m_time >= m_durationInTime - 0.05)
	{
		return m_source->Frame(i) * ((-20)*m_time + 20*m_durationInTime);
	}
	else
	{
		return m_source->Frame(i);
	}
}