#pragma once

namespace BF
{
	template<class T>
	class LinkedListNode
	{
		public:
		T Element;
		LinkedListNode<T>* Next;

		LinkedListNode(T element);
		LinkedListNode(T element, LinkedListNode<T>* next);
	};

	template<class T>
	inline LinkedListNode<T>::LinkedListNode(T element)
	{
		Element = element;
		Next = nullptr;
	}

	template<class T>
	inline LinkedListNode<T>::LinkedListNode(T element, LinkedListNode<T>* next)
	{
		Element = element;
		Next = next;
	}
}