#pragma once

namespace BF
{
	enum class FileLocation
	{
		Invalid,

		MappedVirtual, // Used 'VirtalAlloc()' / 'mmap()'
		MappedFromDisk, // Used 'FileView()' / 'fmap()'
		CachedFromDisk, // When the file is cached into an internal buffer
		Linked // Used existing file with 'fopen()'
	};
}