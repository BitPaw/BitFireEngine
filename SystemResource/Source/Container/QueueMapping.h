#pragma once

#include <stddef.h>
#include <File/File.h>

#define QueueMappingSize 4096

namespace BF
{
	struct QueueMapping : private File
	{
		private:
		size_t _offsetBytesUsed;
		size_t _elementConter;

		public:
		QueueMapping();

		void Allocate(const size_t sizeInBytes);

		bool Enqueue(const void* source, const size_t sizeInBytes);
		bool Dequeue(void* target, size_t sizeInBytes);
	};
}