#include "SBPServer.h"

#include <cstdio>
#include <File/ByteStream.h>
#include <Network/Protocol/SBP/SBPData.h>
#include <Text/Text.h>
#include <Network/Protocol/SBP/SBPText.h>

void BF::SBPServer::CreateText(const char* text, Byte* buffer, size_t& bufferSize, const size_t bufferSizeMax)
{
	ByteStream byteStream(buffer, bufferSize);
	const size_t size = Text::Length(text) + 1; // length + nullbyte 

	const SBPText sbpText(text);

	const SBPData sbpData
	(
		SBPIDText,
		SourceMe,
		TargetMeToAll,
		-1,
		size + 1, // +string indicator
		&sbpText
	);

	unsigned char y = (char)sbpText.Type;

	byteStream.Write("°°", 2u);
	byteStream.Write(sbpData.Command.Data, 4u);
	byteStream.Write(sbpData.Source, Endian::Little);
	byteStream.Write(sbpData.Target, Endian::Little);
	byteStream.Write(sbpData.ID, Endian::Little);
	byteStream.Write(sbpData.DataSize, Endian::Little);
	byteStream.Write(y);
	byteStream.Write(sbpText.TextA, size);

	bufferSize = byteStream.DataCursorPosition;
}

void BF::SBPServer::CreateText(const wchar_t* text, Byte* buffer, size_t& bufferSize, const size_t bufferSizeMax)
{
	ByteStream byteStream(buffer, bufferSize);

	const SBPText sbpText(text);
	const size_t size = sbpText.SizeInBytes();

	const SBPData sbpData
	(
		SBPIDText,
		SourceMe,
		TargetMeToAll,
		-1,
		size + 1, // +string indicator
		&sbpText
	);

	unsigned char y = (char)sbpText.Type;

	byteStream.Write("°°", 2u);
	byteStream.Write(sbpData.Command.Data, 4u);
	byteStream.Write(sbpData.Source, Endian::Little);
	byteStream.Write(sbpData.Target, Endian::Little);
	byteStream.Write(sbpData.ID, Endian::Little);
	byteStream.Write(sbpData.DataSize, Endian::Little);
	byteStream.Write(y);
	byteStream.Write(sbpText.TextW, size);

	bufferSize = byteStream.DataCursorPosition;
}

void BF::SBPServer::Start(const unsigned short port)
{
	_server.Start(port);
}

void BF::SBPServer::Stop()
{
	_server.Stop();
}

void BF::SBPServer::SendFile(const char* text)
{
	
}

void BF::SBPServer::SendFile(const wchar_t* text)
{
}

void BF::SBPServer::SendTextToAll(const char* text)
{
	const size_t bufferSize = 2048;
	size_t size = 0;
	Byte buffer[bufferSize]{ 0 };

	CreateText(text, buffer, size, bufferSize);

	_server.SendMessageToAll(buffer, size);
}

void BF::SBPServer::SendTextToAll(const wchar_t* text)
{
	const size_t bufferSize = 2048;
	size_t size = 0;
	Byte buffer[bufferSize]{ 0 };
	
	CreateText(text, buffer, size, bufferSize);

	_server.SendMessageToAll(buffer, size);
}

void BF::SBPServer::SendTextToClient(const unsigned int clientID, const char* text)
{
	const size_t bufferSize = 2048;
	size_t size = 0;
	Byte buffer[bufferSize]{ 0 };

	CreateText(text, buffer, size, bufferSize);

	_server.SendMessageToClient(clientID, buffer, size);
}

void BF::SBPServer::SendTextToClient(const unsigned int clientID, const wchar_t* text)
{
	const size_t bufferSize = 2048;
	size_t size = 0;
	Byte buffer[bufferSize]{ 0 };

	CreateText(text, buffer, size, bufferSize);

	_server.SendMessageToClient(clientID, buffer, size);
}