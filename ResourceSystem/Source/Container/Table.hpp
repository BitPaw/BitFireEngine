#pragma once

#include "List.hpp"

namespace BF
{
	template<class T>
	class Table
	{
		private:
		List<List<T>> _data;

		public:
		Table()
		{
			
		}

		Table(unsigned int width, unsigned height)
		{
			ReSize(width, height);
		}

		List<T>& operator[](unsigned int index)
		{
			return _data[index];
		}

		void ReSize(unsigned int width, unsigned height)
		{
			_data.ReSize(width);

			for (int i = 0; i < width; i++)
			{
				_data[i].ReSize(height);
			}
		}
	};
}