#pragma once

#include "../IModelFormat.hpp"

namespace BF
{
	struct A3DS : public IModelFormat
	{
		public:
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Save(const wchar_t* filePath);
		FileActionResult ConvertTo(Model& model);
		FileActionResult ConvertFrom(Model& model);
	};
}