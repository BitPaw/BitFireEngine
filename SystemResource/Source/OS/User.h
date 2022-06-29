#pragma once

namespace BF
{
	struct User
	{
		static bool Name(wchar_t* name, const size_t nameSizeMax, size_t& nameSizeWritten);
	};
}