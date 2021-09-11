#include "Sound.h"

#include "AAC/AAC.h"
#include "M4A/M4A.h"
#include "FLAC/FLAC.h"
#include "MID/MID.h"
#include "MP3/MP3.h"
#include "OGG/OGG.h"
#include "WAV/WAV.h"
#include "WMA/WMA.h"

#include "../File/File.h"

BF::Sound::Sound()
{
    NumerOfChannels = 0;
    BitsPerSample = 0;
    SampleRate = 0;

    PlayStyle = SoundPlayStyle::Loop;

    DataSize = 0;
    Data = nullptr;
}

BF::SoundFormat BF::Sound::PeekFileFomat(const char* filePath)
{
    File file(filePath);
    AsciiString fileExtension(file.Extension);

    if (fileExtension.CompareIgnoreCase("aac")) return SoundFormat::AAC;
    if (fileExtension.CompareIgnoreCase("flac")) return SoundFormat::FLAC;
    if (fileExtension.CompareIgnoreCase("m4a")) return SoundFormat::M4A;
    if (fileExtension.CompareIgnoreCase("mid")) return SoundFormat::MID;
    if (fileExtension.CompareIgnoreCase("mp3")) return SoundFormat::MP3;
    if (fileExtension.CompareIgnoreCase("ogg")) return SoundFormat::OGG;
    if (fileExtension.CompareIgnoreCase("wav")) return SoundFormat::WAV;
    if (fileExtension.CompareIgnoreCase("wma")) return SoundFormat::WMA;   

    return SoundFormat::Unkown;
}

void BF::Sound::Load(const char* filePath)
{   
    SoundFormat soundFormat = PeekFileFomat(filePath);

    ID = ResourceIDLoading;

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
            ID = ResourceIDUnsuportedFormat;
            return;
        }        
    }

    ID = ResourceIDLoaded;
}

void BF::Sound::Save(const char* filePath, SoundFormat soundFormat)
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
            aac.Save(FilePath);
            break;
        }     
        case SoundFormat::FLAC:
        {
            FLAC flac;
            flac.ConvertFrom(*this);
            flac.Save(FilePath);
            break;
        }
        case SoundFormat::M4A:
        {
            M4A m4a;
            m4a.ConvertFrom(*this);
            m4a.Save(FilePath);
            break;
        }
        case SoundFormat::MID:
        {
            MID mid;
            mid.ConvertFrom(*this);
            mid.Save(FilePath);
            break;
        }
        case SoundFormat::MP3:
        {
            MP3 mp3;
            mp3.ConvertFrom(*this);
            mp3.Save(FilePath);
            break;
        }
        case SoundFormat::OGG:
        {
            OGG ogg;
            ogg.ConvertFrom(*this);
            ogg.Save(FilePath);
            break;
        }
        case SoundFormat::WAV:
        {
            WAV wav;
            wav.ConvertFrom(*this);
            wav.Save(FilePath);
            break;
        }
        case SoundFormat::WMA:
        {
            WMA wma;
            wma.ConvertFrom(*this);
            wma.Save(FilePath);
            break;
        }
    }
}