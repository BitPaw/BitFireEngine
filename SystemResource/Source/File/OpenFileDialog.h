#pragma once

namespace BF
{
	class OpenFileDialog
	{
		public:
		static bool Open(char* filePathOutput);
		static bool Open(wchar_t* filePathOutput);
	};
}