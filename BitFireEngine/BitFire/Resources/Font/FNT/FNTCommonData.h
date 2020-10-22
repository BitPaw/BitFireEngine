#pragma once

namespace BF
{
	struct FNTCommonData
	{
	public:
		unsigned int LineHeight;
		unsigned int Base;
		unsigned int ScaleWidth;
		unsigned int ScaleHeight;
		unsigned int AmountOfPages;
		bool Packed;

		FNTCommonData();
	};
}