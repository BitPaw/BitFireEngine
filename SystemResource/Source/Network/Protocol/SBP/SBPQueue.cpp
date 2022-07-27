#include "SBPQueue.h"
#include <Memory/Memory.h>
/*
BF::SBPQueue::SBPQueue()
{
	_dequeuedDataCursorPosition = 0;

	{
		const size_t preferedSize = 4096u;

		_file.MapToVirtualMemory(preferedSize, MemoryNoReadWrite);
	}
}

unsigned char BF::SBPQueue::Enqueue(const SBPData& SBPData)
{
	_file.Write(SBPData.CommandID.Data, 4u);
	_file.Write(SBPData.SourceID, EndianLittle);
	_file.Write(SBPData.TargetID, EndianLittle);
	_file.Write(SBPData.ID, EndianLittle);
	_file.Write(SBPData.DataSize, EndianLittle);
	_file.Write(SBPData.Data, SBPData.DataSize);

	return 0;
}

bool BF::SBPQueue::Dequeue(SBPData& sbpData)
{
	{
		const bool hasData = _dequeuedDataCursorPosition != _file.DataCursor;

		if(!hasData)
		{
			return false;
		}
	}

	const size_t cursorPositionOld = _file.DataCursor;

	_file.DataCursor = _dequeuedDataCursorPosition; // Override, for following read

	_file.Read(sbpData.CommandID.Data, 4u);
	_file.Read(sbpData.SourceID, EndianLittle);
	_file.Read(sbpData.TargetID, EndianLittle);
	_file.Read(sbpData.ID, EndianLittle);
	_file.Read(sbpData.DataSize, EndianLittle);
	
	sbpData.Data = sbpData.DataSize ? _file.CursorCurrentAdress() : nullptr;

	// MOve cursor
	{
		const unsigned int offset = (4u * 5u) + sbpData.DataSize;

#if DoDataClear
		Byte__* adress = (Byte__*)_file.Data + _dequeuedDataCursorPosition;

		MemorySet(adress, '#', (4u * 5u));
#endif

		_dequeuedDataCursorPosition += offset;
	}

	if(_dequeuedDataCursorPosition == cursorPositionOld)
	{
		_dequeuedDataCursorPosition = 0;
		_file.DataCursor = 0;
	}
	else
	{
		_file.DataCursor = cursorPositionOld; // Revert, position
	}			

	return true;
}

bool BF::SBPQueue::Clear(const SBPData& sbpData)
{
#if DoDataClear
	MemorySet(sbpData.Data, '#', sbpData.DataSize);
#endif

	return true;
}*/