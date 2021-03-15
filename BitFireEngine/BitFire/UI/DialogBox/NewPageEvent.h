#include <functional>

#include "../../Event/TriggerEvent.hpp"

namespace BF
{
	class NewPageEvent : public TriggerEvent<std::function<void()>>
	{

	};
}