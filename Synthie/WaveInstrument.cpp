#include "stdafx.h"
#include "WaveInstrument.h"





CWaveInstrument::CWaveInstrument(void)
{
}


CWaveInstrument::~CWaveInstrument(void)
{
}

void CWaveInstrument::Start()
{
    m_wavePlayer.SetSampleRate(GetSampleRate());
    m_wavePlayer.Start();
	//m_time = 0;      //Trying to use the CAR class to implement the attack and release functions we already have

	//m_ar.SetSource(&m_wavePlayer);      //Trying to use the CAR class to implement the attack and release functions we already have
  //  m_ar.SetSampleRate(GetSampleRate());      //Trying to use the CAR class to implement the attack and release functions we already have
  //  m_ar.Start();      //Trying to use the CAR class to implement the attack and release functions we already have
}


void CWaveInstrument::SetNote(CNote *note)
{
}


bool CWaveInstrument::Generate()
{
	//m_wavePlayer.Generate();      //Trying to use the CAR class to implement the attack and release functions we already have
  //  bool valid = m_ar.Generate();      //Trying to use the CAR class to implement the attack and release functions we already have
	 bool valid = m_wavePlayer.Generate();

	 m_frame[0] = m_wavePlayer.Frame(0);
	 m_frame[1] = m_wavePlayer.Frame(1);
   // m_frame[0] = m_ar.Frame(0);      //Trying to use the CAR class to implement the attack and release functions we already have
  //  m_frame[1] = m_ar.Frame(1);      //Trying to use the CAR class to implement the attack and release functions we already have
//	m_time += GetSamplePeriod();      //Trying to use the CAR class to implement the attack and release functions we already have

    return valid;
}