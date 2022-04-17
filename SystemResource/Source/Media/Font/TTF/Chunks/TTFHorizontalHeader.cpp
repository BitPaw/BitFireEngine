#include "TTFHorizontalHeader.h"

#include <stdio.h>

BF::TTFHorizontalHeader::TTFHorizontalHeader()
{
	Ascender = 0;
	Descender = 0;
	LineGap = 0;
	AdvanceWidthMaximum = 0;
	MinimumLeftSideBearing = 0;
	MinimumRightSideBearing = 0;
	MaximalExtendX = 0;
	CaretSlopeRise = 0;
	CaretSlopeRun = 0;
	Reserved[0] = 0;
	MetricDataFormat = 0;
	NumberOfHorizontalMetrics = 0;
}

void BF::TTFHorizontalHeader::Print(char* output)
{
	sprintf
	(
		output,
		"+--------------------------------------+\n"
		"| HorizontalHeader                     |\n"
		"+------------------------------+-------+\n"
		"| Version                      | %3i.%i |\n"
		"| Ascender                     | %5i |\n"
		"| Descender                    | %5i |\n"
		"| LineGap                      | %5i |\n"
		"| Advance Width Maximum        | %5i |\n"
		"| Minimum Left Side Bearing    | %5i |\n"
		"| Minimum Right Side Bearing   | %5i |\n"
		"| Maximal Extend X             | %5i |\n"
		"| Caret Slope Rise             | %5i |\n"
		"| Caret Slope Run              | %5i |\n"
		"| Metric Data Format           | %5i |\n"
		"| Number Of Horizontal Metrics | %5i |\n"
		"+------------------------------+-------+\n",
		Version.Major,
		Version.Minor,
		Ascender,
		Descender,
		LineGap,
		AdvanceWidthMaximum,
		MinimumLeftSideBearing,
		MinimumRightSideBearing,
		MaximalExtendX,
		CaretSlopeRise,
		CaretSlopeRun,
		MetricDataFormat,
		NumberOfHorizontalMetrics
	);
}