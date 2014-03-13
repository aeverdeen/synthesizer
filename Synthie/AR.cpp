#include "StdAfx.h"
#include "AR.h"
#include "ToneInstrument.h"
#include "WaveInstrumentB.h"


CAR::CAR(void)
{
	//added envelope generation variables
	m_source = NULL;
	m_toneInstr = NULL;
	m_waveInstr = NULL;
	m_attack = 0.05;
	m_release = 0.05;
	m_sustain = .0;
	m_decay = .0;
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

	if(m_waveInstr == NULL)
	{
		m_durationInTime = m_duration * (1/(m_toneInstr->GetBpm()/60));
	}
	else
	{
		m_durationInTime = m_duration * (1/(m_waveInstr->GetBpm()/60));
	}
    // Update time
	m_time += GetSamplePeriod();

    // We return true until the time reaches the duration.
    return m_time < m_durationInTime;
}

double CAR::Frame(int i)
{
	//do envelope generation
	if(m_time <= m_attack)
	{
		m_amp = 2 * m_time;
		return m_source->Frame(i) * m_amp;
	}
	//release
	else if(m_time >= m_durationInTime - m_release)
	{
		m_amp = ((-2)*m_time + 2*m_durationInTime);
		return m_source->Frame(i) * m_amp;
	}
	//decay
	else if(m_time >= m_attack && m_time <= m_attack + m_decay  && m_decay > 0)
	{
		m_amp = ((-1)*m_time + 1*m_durationInTime);
		return m_source->Frame(i)* m_amp;
	}
	//sustain
	else if(m_sustain > 0)
	{
		return m_source->Frame(i) * m_amp;
	}
	else
	{
		return m_source->Frame(i);
	}
}