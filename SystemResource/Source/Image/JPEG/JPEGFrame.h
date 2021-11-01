#pragma once

#include "JPEGFrameComponent.h"

namespace BF
{
	struct JPEGFrame
	{
		unsigned short Precusion;
		unsigned short LineNb;
		unsigned char LineSamples;
		unsigned char ComponentListSize;
		JPEGFrameComponent ComponentList[3];
	};
}