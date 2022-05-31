#pragma once

#define SBPTextTypeInvalid '?'
#define SBPTextTypeNarrow 'A'
#define SBPTextTypeWide 'W'

namespace BF
{
	enum class SBPTextType : char
	{
		Invalid = SBPTextTypeInvalid,

		Narrow = SBPTextTypeNarrow, // Interpred text as char*
		Wide = SBPTextTypeWide // Interpret thext as wchar_t*
	};

	struct SBPText
	{
		public:
		SBPTextType Type;
		
		union 
		{
			const char* TextA;
			const wchar_t* TextW;
		};

		SBPText();
		SBPText(const char* text);
		SBPText(const wchar_t* text);

		size_t SizeInBytes() const;
	};
}