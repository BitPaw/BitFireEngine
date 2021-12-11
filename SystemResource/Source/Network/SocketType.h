#pragma once

namespace BF
{
	enum class SocketType
	{
		Invalid,

		Stream,// stream socket */
		Datagram, // datagram socket */ 
		Raw, // raw-protocol interface */ 
		RDM, // reliably-delivered message */ 
		SeqPacket // sequenced packet stream */
	};

	SocketType ConvertSocketType(unsigned int socketType);
	unsigned int ConvertSocketType(SocketType socketType);
}