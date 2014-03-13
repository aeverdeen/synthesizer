#include "StdAfx.h"
#include "AudioProcessNode.h"


CAudioProcessNode::CAudioProcessNode(void)
{
}


CAudioProcessNode::~CAudioProcessNode(void)
{
}

short Range(double d)
{
	if(d < -32768)
		return -32768;
	else if(d > 32767)
		return 32767;

	return (short)d;
}
