#pragma once

#include "../IModelFormat.hpp"

namespace BF
{
	struct PLY : public IModelFormat
	{
		public:
		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);
		FileActionResult ConvertTo(Model& model);
		FileActionResult ConvertFrom(Model& model);
	};
}