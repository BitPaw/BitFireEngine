#include "SoundLoader.h"

BF::Sound* BF::SoundLoader::LoadFromFile(AsciiString& filePath)
{
    Sound* sound = nullptr;
    SoundFormat soundFormat = SoundFormat::Unkown;
    TextFile textFile(filePath);
    AsciiString fileExtension = textFile.FileExtension;

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
           Log::Write(LogMessageType::Event, "[.MID] MIDI File detected.");

            MID* mid = MIDLoader::LoadFromFile(filePath);

            //sound = mid;

            break;
        }


        case SoundFormat::MP3:
        {
            Log::Write(LogMessageType::Event, "[.MP3] MPEG File detected.");

            MP3* mp3 = MP3Loader::LoadFromFile(filePath);

            //sound = mp3;

            break;
        }

        case SoundFormat::OGG:
        {
            Log::Write(LogMessageType::Event, "[.OGG] Ogging File detected.");

            OGG* ogg = OGGLoader::LoadFromFile(filePath);

           // sound = ogg;

            break;
        }

        case SoundFormat::WAV:
        {
            Log::Write(LogMessageType::Event, "[.WAV] Wave File detected.");

            WAV* wav = WAVLoader::LoadFromFile(filePath);

            //sound = wav;

            break;
        }

        case SoundFormat::Unkown:
        default:
            throw "Unsuported Type/File";
    }

    return sound;
}



BF::Sound* BF::SoundLoader::MIDToSound(MID* midi)
{
    return nullptr;
}

BF::Sound* BF::SoundLoader::MP3ToSound(MP3* mp3)
{
    return nullptr;
}

BF::Sound* BF::SoundLoader::OGGToSound(OGG* ogg)
{
    return nullptr;
}

BF::Sound* BF::SoundLoader::WAVToSound(WAV* wave)
{
    return nullptr;
}



BF::MID* BF::SoundLoader::SoundToMID(Sound* sound)
{
    return nullptr;
}

BF::MP3* BF::SoundLoader::SoundToMP3(Sound* sound)
{
    return nullptr;
}

BF::OGG* BF::SoundLoader::SoundToOGG(Sound* sound)
{
    return nullptr;
}

BF::WAV* BF::SoundLoader::SoundToWav(Sound* sound)
{
    return nullptr;
}