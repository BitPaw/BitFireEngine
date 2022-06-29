#pragma once

#include <cstdlib>
#include <cstddef>

#include <Hardware/Memory/Memory.h>

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

		~Dictionary()
		{
			delete[] KeyList;
			delete[] ValueList;
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

		void Add(const Key key, const Value value)
		{
			bool needMoreSpace = (SizeUsed + 1) > SizeAllocated;

			if (needMoreSpace)
			{
				const size_t riseAmount = 1;

				SizeAllocated += riseAmount;

				Key* newKeyAdress = Memory::Reallocate<Key>(KeyList, SizeAllocated);

				if (!newKeyAdress)
				{
					// OutOfMemory
				}

				Value* newValueAdress = Memory::Reallocate<Value>(ValueList, SizeAllocated);

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