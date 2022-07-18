#include "ResponseCache.h"

BF::ResponseCache::ResponseCache()
{
    _cache.MapToVirtualMemory(4096u, MemoryReadAndWrite);
}

ResponseID BF::ResponseCache::Register()
{
    static int counter = 0;
    const size_t invalidIndex = -1;

    counter++;

    _responseIDLookup.Add(counter, invalidIndex);

    return counter;
}

BF::ResponseCacheResult BF::ResponseCache::Fill(const ResponseID responseID, const void* data, const size_t dataSize)
{
    ResponseCacheEntry responseCacheEntry;

    // Is an entry there but has no data? return if not
    {
        const ResponseCacheResult findResult = Find(responseID, responseCacheEntry);
        const bool isWaiting = findResult == ResponseCacheResult::WaitingForResponse;

        if(!isWaiting)
        {
            return ResponseCacheResult::NotRegistered;
        }
    }

    // Add data
    {
        const size_t currentPosition = _cache.DataCursor;

         _cache.Write((unsigned long long)dataSize, EndianLittle);
        _cache.Write(data, dataSize);

        _responseIDLookup.Update(responseID, currentPosition);
    }

    return ResponseCacheResult::Success;
}

BF::ResponseCacheResult BF::ResponseCache::Find(const ResponseID responseID, ResponseCacheEntry& responseCacheEntry)
{
    // lokkuo
    const size_t* adressEntry = _responseIDLookup.Find(responseID);

    // is registerd?
    {
        const bool isRegistered = adressEntry;

        if(!isRegistered)
        {
            return ResponseCacheResult::NotRegistered;
        }
    }

    // is pointing to something?
    {
        const size_t entry = *adressEntry != -1;

        if(!entry)
        {
            return ResponseCacheResult::WaitingForResponse;
        }
    }

    {
        const size_t cursorOldPosition = _cache.DataCursor;

        _cache.DataCursor = *adressEntry;

        _cache.Read((unsigned long long&)responseCacheEntry.Length, EndianLittle);

        responseCacheEntry.Data = _cache.CursorCurrentAdress();

        _cache.DataCursor = cursorOldPosition;
    }

    return ResponseCacheResult::Answered;
}

void BF::ResponseCache::Remove(const ResponseID responseID)
{
    // remove from lookuo
    {
        _responseIDLookup.Remove(responseID);
    }

    // clear from cache
    {
        //_cache
    }
}
