#pragma once

namespace BF
{
	template<class T>
	class RingBuffer
	{
	public:
		T* _data;
		unsigned int _size;
		unsigned int _currentIndex;

		RingBuffer(unsigned int size)
		{
			_data = new T[size];
			_size = size;

			memset(_data,0, sizeof(T)* _size);
		}

		void Push(T& element)
		{
			_data[_currentIndex++] = element;

			_currentIndex %= _size;
		}

		unsigned int IndexGet()
		{
			return _currentIndex;
		}

		void IndexSet(unsigned int index)
		{
			_currentIndex = index < _size ? index : _size - 1;
		}

		void Copy(unsigned int distance, unsigned int length, RingBuffer<T>& bufferB)
		{
			if (length < 0 || distance < 1 || distance > _size)
			{
				throw "IllegalArgumentException";
			}

			int readIndex = (_currentIndex - distance + _size) % _size;

			if (readIndex < 0 || readIndex >= _size)
			{
				throw "AssertionError";
			}

			for (int i = 0; i < length; i++)
			{
				T& b = _data[readIndex];

				readIndex = (readIndex + 1) % _size;

				bufferB.Push(b);
				Push(b);
			}
		}
	};
}