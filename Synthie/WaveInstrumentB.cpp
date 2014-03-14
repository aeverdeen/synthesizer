#include "StdAfx.h"
#include "WaveInstrumentB.h"




CWaveInstrumentB::CWaveInstrumentB(void)
{
	m_duration = 0.1;
	m_ar.SetWaveInstrument(this);

}

CWaveInstrumentB::~CWaveInstrumentB(void)
{
}


void CWaveInstrumentB::Start()
{
    m_wavePlayer.SetSampleRate(GetSampleRate());
    m_wavePlayer.Start();
	
	m_ar.SetSource(&m_wavePlayer);
	m_ar.SetSampleRate(GetSampleRate());
	m_ar.SetDuration(m_duration);
	m_ar.Start();

}


void CWaveInstrumentB::SetNote(CNote *note)
{
	// Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    note->Node()->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    // Loop over the list of attributes
    for(int i=0;  i<len;  i++)
    {
        // Get attribute i
        CComPtr<IXMLDOMNode> attrib;
        attributes->get_item(i, &attrib);

        // Get the name of the attribute
        CComBSTR name;
        attrib->get_nodeName(&name);

        CComVariant value;
        attrib->get_nodeValue(&value);

        if(name == "duration")
        {
            value.ChangeType(VT_R8);
            SetDuration(value.dblVal);
        }

        else if(name == "attack")
        {
            value.ChangeType(VT_R8);
            m_ar.SetAttack(value.dblVal);
        }
        else if(name == "release")
        {
            value.ChangeType(VT_R8);
            m_ar.SetRelease(value.dblVal);
        }
	    else if(name == "decay")
        {
            value.ChangeType(VT_R8);
            m_ar.SetDecay(value.dblVal);
        }
        else if(name == "sustain")
        {
            value.ChangeType(VT_R8);
            m_ar.SetSustain(value.dblVal);
        }
    }

}


bool CWaveInstrumentB::Generate()
{
    m_durationInTime = m_duration * (1/(m_bpmMaster/60));

	bool valid = m_ar.Generate();

	m_frame[0] = m_ar.Frame(0);
	m_frame[1] = m_ar.Frame(1);

	m_time += GetSamplePeriod();

	return valid;
}