#pragma once

#include "LinkedList.hpp"

namespace BF
{
	template <class T>
	class Queue
	{
		private:
		LinkedList<T> _objectQueue;


		public:
		void Add(T element)
		{
			_objectQueue.Add(element);
		}

		unsigned int Size()
		{
			return _objectQueue.Size();
		}

		bool IsEmpty()
		{
			return Size() == 0;
		}


		/*
		Gets the Next object in this queue and removes it from the list.
		*/
		T GetNext()
		{
			LinkedListNode<T>* object = _objectQueue.GetFirst();
			T queueedobject = object->Element;

			_objectQueue.RemoveFirst();

			return queueedobject;
		}
	};
}