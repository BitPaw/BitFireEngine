#pragma once

namespace BF
{
	enum class TTFVersionType
	{
		Invalid,

		Version1Dot0,
		Version2Dot0,
		Version2Dot5, 
		Version3Dot0
	};

	TTFVersionType ConvertVersionType(unsigned short major, unsigned short minor);
	void ConvertVersionType(unsigned short& major, unsigned short& minor, TTFVersionType versionType);
}