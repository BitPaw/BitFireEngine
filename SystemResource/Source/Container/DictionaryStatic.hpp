#pragma once

#include <cstddef>

namespace BF
{
	template <class Key, class Value, size_t FullSize>
	struct DictionaryStatic
	{
		private:
		Key KeyList[FullSize];
		Value ValueList[FullSize];
		size_t Size = FullSize;

		public:/*
		DictionaryStatic()
		{
			//KeyList = nullptr;
			//ValueList = nullptr;
			Size = 0;
		}*/

		Value* GetValue(Key key)
		{
			//return &_valueTree; // Found

			return nullptr; // NotFound
		}

		void Add(Key key, Value value)
		{
			//_keyTree = key;
			//_valueTree = value;

			return key;
		}

		void Resize(size_t size)
		{

		}

		void Remove(Key key)
		{
			//_dataTree.Remove(key);
		}

		bool ContainsKey(Key key)
		{
			return false;//_dataTree.count(key);
		}

		bool ContainsValue(Value value)
		{
			return false;
		}

		bool IsEmpty()
		{
			return false;
		}
	};
}