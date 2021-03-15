#pragma once

namespace BF
{
	template <class Key, class Value>
	struct Dictionary
	{
		private:
		Key _keyTree;
		Value _valueTree;

		public:
		Value* GetValue(Key key)
		{
			return &_valueTree;
		}

		Key Add(Key key)
		{
			_keyTree = key;

			return nullptr;
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