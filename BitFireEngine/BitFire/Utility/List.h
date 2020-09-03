#pragma once

#include "ListSize.h"

namespace BF
{
	template <class T>
	class List
	{
	private:
		T* _content;

	public:
		unsigned int CurrentIndex;
		ListSize Size;

		List();
		List(const unsigned int size);

		~List();

		void ReSize();
		void ReSize(const unsigned int size);
				
		T& operator[](unsigned int value)
		{
			return _content[value];
		}		
	};

	template<class T>
	inline List<T>::List() : List<T>::List(0)
	{

	}

	template<class T>
	inline List<T>::List(const unsigned int size)
	{		
		CurrentIndex = 0;
		Size.Value = size;
		Size.Value = size * sizeof(T);

		if (size == 0)
		{
			_content = nullptr;
		}
		else
		{
			List<T>::ReSize(size);
		}
	}

	template<class T>
	inline List<T>::~List()
	{
		if (Size.Value > 0)
		{
			// Just to test, enable this sometime!

			//delete[] _content;
			//_content = nullptr;
		}	
	}

	template<class T>
	inline void List<T>::ReSize()
	{
		ReSize(Size.Value);
	}

	template<class T>
	inline void List<T>::ReSize(const unsigned int size)
	{
		Size.Value = size;
		Size.ValueInBytes = size * sizeof(T);

		_content = new T[size];
	}
}