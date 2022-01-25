#pragma once

namespace BF
{
	enum class FileCachingMode
	{    
        Default,
         
        Random,  // Access data in a random order.
        Sequential, // Data sequentially from lower offsets to higher offsets.      
        Temporary, // File will not be saves to drive.
        UseOnce, // Access the specified data once and then not reuse it again.

        

        // Windows only       
        WriteThrough,
        NoBuffering, // No OS Caching, direct to Harddrive if supprted     

        // UNIX only       
        NeedLater, // Data is not needed right now. "For later"[near future].        
        DontNeedNow // Data will not be cached. "I dont need it yet"  
	};

    static FileCachingMode ConvertFileCachingMode(unsigned int value);
    static unsigned int ConvertFileCachingMode(FileCachingMode fileCachingMode);
}