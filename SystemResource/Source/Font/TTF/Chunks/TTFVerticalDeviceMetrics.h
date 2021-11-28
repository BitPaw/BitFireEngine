#pragma once

namespace BF
{
	struct TTFVerticalDeviceMetrics
	{
		public:
		unsigned short Version; // Version number(0 or 1).
		unsigned short numRecs; // Number of VDMX groups present
		unsigned short numRatios; // Number of aspect ratio groupings
		//	RatioRange 	ratRange[numRatios];// 	Ratio record array.
		//Offset16 	vdmxGroupOffsets[numRatios];// 	Offset from start of this table to the VDMXGroup table for a corresponding RatioRange record.
	}; 
}