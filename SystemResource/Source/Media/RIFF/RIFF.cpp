#include "RIFF.h"

#define RIFFSignature MakeInt('R', 'I', 'F', 'F')
#define RIFXSignature MakeInt('R', 'I', 'F', 'X')

//#define RIFFSubTypeANI MakeInt('x', 'x', 'x', 'x')
#define RIFFSubTypeAVI MakeInt('A', 'V', 'I', ' ')
#define RIFFSubTypeRDIB MakeInt('R', 'D', 'I', 'B')
//#define RIFFSubTypeBND MakeInt('x', 'x', 'x', 'x')
//#define RIFFSubTypeDXR MakeInt('x', 'x', 'x', 'x')
#define RIFFSubTypePAL MakeInt('P', 'A', 'L', ' ')
//#define RIFFSubTypeRDI MakeInt('x', 'x', 'x', 'x')
#define RIFFSubTypeRMMP MakeInt('R', 'M', 'M', 'P')
#define RIFFSubTypeRMID MakeInt('R', 'M', 'I', 'D')
#define RIFFSubTypeWAVE MakeInt('W', 'A', 'V', 'E')

BF::RIFF::RIFF()
{
	Valid = false;
	EndianFormat = Endian::Invalid;
	ChunkSize = 0;
	Format = RIFFFormat::Invalid;
}

void BF::RIFF::Parse(FileStream& fileStream)
{
	ByteCluster chunkID;
	ByteCluster formatID;

	fileStream.Read(chunkID.Data, 4);
	fileStream.Read(ChunkSize, Endian::Little);
	fileStream.Read(formatID.Data, 4);

	switch(chunkID.Value) // Detect Endiantype
	{
		case RIFXSignature:
			EndianFormat = Endian::Big;
			break;

		case RIFFSignature:
			EndianFormat = Endian::Little;
			break;

		default:
			EndianFormat = Endian::Invalid;
			break;
	}

	switch(formatID.Value)
	{	 	 
		case RIFFSubTypeAVI:
			Format = RIFFFormat::AudioVideoInterleave;
			break;

		case RIFFSubTypeRDIB:
			Format = RIFFFormat::DeviceIndependentBitmap;
			break;

		case RIFFSubTypePAL:
			Format = RIFFFormat::Palette;
			break;

		case RIFFSubTypeRMMP:
			Format = RIFFFormat::MultimediaMovieFile;
			break;

		case RIFFSubTypeRMID:
			Format = RIFFFormat::MIDI;
			break;

		case RIFFSubTypeWAVE:
			Format = RIFFFormat::WaveformAudio;
			break;

		default:
			Format = RIFFFormat::Invalid;
			break;
	}

	Valid = (EndianFormat != Endian::Invalid) && (Format != RIFFFormat::Invalid);
}