#pragma once

namespace BF
{
	struct GIFImageDescriptor
	{
		public:
		unsigned char Separator;
		unsigned short LeftPosition;
		unsigned short TopPosition;
		unsigned short Width;
		unsigned short Height;
		unsigned char LocalColorTableSize;
		unsigned char Reserved;
		bool SortFlag;
		bool InterlaceFlag;
		bool LocalColorTableFlag;
	};
}