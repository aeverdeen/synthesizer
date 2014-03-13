#pragma once
#include "audionode.h"
class CWavePlayerB :
	public CAudioNode
{
public:
	CWavePlayerB(void);
	~CWavePlayerB(void);

public:
    virtual void Start();
    virtual bool Generate();

    void SetSamples(short *s, int n) {m_samples = s; m_numsamples = n;}

private:
    short *m_samples;
    int    m_numsamples;
    int    m_position;
	int	   m_loops;  //how many times to loop
};

