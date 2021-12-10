#pragma once

#include "IPAdressInfo.h"

namespace BF
{
	class IClientListener
	{
		public:
		virtual void OnConnectedToServer(IPAdressInfo& adressInfo) = 0;
	};
}