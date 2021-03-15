#pragma once

#include <functional>

#include "../../Event/TriggerEvent.hpp"

namespace BF
{
	class OnWindowCloseEvent : public TriggerEvent<std::function<void()>>
	{

	};
}