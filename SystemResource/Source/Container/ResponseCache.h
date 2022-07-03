#pragma once

#include <Container/Dictionary.hpp>
#include <File/File.h>

#define ResponseID unsigned int

namespace BF
{
	enum class ResponseCacheResult
	{
		Invalid,

		Success,

		NotRegistered,

		WaitingForResponse,

		Answered		
	};

	struct ResponseCacheEntry
	{
		size_t Length;
		void* Data;
	};

	struct ResponseCache
	{
		private:
		Dictionary<ResponseID, size_t> _responseIDLookup;
		File _cache;

		public:

		ResponseCache();

		// I have rasponse i need to get later on.
		ResponseID Register();

		ResponseCacheResult Fill(const ResponseID responseID, const void* data, const size_t dataSize);

		// Find data if located, else it returns NULL.
		ResponseCacheResult Find(const ResponseID responseID, ResponseCacheEntry& responseCacheEntry);

		// Removes atatched data and the ID from lookup
		void Remove(const ResponseID responseID);
	};
}