#pragma once

#include <functional>

#include "InputContainer.h"

#include "../../Event/DataEvent.hpp"

namespace BF
{
	class OnInputEvent : public DataEvent<std::function<void(InputContainer&)>, InputContainer>
	{


	};
}