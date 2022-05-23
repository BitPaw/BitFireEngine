#include "Sound.h"

#include "AAC/AAC.h"
#include "M4A/M4A.h"
#include "FLAC/FLAC.h"
#include "MID/MID.h"
#include "MP3/MP3.h"
#include "OGG/OGG.h"
#include "WAV/WAV.h"
#include "WMA/WMA.h"

#include <File/File.h>
#include <Hardware/Memory/Memory.h>

BF::Sound::Sound()
{
    NumerOfChannels = 0;
    BitsPerSample = 0;
    SampleRate = 0;

    DataSize = 0;
    Data = nullptr;
}

BF::Sound::~Sound()
{
    Memory::Release(Data, DataSize);
}

BF::SoundFormat BF::Sound::FileFormatPeek(const wchar_t* filePath)
{
    FilePath file(filePath);

    if (file.ExtensionEquals("aac")) return SoundFormat::AAC;
    if (file.ExtensionEquals("flac")) return SoundFormat::FLAC;
    if (file.ExtensionEquals("m4a")) return SoundFormat::M4A;
    if (file.ExtensionEquals("mid")) return SoundFormat::MID;
    if (file.ExtensionEquals("mp3")) return SoundFormat::MP3;
    if (file.ExtensionEquals("ogg")) return SoundFormat::OGG;
    if (file.ExtensionEquals("wav")) return SoundFormat::WAV;
    if (file.ExtensionEquals("wma")) return SoundFormat::WMA;

    return SoundFormat::Unkown;
}

size_t BF::Sound::FullSizeInMemory()
{
    return sizeof(*this);
}

BF::FileActionResult BF::Sound::Load(const wchar_t* filePath)
{   
    SoundFormat soundFormat = FileFormatPeek(filePath);

    switch (soundFormat)
    {
        case SoundFormat::AAC:
        {
            AAC aac;
            aac.Load(filePath);
            aac.ConvertTo(*this);
            break;
        }
        case SoundFormat::FLAC:
        {
            FLAC flac;
            flac.Load(filePath);
            flac.ConvertTo(*this);
            break;
        }
        case SoundFormat::M4A:
        {
            M4A m4a;
            m4a.Load(filePath);
            m4a.ConvertTo(*this);
            break;
        }
        case SoundFormat::MID:
        {
            MID mid;
            mid.Load(filePath);
            mid.ConvertTo(*this);
            break;
        }
        case SoundFormat::MP3:
        {
            MP3 mp3;
            mp3.Load(filePath);
            mp3.ConvertTo(*this);
            break;
        }
        case SoundFormat::OGG:
        {
            OGG ogg;
            ogg.Load(filePath);
            ogg.ConvertTo(*this);
            break;
        }
        case SoundFormat::WAV:
        {
            WAV wav;
            wav.Load(filePath);
            wav.ConvertTo(*this);
            break;
        }
        case SoundFormat::WMA:
        {
            WMA wma;
            wma.Load(filePath);
            wma.ConvertTo(*this);
            break;
        }
        case SoundFormat::Unkown:
        default:
        {
            return FileActionResult::FormatNotSupported;
        }
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::Sound::Save(const wchar_t* filePath, SoundFormat soundFormat)
{
    switch (soundFormat)
    {
        default:
        case SoundFormat::Unkown:
            // Error
            break;

        case SoundFormat::AAC:
        {
            AAC aac;
            aac.ConvertFrom(*this);
            //aac.Save(FilePath);
            break;
        }     
        case SoundFormat::FLAC:
        {
            FLAC flac;
            flac.ConvertFrom(*this);
           // flac.Save(FilePath);
            break;
        }
        case SoundFormat::M4A:
        {
            M4A m4a;
            m4a.ConvertFrom(*this);
            //m4a.Save(FilePath);
            break;
        }
        case SoundFormat::MID:
        {
            MID mid;
            mid.ConvertFrom(*this);
           // mid.Save(FilePath);
            break;
        }
        case SoundFormat::MP3:
        {
            MP3 mp3;
            mp3.ConvertFrom(*this);
            //mp3.Save(FilePath);
            break;
        }
        case SoundFormat::OGG:
        {
            OGG ogg;
            ogg.ConvertFrom(*this);
           // ogg.Save(FilePath);
            break;
        }
        case SoundFormat::WAV:
        {
            WAV wav;
            wav.ConvertFrom(*this);
           // wav.Save(FilePath);
            break;
        }
        case SoundFormat::WMA:
        {
            WMA wma;
            wma.ConvertFrom(*this);
           // wma.Save(FilePath);
            break;
        }
    }

    return FileActionResult::Successful;
}