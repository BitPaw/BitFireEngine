#include <stdio.h>
#include <stdlib.h>


//#include <Network/Protocol/SBP/SBPServer.h>
//#include <Network/Protocol/SBP/SBPClient.h>
//#include <Network/Protocol/SBP/SBPQueue.h>
#include <Time/StopWatch.h>
//#include <OS/Sound/AudioSystem.h>
//#include <Media/Sound/WAV/WAV.h>
#include <File/Format/FNT/FNT.h>
#include <File/File.h>
//#include <Media/Font/Font.h>
//#include <Media/Font/FNT/FNT.h>
//#include <Media/Sound/OGG/OGG.h>
//#include <Media/Sound/MP3/MP3.h>
//#include <Media/Sound/M4A/M4A.h>

using namespace BF;



int main()
{
#if 0
    const unsigned int size = 5;
    SBPData sbpData[size];

    const unsigned int x = (unsigned int)MakeInt('F', 'i', 'l', 'e');

    const char text[] = "Hallo i bims";

    sbpData[0].Set(x, SourceMe, TargetEveryBody, -1, 0, nullptr);
    sbpData[1].Set(MakeInt('C', 'o', 'n', '#'), SourceMe, TargetServer, -1, 0, (void*)1u);
    sbpData[2].Set(MakeInt('I', '\'', 'a', 'm'), SourceMe, TargetAll, -1, 0, (void*)2u);
    sbpData[3].Set(MakeInt('W', 'h', 'o', '?'), SourceMe, TargetEveryBody, -1, 0, (void*)3u);
    sbpData[4].Set(MakeInt('T', 'e', 'x', 't'), SourceMe, TargetEveryBody, -1, sizeof(text), text);



    auto www = sizeof(TimeSpanType);



    SBPQueue sbpQueue;

    //sbpQueue.Allocate(1024);


    for(size_t i = 0; i < size; i++)
    {
        SBPData& pdata = sbpData[i];

        sbpQueue.Enqueue(pdata);
    }

    {
        SBPData data;

        while(sbpQueue.Dequeue(data))
        {
            SBPDataPrint(data);

            sbpQueue.Clear(data);
        }
    }


    for(int i = size-1; i >= 0; --i)
    {
        SBPData& pdata = sbpData[i];

        sbpQueue.Enqueue(pdata);
    }

#endif

#if 0
    printf("Start..\n");

    SBPClient client;
    SBPServer server;

    server.Start(25666);

    client.ConnectToServer("127.0.0.1", 25666);




    while(true)
    {
        //server.SendFile("C:/Users/BitPaw/Videos/Compile Info.txt");

        //Sleep(5000);
    }
#endif

#if 0
    SBPServer server;

    server.Start(25565);

    while(true)
    {
       server.SendFile("C:/Users/BitPaw/Videos/Compile Info.txt");

       Sleep(5000);
    }
#endif



#if 0
    M4A m4a;

    m4a.Load("A:/A.m4a");

#endif


#if 0
    MP3 mp3;

    mp3.Load("B:/Daten/Music/08-Bit/Dragon Ball Z Opening 8 bit.mp3");
    // mp3.Load("B:/Daten/Music/08-Bit/Black Sabbath - Iron man.mp3");

     //mp3.Load("A:/F/Giygas Beat.mp3");
#endif




#if 0 //OGG


    /*
    SBPClient client;

    client.ConnectToServer("localhost", 25666);

    while(true)
    {
        Sleep(1000);
    }
    */

    OGG ogg;

    ogg.Load("N:/NAS/Games/PC/OneShot/Audio/BGS/tv_static.ogg");
#endif


#if 1
    StopWatch sw;

    const char* filePath = "B:\\Daten\\Fonts\\_BitMapFont\\arial.fnt";

    FNT font;

    sw.Start();

    File file;

    const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath, MemoryReadOnly);
    const bool sucessful = fileLoadingResult == FileActionResult::Successful;

    const unsigned char fileParsingResult = FNTLoad(&font, file.Data, file.DataSize);

    float loadningTime = sw.Reset();

    //FNTSave(L"A:\\arial_COPY.fnt");

  //  float savingTime = sw.Reset();

    printf("Loading Took : %3.2fus\n", loadningTime * 1000000);
   // printf("Saveing Took : %3.2fus\n", savingTime * 1000000);
#endif


#if 0 // Audio

    WAV wave;

    FileActionResult fileActionResult = wave.Load("A:/CatFeet.wav");


    AudioSystem audioSystem;

    AudioDeviceCapabilities audioDeviceCapabilities[12];
    size_t audioDeviceOutputSize = 0;

    audioSystem.DevicesFetchOutput(audioDeviceCapabilities, 12, audioDeviceOutputSize);

    for(size_t i = 0; i < audioDeviceOutputSize; i++)
    {
        audioDeviceCapabilities[i].Prinf();
    }


    audioSystem.DevicesFetchInput(audioDeviceCapabilities, 12, audioDeviceOutputSize);

    for(size_t i = 0; i < audioDeviceOutputSize; i++)
    {
        audioDeviceCapabilities[i].Prinf();
    }


    AudioDeviceOutput audioDeviceOutput;
    AudioResult openRes = audioSystem.OutputOpen
    (
        audioDeviceOutput,
        audioDeviceCapabilities[0].DeviceID,
        wave.Format.AudioFormat,
        wave.Format.NumerOfChannels,
        wave.Format.SampleRate,
        wave.Format.ByteRate,
        wave.Format.BlockAllign,
        wave.Format.BitsPerSample,
        wave.Format.ChunkSize
    );

    AudioResult openWrite = audioSystem.OutputWrite
    (
        audioDeviceOutput,
        wave.SoundData,
        wave.SoundDataSize,
        0,
        0,
        WHDR_BEGINLOOP | WHDR_ENDLOOP,
        100
    );

 

   audioSystem.OutputPlaybackRateSet(audioDeviceOutput, 0x000F8000);

    while(true)
    {
        for(size_t i = 0; i < 0xFFFF; i++)
        {
           // audioSystem.OutputVolumeSet(audioDeviceOutput, i, i);

            for(size_t w = 0;w< 1; w++)
            {
               // printf(".");                   
            }
        }
    }

#endif
    return 0;
}
