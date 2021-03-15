#pragma once

#include "LinkedListNode.hpp"

namespace BF
{
	template <typename T>
	class LinkedList
	{
		private:
		LinkedListNode<T>* _firstNode;
		LinkedListNode<T>* _lastNode;
		unsigned int _size;

		LinkedListNode<T>* GetAt(unsigned int index);

		public:
		LinkedList();

		LinkedListNode<T>* operator[](unsigned int index);

		unsigned int Size();
		void Add(T element);

		LinkedListNode<T>* GetFirst();
		LinkedListNode<T>* GetLast();
		
		bool Contains(T element);



		void RemoveFirst();
		void RemoveAt(unsigned int index);
	};

	template<class T>
	inline LinkedListNode<T>* LinkedList<T>::GetAt(unsigned int index)
	{
		LinkedListNode<T>* currentNode = GetFirst();

		for (unsigned int i = 0; i < index; i++)
		{
			currentNode = currentNode->Next;
		}

		return currentNode;
	}

	template<class T>
	inline BF::LinkedList<T>::LinkedList()
	{
		_firstNode = nullptr;
		_lastNode = nullptr;
		_size = 0;
	}

	template<class T>
	inline LinkedListNode<T>* BF::LinkedList<T>::operator[](unsigned int index)
	{
		LinkedListNode<T>* currentNode = GetAt(index);

		return currentNode;
	}

	template<class T>
	inline BF::LinkedListNode<T>* BF::LinkedList<T>::GetFirst()
	{
		return _firstNode;
	}

	template<class T>
	inline BF::LinkedListNode<T>* BF::LinkedList<T>::GetLast()
	{
		return _lastNode;
	}

	template<class T>
	inline unsigned int BF::LinkedList<T>::Size()
	{
		return _size;
	}

	template<class T>
	inline void BF::LinkedList<T>::Add(T element)
	{
		LinkedListNode<T>* lastIndex = GetLast();
		LinkedListNode<T>* next = new LinkedListNode<T>(element);
		bool hasLast = lastIndex != nullptr;

		if (hasLast)
		{	
			lastIndex->Next = next;
		}
		else
		{
			_firstNode = next;		
		}	

		_lastNode = next;

		_size++;
	}

	template<class T>
	inline bool BF::LinkedList<T>::Contains(T element)
	{
		LinkedListNode<T>* currentElement = GetFirst();

		while (currentElement != nullptr)
		{
			bool isTarget = currentElement->Element == element;

			if (isTarget)
			{
				return true;
			}
			else
			{
				currentElement = currentElement->Next;
			}
		}

		return false;
	}

	template<class T>
	inline void LinkedList<T>::RemoveFirst()
	{
		RemoveAt(0);
	}

	template<class T>
	inline void LinkedList<T>::RemoveAt(unsigned int index)
	{
		LinkedListNode<T>* previous = nullptr;
		LinkedListNode<T>* target = nullptr;
		LinkedListNode<T>* next = nullptr;
		bool validPosition = index < _size;
		bool hasPrivousEntry = false;
		bool hasNextEnzty = false;

		if (!validPosition)
		{
			throw "Invalid size";
		}

		hasPrivousEntry = index > 0;
						
		target = GetAt(index);
		next = target->Next;

		hasNextEnzty = next != nullptr;


		if (hasPrivousEntry)
		{
			previous = GetAt(index-1);
			previous->Next = next;			
		}
		else
		{
			_firstNode = next;
		}	

		_size--;	

		delete target;
	}
}