#include "StdAfx.h"
#include "Recorded.h"
#include "xmlhelp.h"
#include <cmath>


CRecorded::CRecorded(void)
{
	m_sampleRate = 44100;
	m_samplePeriod = 1.0 / 44100.0;
	m_duration = 0;
	m_beatDuration = 0;
	m_time = 0;
	LoadFile();
}

bool CRecorded::LoadFile(void)
{
	if(!m_waveFile.Open(".\\media\\shortskirtmet2.wav"))
		return FALSE;

	m_sampleRate = m_waveFile.SampleRate();
	m_samplePeriod = 1.0 / m_sampleRate;
	m_duration = m_waveFile.GetDuration();
   
	return TRUE;
}


CRecorded::~CRecorded(void)
{
}

void CRecorded::SetNote(CNote *note)
{
	CComPtr<IXMLDOMNode> node;
    note->Node()->get_firstChild(&node);

    // Loop over the list of attributes
    for( ; node != NULL; NextNode(node))
    {
        CComBSTR name;
		node->get_nodeName(&name);

		if(name == L"effect")
		{
			XmlLoadEffect(node);
		}
    }
}

void CRecorded::ProcessReadFrame(short *p_frame)
{
   m_waveFile.ReadFrame(p_frame);
}

void CRecorded::Start(void)
{
	m_time = 0;
	m_currentEffect = 0;
	m_waveFile.Rewind();
	m_fuzz = FALSE;
	m_dynamic = FALSE;
	m_scale = 0;
}

bool CRecorded::Generate(void)
{
	short temp[2];
	ProcessReadFrame(temp);


	while(m_currentEffect < (int)m_effects.size())
    {
        // Get a pointer to the current effect
        RecordedEffect *effect = &m_effects[m_currentEffect];

        // If the measure is in the future we can't play
        // this effect just yet.
        if(effect->measure > m_curMeasure)
            break;
        
        // If this is the current measure, but the
        // beat has not been reached, we can't play
        // this effect.
        if(effect->measure == m_curMeasure && effect->beat > m_curBeat)
            break;

        // Figure out which effect to apply
		if(effect->eName == L"both")
		{
			m_fuzz = TRUE;
			m_dynamic = TRUE;
			m_scale = effect->scale;
		}
		else if(effect->eName == L"dynamic")
		{
			m_fuzz = FALSE;
			m_dynamic = TRUE;
		}
		else if(effect->eName == L"fuzz")
		{
			m_fuzz = TRUE;
			m_dynamic = FALSE;
			m_scale = effect->scale;
		}
		else
		{
			m_fuzz = FALSE;
			m_dynamic = FALSE;
		}
		m_currentEffect++;
    }

	ProcessEffects(temp);

	m_frame[0] = double(temp[0]) / 32768.0;
	m_frame[1] = double(temp[1]) / 32768.0;
	m_time += GetSamplePeriod();
	return m_time < (m_duration - 0.01);
}

void CRecorded::ProcessEffects(short *p_frame)
{
	if(m_fuzz)
	{
		ProcessFuzz(p_frame);
	}
}

void CRecorded::ProcessFuzz(short *p_frame)
{
	for(int i = 32000; i > 0; i -= 1000 * m_scale)
	{
		if(p_frame[0] > i)
		{
			p_frame[0] = i;
			break;
		}
		else if(p_frame[0] < (-1)*i)
		{
			p_frame[0] = (-1)*i;
			break;
		}
	}

	for(int i = 32000; i > 0; i -= 1000 * m_scale)
	{
		if(p_frame[1] > i)
		{
			p_frame[1] = i;
			break;
		}
		else if(p_frame[1] < (-1)*i)
		{
			p_frame[1] = (-1)*i;
			break;
		}
	}
}

void CRecorded::XmlLoadEffect(IXMLDOMNode *xml)
{
	// Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    xml->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

	RecordedEffect temp;

	for(int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR attName;
		attrib->get_nodeName(&attName);

		// Get the value of the attribute.  A CComVariant is a variable
		// that can have any type. It loads the attribute value as a
		// string (UNICODE), but we can then change it to an integer 
		// (VT_I4) or double (VT_R8) using the ChangeType function 
		// and then read its integer or double value from a member variable.
		CComVariant value;
		attrib->get_nodeValue(&value);

		if(attName == L"effect")
		{
			temp.eName = value.bstrVal;
		}
		else if(attName == L"measure")
		{
			value.ChangeType(VT_I4);
			temp.measure = value.intVal - 1;
		}
		else if(attName == L"beat")
		{
			value.ChangeType(VT_R8);
			temp.beat = value.dblVal - 1;
		}
		else if(attName == L"scale")
		{
			value.ChangeType(VT_I4);
			temp.scale = value.intVal;
		}
	}

	m_effects.push_back(temp);
}
