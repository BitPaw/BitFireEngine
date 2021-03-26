#pragma once

#include <malloc.h>

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
			DeleteAll();
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

		void ReSize(unsigned int size)
		{
			ReSize(size, false);
		}

		void ReSize(unsigned int size, bool copyOldContent)
		{
			T* oldData = _content;
			int oldSize = _size;

			if (_size == size || size == 0)
			{
				return; // Do nothing
			}

			//---[Create new DataAraay]---
			_content = new T[size];
			_size = size;
			//----------------------------

			if (copyOldContent)
			{
				for (int i = 0; i < oldSize && i < size; i++)
				{
					//_content[i] = oldData[i];
				}

				delete[] oldData;
			}						
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
				_size = 0;
				delete[] _content;
				_content = nullptr;			
			}
		}

		T& operator[](unsigned int value)
		{
			return _content[value];
		}
	};
}