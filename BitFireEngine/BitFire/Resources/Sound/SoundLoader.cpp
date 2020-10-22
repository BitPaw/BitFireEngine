#include "SoundLoader.h"

BF::ISound* BF::SoundLoader::LoadFromFile(std::string filePath)
{
    ISound* sound = nullptr;
    SoundFormat soundFormat = SoundFormat::Unkown;
    TextFile textFile(filePath);
    std::string fileExtension = textFile.GetFileExtension();

    bool isMIDI = fileExtension == "mid";
    bool isMP3 = fileExtension == "mp3";
    bool isOGG = fileExtension == "ogg";
    bool isWAV = fileExtension == "wav";

    if (isMIDI) soundFormat = SoundFormat::MID;
    if (isMP3) soundFormat = SoundFormat::MP3;
    if (isOGG) soundFormat = SoundFormat::OGG;
    if (isWAV) soundFormat = SoundFormat::WAV;

    switch (soundFormat)
    {
        case SoundFormat::MID:
        {
            MessageSystem::PushMessage(MessageType::Info, "[.MID] MIDI File detected.");

            MID* mid = MIDLoader::LoadFromFile(filePath);

            sound = mid;

            break;
        }


        case SoundFormat::MP3:
        {
            MessageSystem::PushMessage(MessageType::Info, "[.MP3] MPEG File detected.");

            MP3* mp3 = MP3Loader::LoadFromFile(filePath);

            sound = mp3;

            break;
        }

        case SoundFormat::OGG:
        {
            MessageSystem::PushMessage(MessageType::Info, "[.OGG] Ogging File detected.");

            OGG* ogg = OGGLoader::LoadFromFile(filePath);

            sound = ogg;

            break;
        }

        case SoundFormat::WAV:
        {
            MessageSystem::PushMessage(MessageType::Info, "[.WAV] Wave File detected.");

            WAV* wav = WAVLoader::LoadFromFile(filePath);

            sound = wav;

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