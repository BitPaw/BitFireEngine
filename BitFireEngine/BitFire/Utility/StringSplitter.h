#pragma once

#include <string>
#include <iostream>

#include "List.hpp"

namespace BF
{
	class StringSplitter
	{
	private:
		StringSplitter();

	public:
		unsigned char SplitToken;
		 
		List<std::string> Lines;

		static StringSplitter Split(std::string content, char splitToken);
		static StringSplitter Split(std::string content, std::string splitTokens);
		static std::string CutInHalfAndTakeRightValue(std::string content, char splitToken);
	};
}