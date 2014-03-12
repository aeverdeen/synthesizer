#pragma once
#include <vector>
#include <algorithm>
#include "Instrument.h"
#include "audio/wave.h"
#include "audio/DirSoundStream.h"
#include "audio/DirSoundSource.h"
#include "audio/WaveformBuffer.h"
class CRecorded :
	public CInstrument
{
public:

	enum EffectName {NONE, ONE, TWO, BOTH};

	struct RecordedEffect {

		bool operator<(const RecordedEffect &b)
		{
			if(measure < b.measure)
			{
				return TRUE;
			}
			if(b.measure > measure)
			{
				return FALSE;
			}
			if(measure == b.measure && beat < b.beat)
			{
				return TRUE;
			}
			return FALSE;
		}
		int measure;
		int scale;
		double beat;
		wstring eName; 
	} ;

	CRecorded(void);
	virtual ~CRecorded(void);

	virtual void SetNote(CNote *note);
	//void SetEffects(CNote

	virtual void Start();
	virtual bool Generate();

	void ProcessReadFrame(short *p_frame);
	void ProcessEffects(short *p_frame);
	void ProcessFuzz(short *p_frame);

	void XmlLoadEffect(IXMLDOMNode *xml);

	bool LoadFile();

private:
	CDirSoundSource m_waveFile; //The wavefile

	double m_duration; //Length of the sample
	double m_beatDuration; //Length of sample in beats
	double m_time; //Current time

	int m_currentEffect;
	bool m_fuzz; //These two booleans determine which effect is to be applied
	bool m_dynamic;
	int m_scale; // The scale of the fuzz effect

	std::vector<RecordedEffect> m_effects;
};

