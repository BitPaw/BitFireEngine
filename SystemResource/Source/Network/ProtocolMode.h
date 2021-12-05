#pragma once

namespace BF
{
	enum class ProtocolMode
	{
		Any,

		TCP,
		UDP
	};

	ProtocolMode ConvertProtocolMode(unsigned char protocolMode);
	unsigned char ConvertProtocolMode(ProtocolMode protocolMode);
}