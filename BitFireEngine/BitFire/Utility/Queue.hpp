#pragma once

namespace BF
{
	template <class T>
	class Queue
	{
		private:
		T* _data;


		public:
		void Add(T element);

		/**
			Get the next value and deletes it.
		*/
		T GetNext();
	};

	template<class T>
	inline void Queue<T>::Add(T element)
	{
	}
	template<class T>
	inline T Queue<T>::GetNext()
	{
		return T();
	}
}