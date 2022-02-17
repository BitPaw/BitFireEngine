#pragma once

#include <Resource.h>

namespace BF
{
	struct ResourceAsyncLoadInfo
	{
		Resource* ResourceAdress;
		wchar_t FilePath[260];
	};
}