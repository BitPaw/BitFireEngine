#include "SBPQueue.h"
#include <Hardware/Memory/Memory.h>

BF::SBPQueue::SBPQueue()
{
	_dequeuedDataCursorPosition = 0;

	{
		const size_t preferedSize = 4096u;

		_file.MapToVirtualMemory(preferedSize);
	}
}

unsigned char BF::SBPQueue::Enqueue(const SBPData& SBPData)
{
	_file.Write(SBPData.CommandID.Data, 4u);
	_file.Write(SBPData.SourceID, Endian::Little);
	_file.Write(SBPData.TargetID, Endian::Little);
	_file.Write(SBPData.ID, Endian::Little);
	_file.Write(SBPData.DataSize, Endian::Little);
	_file.Write(SBPData.Data, SBPData.DataSize);

	return 0;
}

bool BF::SBPQueue::Dequeue(SBPData& sbpData)
{
	{
		const bool hasData = _dequeuedDataCursorPosition != _file.DataCursorPosition;

		if(!hasData)
		{
			return false;
		}
	}

	const size_t cursorPositionOld = _file.DataCursorPosition;

	_file.DataCursorPosition = _dequeuedDataCursorPosition; // Override, for following read

	_file.Read(sbpData.CommandID.Data, 4u);
	_file.Read(sbpData.SourceID, Endian::Little);
	_file.Read(sbpData.TargetID, Endian::Little);
	_file.Read(sbpData.ID, Endian::Little);
	_file.Read(sbpData.DataSize, Endian::Little);
	
	sbpData.Data = sbpData.DataSize ? _file.CursorCurrentAdress() : nullptr;

	// MOve cursor
	{
		const unsigned int offset = (4u * 5u) + sbpData.DataSize;

#if DoDataClear
		Byte* adress = (Byte*)_file.Data + _dequeuedDataCursorPosition;

		Memory::Set(adress, '#', (4u * 5u));
#endif

		_dequeuedDataCursorPosition += offset;
	}

	if(_dequeuedDataCursorPosition == cursorPositionOld)
	{
		_dequeuedDataCursorPosition = 0;
		_file.DataCursorPosition = 0;
	}
	else
	{
		_file.DataCursorPosition = cursorPositionOld; // Revert, position
	}			

	return true;
}

bool BF::SBPQueue::Clear(const SBPData& sbpData)
{
#if DoDataClear
	Memory::Set(sbpData.Data, '#', sbpData.DataSize);
#endif

	return true;
}