#pragma once

#define SBPTextTypeInvalid '?'
#define SBPTextTypeNarrow 'A'
#define SBPTextTypeWide 'W'

namespace BF
{
	struct SBPText
	{
		public:
		unsigned char Type;
		
		union 
		{
			const void* Text;
			const char* TextA;
			const wchar_t* TextW;
		};

		SBPText();
		SBPText(const char* text);
		SBPText(const wchar_t* text);

		size_t SizeInBytes() const;
	};
}