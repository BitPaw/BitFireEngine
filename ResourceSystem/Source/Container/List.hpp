#pragma once

#include "../../../MemoryManager/Memory.h"

namespace BF
{
	template <class T>
	class List
	{
		private:
		T* _content;
		unsigned int _size;

		public:
		List()
		{
			_content = nullptr;
			_size = 0;
		}

		List(const unsigned int size)
		{	
			ReSize(size);
		}

		~List()
		{
			if (_content != nullptr)
			{
				delete[] _content;
			}
		}

		bool IsEmpty()
		{
			return Size() == 0;
		}

		unsigned int Size()
		{
			return _size;
		}

		unsigned int SizeInBytes()
		{
			return _size * sizeof(T);
		}

		T* SwapBuffer(T* newBuffer, unsigned int size)
		{
			T* oldBuffer = _content;

			_content = newBuffer;
			_size = size;

			return oldBuffer;
		}

		void ReSize(unsigned int size)
		{
			ReSize(size, false);
		}

		void ReSize(unsigned int size, bool copyOldContent)
		{
			T* oldData = _content;
			int oldSize = _size;
			bool reallocate = true;// oldSize < size || (oldSize - size) > 128;
			// 200 < 100 && 200 - 128 > 100

			if (!reallocate)
			{
				return; // Cancel if the reallocation is to wasteful
			}

			if (_size == size || size == 0)
			{
				return; // Do nothing
			}

			//---[Create new DataAraay]---
			_content = (T*)MemoryResize(_content, size * sizeof(T));
			_size = size;

			for (unsigned int i = 0; i < _size; i++)
			{
				_content[i] = T();
			}
			//----------------------------					
		}

		/*
		Add an Element to the List.
		Warning: This will cause an allocation.
		Warning: Element will be copyed.
		*/
		void Add(T element)
		{
			ReSize(_size + 1);
		}

		// Delete all elements
		void DeleteAll()
		{
			if (_content != nullptr && _size != 0)
			{			
				delete[] _content; // Todo

				_size = 0;
				_content = nullptr;			
			}
		}

		inline T& operator[](unsigned int value)
		{
			return _content[value];
		}
	};
}