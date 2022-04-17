#pragma once

#include "JPEGScanSelector.h"

namespace BF
{
	struct JPEGScanStart
	{
		public:
		unsigned char ScanSelectorSize;
		JPEGScanSelector ScanSelector[3];
		unsigned char SpectralSelectFrom;
		unsigned char SpectralSelectTo;
		unsigned char SuccessiveAproximation;

		JPEGScanStart();
	};
}