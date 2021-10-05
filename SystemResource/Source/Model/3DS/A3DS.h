#pragma once

#include "../IModelFormat.hpp"

namespace BF
{
	struct A3DS : public IModelFormat
	{
		public:
		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);
		FileActionResult ConvertTo(Model& model);
		FileActionResult ConvertFrom(Model& model);
	};
}