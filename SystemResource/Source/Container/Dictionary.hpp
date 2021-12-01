#pragma once

#include <stdlib.h>

namespace BF
{
	template <class Key, class Value>
	struct Dictionary
	{
		private:
		Key* KeyList;
		Value* ValueList;
		size_t SizeUsed;
		size_t SizeAllocated;

		public:
		Dictionary()
		{
			KeyList = nullptr;
			ValueList = nullptr;
			SizeUsed = 0;
			SizeAllocated = 0;
		}

		Value* GetValue(Key key)
		{
			for (size_t i = 0; i < SizeUsed; i++)
			{
				Key currentKey = KeyList[i];

				if (currentKey == key)
				{
					return &ValueList[i]; //  + i * sizeof(Value)
				}			
			}

			return nullptr;
		}

		void Add(Key key, Value value)
		{
			bool needMoreSpace = (SizeUsed + 1) > SizeAllocated;

			if (needMoreSpace)
			{
				const size_t riseAmount = 1;

				SizeAllocated += riseAmount;

				Key* newKeyAdress = (Key*)realloc(KeyList, SizeAllocated * sizeof(Key));

				if (!newKeyAdress)
				{
					// OutOfMemory
				}

				Value* newValueAdress = (Value*)realloc(ValueList, SizeAllocated * sizeof(Value));

				if (!newValueAdress)
				{
					// OutOfMemory
				}

				KeyList = newKeyAdress;
				ValueList = newValueAdress;				
			}

			KeyList[SizeUsed] = key;
			ValueList[SizeUsed] = value;

			++SizeUsed;
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

		unsigned int Size()
		{
			return 0;
		}

	};
}