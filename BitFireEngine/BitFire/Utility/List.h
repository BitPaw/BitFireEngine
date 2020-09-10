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

		void Sort();

		// [A or B] Merges two List together (Addition)[OR]
		static List<T> Merge(List<T> listA, List<T> listB);

		// [A without B] Differentiate two lists. (Substraction)
		static List<T> Differentiate(List<T> listA, List<T> listB);
				
		// [A and B] Intersect two lists. [AND]
		static List<T> Intersect(List<T> listA, List<T> listB);

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

	template<class T>
	inline void List<T>::Sort()
	{
		// Do sorting stuff
	}

	template<class T>
	inline List<T> List<T>::Merge(List<T> listA, List<T> listB)
	{
		List<T> mergedList;		
		unsigned int listALength = listA.Size.Value;
		unsigned int listBLength = listB.Size.Value;
		unsigned int listMaxSize = listALength + listBLength;
		unsigned int newSize = 0;

		unsigned int mergedListindex = 0;

		unsigned int currentDublicatIndexPosition = 0;
		List<unsigned int> dublicatIndexList;// (listMaxSize)

		for (unsigned int indexA = 0; indexA < listALength; indexA++) // Go tru every AList
		{
			for (unsigned int indexB = 0; indexB < listBLength; indexB++) // Go tru every AList
			{
				bool isDifferent = listA[indexA] != listB[indexB];

				if (isDifferent)
				{
					dublicatIndexList[currentDublicatIndexPosition++] = indexB;

					newSize++;
				}
			}
		}

		mergedList.ReSize(newSize);		

		for (unsigned int indexA = 0; indexA < listALength; indexA++) 
		{
			for (unsigned int indexB = 0; indexB < listBLength; indexB++) 
			{
				bool skip = false;

				for (unsigned int i = 0; i < currentDublicatIndexPosition; i++)
				{
					skip = dublicatIndexList[i] == indexB;
				}

				if (!skip)
				{
					//mergedList[mergedListindex++].
				}
			}
		}

		return mergedList;
	}

	template<class T>
	inline List<T> List<T>::Differentiate(List<T> listA, List<T> listB)
	{
		return List<T>();
	}

	template<class T>
	inline List<T> List<T>::Intersect(List<T> listA, List<T> listB)
	{
		return List<T>();
	}
}