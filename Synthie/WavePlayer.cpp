#include "stdafx.h"
#include "WavePlayer.h"


CWavePlayer::CWavePlayer(void)
{
	    m_samples = NULL;
    m_numsamples = 0;
}


CWavePlayer::~CWavePlayer(void)
{
}
void CWavePlayer::Start()
{
    m_position = 0;
	m_time = 0;
    m_count = 0;
}

bool CWavePlayer::Generate()
{
	//int p = 0.3; //trying to do glissando


    if(m_position < m_numsamples)
    {
   //     double wave = (m_samples[m_position] / 32768)*(1-m_position^p);  //trying to do glissando
	//	double wave2 = (m_samples[++m_position] / 32768)*(m_position^p); //trying to do glissando

	//	m_frame[0] = wave+wave2; //trying to do glissando
		m_frame[0] = (m_samples[m_position] / 32768.0);
        m_frame[1] = m_frame[0];
		m_position=m_position+2;


		//The following is trying to implement the Envelope Generation
		if (m_time<=0.05)
		{
			m_frame[0] = (m_samples[m_position] / 32768.0)*m_time;
			m_frame[1] = m_frame[0];

		}
		else if (m_time >=(0.15-0.05))
		{
			m_frame[0] = (m_samples[m_position] / 32768.0)*((-1)*m_time+0.15);
		  m_frame[1] = m_frame[0];
		}
		else
		{
			m_frame[0] = (m_samples[m_position] / 32768.0);
		    m_frame[1] = m_frame[0];
		}

		if (m_position> (m_numsamples/3)) //loop point
		{
		 if (m_count<1)
		{
			m_position = 0;
			m_count++;
		}
		}
			m_time += GetSamplePeriod();
		//m_position = m_position+2; //Pitch
        return true;
    }
    else
    {
        m_frame[1] = m_frame[0] = 0;
        return false;
    }
}
