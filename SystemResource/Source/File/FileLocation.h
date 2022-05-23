#pragma once

namespace BF
{
	enum class FileLocation
	{
		Invalid,

		MappedVirtual, // Used 'VirtalAlloc()' / 'mmap()'
		MappedFromDisk, // Used 'FileView()' / 'fmap()'
		CachedFromDisk // Used existing file with 'fopen()'
	};
}