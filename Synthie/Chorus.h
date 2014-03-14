#pragma once
#include "audioprocessnode.h"
#include "Note.h"
#include <vector>


class CChorus :
	public CAudioProcessNode
{

protected:
	std::vector<double> m_queue;
	int m_rloc;
	int m_queuesize;
	double m_time;
	wstring m_freq;
	double m_duration;

	int m_numVoices;
	double m_voiceAmp;
	//CNote m_note;
	wstring m_which;


public:
	CChorus(void);
	virtual ~CChorus(void);

	virtual void Start();
	virtual bool Generate();
	virtual void Process(double * , double *);
	virtual void SetNote(CNote * note);
	void SetWhich(wstring w){m_which = w ; }
	void SetFreq(wstring x) {m_freq = x;}
	void SetDuration(double d) {m_duration = d;}
	
};

