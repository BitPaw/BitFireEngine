#include "IPv4.h"

BF::IPv4::IPv4()
{
	_octetList.ReSize(4);

	_octetList[0] = 127;
	_octetList[1] = 0;
	_octetList[2] = 0;
	_octetList[3] = 1;
}

BF::IPv4::IPv4(AsciiString ip) : IPv4()
{
	SetAdress(ip);
}

void BF::IPv4::SetAdress(AsciiString ip)
{
	try
	{
		const unsigned int amountOfDots = ip.Count('.');

		if (amountOfDots == 3)
		{
			List<AsciiString> octetList;

			ip.Splitt('.', octetList);

			unsigned int amountOfoctets = octetList.Size();

			if (amountOfoctets == 4)
			{
				_octetList[0] = octetList[0].ToInt();
				_octetList[1] = octetList[1].ToInt();
				_octetList[2] = octetList[2].ToInt();
				_octetList[3] = octetList[3].ToInt();
			}
			else
			{
				throw "Expected a number, got something else";
			}
		}
		else
		{
			throw "Too many dots";
		}
	}
	catch (std::exception e)
	{
		throw "Invalid IPv4";
	}	
}

bool BF::IPv4::IsValidIP(AsciiString ip)
{
	try
	{
		IPv4 ipadress(ip);
	}
	catch (const std::exception&)
	{
		return false;
	}

	return true;
}

BF::AsciiString BF::IPv4::ToString()
{
	AsciiString point(".");
	AsciiString a(_octetList[0]);
	AsciiString b(_octetList[1]);
	AsciiString c(_octetList[2]);
	AsciiString d(_octetList[3]);

	return	a + point + b + point + c + point + d;
}
