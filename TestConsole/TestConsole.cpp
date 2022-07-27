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
#include <File/Format/MP3/MP3.h>
#include <File/Format/PNG/PNG.h>
#include <OS/Window.h>
#include <OS/OSUI.h>
#include <CommCtrl.h>
//#include <Media/Font/Font.h>
//#include <Media/Font/FNT/FNT.h>
//#include <Media/Sound/OGG/OGG.h>
//#include <Media/Sound/MP3/MP3.h>
//#include <Media/Sound/M4A/M4A.h>

using namespace BF;


void OnWindowCreated(void* windowAdress)
{
    Window* window = (Window*)windowAdress;

    OSButton button;
    OSListBox listBox;
    OSComboBox comboBox;
    OSRichEdit richEdit;
    OSScrollBar scrollBar;

    ButtonConstruct(window->ID, &button, 20, 35*1 +55, 100, 35, L"OK");
    ListBoxConstruct(window->ID, &listBox, 20, 35*4 + 55, 100, 35, L"OK");
    ComboBoxConstruct(window->ID, &comboBox, 20, 35*8 + 55, 100, 35, L"OK");
    RichEditConstruct(window->ID, &richEdit, 20, 35 * 16 + 55, 100, 35, L"OK");
    ScrollBarConstruct(window->ID, &scrollBar, 20, 35 * 32 + 55, 100, 35, L"OK");


    INITCOMMONCONTROLSEX icex;

    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_DATE_CLASSES;

    unsigned char x = InitCommonControlsEx(&icex);

    printf("Hello\n");

}


int main()
{


    Window window;


    WindowConstruct(&window);

    window.WindowCreatedCallBack = OnWindowCreated;

    WindowCreate(&window, 600, 400, "I BIMS", true);
    
    while(!window.IsRunning)
    {
        printf(".");
    }

    while(true)
    {
        //printf(".");
    }
















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

#if 1
    PNG png;

    File dggfgf;
    const ActionResult fileLoadingResult = FileMapToVirtualMemoryA(&dggfgf, "B:\\Daten\\Bilder\\tumblr_oou0htSqtG1shbbpso1_640.png", MemoryReadOnly);
    const bool sucessful = fileLoadingResult == ResultSuccessful;

    size_t readBytes = 0;
    PNGParse(&png, dggfgf.Data, dggfgf.DataSize, &readBytes);

#endif


#if 0
    MP3 mp3;


    File dggfgf;

    const ActionResult fileLoadingResult = dggfgf.MapToVirtualMemory("B:/Daten/Music/08-Bit/Dragon Ball Z Opening 8 bit.mp3", MemoryReadOnly);
    const bool sucessful = fileLoadingResult == ResultSuccessful;
    size_t witnnen = 0;

    MP3Parse(&mp3, dggfgf.Data, dggfgf.DataSize, &witnnen);

    //mp3.Load();
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

    const ActionResult iiuiiii = FileMapToVirtualMemoryA(&dggfgf, filePath, MemoryReadOnly);
    const bool sucessfulddd = iiuiiii == ResultSuccessful;

    size_t parsedBytes = 0;
    const ActionResult fileParsingResult = FNTParse(&font, file.Data, file.DataSize, &parsedBytes);

    float loadningTime = sw.Reset();

    //FNTSave(L"A:\\arial_COPY.fnt");

  //  float savingTime = sw.Reset();

    printf("Loading Took : %3.2fus\n", loadningTime * 1000000);
   // printf("Saveing Took : %3.2fus\n", savingTime * 1000000);
#endif


#if 0 // Audio

    WAV wave;

    ActionResult fileActionResult = wave.Load("A:/CatFeet.wav");


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
