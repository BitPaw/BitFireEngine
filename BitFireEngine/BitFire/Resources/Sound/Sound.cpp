#include "Sound.h"

#include "SoundFormat.h"
#include "MID/MID.h"
#include "MP3/MP3.h"
#include "OGG/OGG.h"
#include "WAV/WAV.h"
#include "../File/File.h"

void BF::Sound::Load(AsciiString& filePath)
{
    SoundFormat soundFormat = SoundFormat::Unkown;
    File file(filePath);
    AsciiString& fileExtension = file.Extension;

    bool isMIDI = fileExtension.CompareIgnoreCase("mid");
    bool isMP3 = fileExtension.CompareIgnoreCase("mp3");
    bool isOGG = fileExtension.CompareIgnoreCase("ogg");
    bool isWAV = fileExtension.CompareIgnoreCase("wav");

    if (isMIDI) soundFormat = SoundFormat::MID;
    if (isMP3) soundFormat = SoundFormat::MP3;
    if (isOGG) soundFormat = SoundFormat::OGG;
    if (isWAV) soundFormat = SoundFormat::WAV;

    switch (soundFormat)
    {
        case SoundFormat::MID:
        {
            MID mid;

            //sound = mid;

            break;
        }
        case SoundFormat::MP3:
        {
            MP3 mp3;

            //sound = mp3;

            break;
        }
        case SoundFormat::OGG:
        {
            OGG ogg;

            // sound = ogg;

            break;
        }
        case SoundFormat::WAV:
        {
            WAV wav;

            //sound = wav;

            break;
        }
        case SoundFormat::Unkown:
        default:
        {
            throw "Unsuported Type/File";
        }         
    }
}