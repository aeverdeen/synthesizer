#include "StdAfx.h"
#include "WavePlayerB.h"

CWavePlayerB::CWavePlayerB(void)
{
    m_samples = NULL;
    m_numsamples = 0;
	m_loops = 0;
}

CWavePlayerB::~CWavePlayerB(void)
{
}

void CWavePlayerB::Start()
{
    m_position = 0;
}

bool CWavePlayerB::Generate()
{
    if(m_position < m_numsamples)
    {
		//loop  used to double pitch
		if(m_loops > 5)
		{
			m_position += 2;
		}
        m_frame[0] = m_samples[m_position++] / 32768.0;
        m_frame[1] = m_frame[0];
        //loop point
		if(m_position < m_numsamples-1)
		{
			if(m_loops < 5)
			{
				m_position = m_numsamples/2;
				m_loops++;
			}
		}
		return true;
	}
	else
    {
        m_frame[1] = m_frame[0] = 0;
        return false;
    }

}