#pragma once

#include "TTFVersion.h"

namespace BF
{
	struct TTFHorizontalHeader
	{
		public:
		TTFVersion Version;
		short Ascender;
		short Descender;
		short LineGap;
		unsigned short AdvanceWidthMaximum;
		short MinimumLeftSideBearing;
		short MinimumRightSideBearing;
		short MaximalExtendX;
		short CaretSlopeRise;
		short CaretSlopeRun;
		unsigned char Reserved[10];
		short MetricDataFormat;
		unsigned short NumberOfHorizontalMetrics;

		TTFHorizontalHeader();

		void Print(char* output);
	};
}