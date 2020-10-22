#pragma once

namespace BF
{
	struct Padding
	{
	public:
		unsigned int Left;
		unsigned int Top;
		unsigned int Right;
		unsigned int Bottom;

		Padding();
		Padding(const unsigned int all);
		Padding(const unsigned int left, const unsigned int right);
		Padding(const unsigned int left, const unsigned int top, const unsigned int right, const unsigned int bottom);
	};
}