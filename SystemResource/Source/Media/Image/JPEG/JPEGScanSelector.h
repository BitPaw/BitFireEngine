#pragma once

namespace BF
{
	struct JPEGScanSelector
	{
		public:
		unsigned char Selector;
		unsigned char DC;
		unsigned char ACTable;

		JPEGScanSelector();
	};
}