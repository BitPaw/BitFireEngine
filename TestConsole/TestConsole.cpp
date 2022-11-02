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
#include <OS/PXWindow.h>
#include <OS/OSUI.h>
#include <CommCtrl.h>
#include <File/Image.h>
#include <File/Font.h>
//#include <Media/Font/Font.h>
//#include <Media/Font/FNT/FNT.h>
//#include <Media/Sound/OGG/OGG.h>
//#include <Media/Sound/MP3/MP3.h>
//#include <Media/Sound/M4A/M4A.h>

using namespace BF;


void OnWindowCreated(const void* const receiver, const PXWindow* window)
{
    OSButton button;
    OSListBox listBox;
    OSComboBox comboBox;
    OSRichEdit richEdit;
    OSScrollBar scrollBar;
    OSUIText text;
    OSUICheckBox checkBox;
    OSUITrackbar trackbar;
    OSUITabControl odUITabControl;
    OSUIListBox osListBox;

    OSUIStatusbar statusbar;
    OSUIUpDown osUIUpDown;
    OSUIProgressbar osUIProgressbar;
    OSUIHotKey osUIHotKey;

    OSUICalender calender;
    OSUIToolTip uiToolTip;
    OSUIAnimate osUIAnimate;
    OSUIDateTimePicker osUIDateTimePicker;

    OSUIGroupBox osUIGroupBox;
    OSUIGroupRadioButton osUIRadioButtonA;
    OSUIGroupRadioButton osUIRadioButtonB;
    OSUIGroupRadioButton osUIRadioButtonC;
    OSUIRadioButton osUIRadioButtonSingle;


    OSUIPageScroller osUIPageScroller;
    OSUIFontSelector osUIFontSelector;
    OSUIHeader osUIHeader;
    OSUILink osUILink;
    OSUITreeView osUITreeView;


    int xoffset = 20;

    int w = 150;
    int h = 35;
    int v = 50;
    int b = 200;

    ButtonConstruct(window->ID, &button, xoffset + b * 0,         v*1, w, h, L"Button Text");
    ListBoxConstruct(window->ID, &listBox, xoffset + b * 0 ,         v*2, w, h, L"ListBox");
    ComboBoxConstruct(window->ID, &comboBox, xoffset + b * 0,         v*3, w, h, L"ComboBox");
    RichEditConstruct(window->ID, &richEdit, xoffset + b * 0, v * 4, w, h, L"Richtext");
    OSUIListBoxCreate(window->ID, &osListBox, xoffset + b * 0,         v*5 , w, h, L"OSUITabControl");
    OSUITabControlCreate(window->ID, &odUITabControl, xoffset + b * 0,   v*6, w, h, L"OSListBox");
    ScrollBarConstruct(window->ID, &scrollBar, xoffset + b * 0, v * 7, w, h, L"Scrollbar");
    OSUITextConstruct(window->ID, &text, xoffset + b * 0 , v * 8, w, h, L"Some Text");
    OSCheckBoxConstruct(window->ID, &checkBox, xoffset + b * 0 , v * 9, w, h, L"CheckBox");
    OSUITrackbarCreate(window->ID, &trackbar, xoffset + b * 0 , v * 10, w, h, L"Trackbar");
    OSUIStatusbarCreate(window->ID, &statusbar, xoffset + b * 0, v * 11, w, h, L"Statusbar");
    OSUIUpDownCreate(window->ID, &osUIUpDown, xoffset + b * 0, v * 12, w, h, L"Some Text");
    OSUIProgressbarCreate(window->ID, &osUIProgressbar, xoffset + b * 0, v * 13, w, h, L"Progressbar");
    OSUIHotKeyCreate(window->ID, &osUIHotKey, xoffset + b * 0, v * 14, w, h, L"HotKey");


    OSUIPageScrollerCreate(window->ID, &osUIPageScroller, xoffset + b * 1, v * 1, w, h, L"OSUIPageScrollerCreate");
    OSUIFontSelectorCreate(window->ID, &osUIFontSelector, xoffset + b * 1, v * 2, w, h, L"OSUIFontSelectorCreate");
    OSUIHeaderCreate(window->ID, &osUIHeader, xoffset + b * 1, v * 3, w, h, L"OSUIHeaderCreate");
    OSUILinkCreate(window->ID, &osUILink, xoffset + b * 1, v * 4, w, h, L"OSUILinkCreate");

    OSUIGroupBoxCreate(window->ID, &osUIGroupBox, xoffset + b * 1, v * 5, 200, h * 5, L"GroupBox");
    OSUIGroupRadioButtonCreate(window->ID, &osUIRadioButtonA, xoffset + b * 1, v * 6, 200, h, L"RadioButton_A");
    OSUIGroupRadioButtonCreate(window->ID, &osUIRadioButtonB, xoffset + b * 1, v * 7, 200, h, L"RadioButton_B");
    OSUIGroupRadioButtonCreate(window->ID, &osUIRadioButtonC, xoffset + b * 1, v * 8, 200, h, L"RadioButton_C");

    OSUIRadioButtonCreate(window->ID, &osUIRadioButtonSingle, xoffset + b * 1, v * 9, 200, h, L"RadioButton_Single");


    OSUIDateTimePickerCreate(window->ID, &osUIDateTimePicker, xoffset + b * 2, v * 1, w, h, L"DateTimePicker");
    OSUIToolTipCreate(window->ID, &uiToolTip, xoffset + b * 2, v * 2, 180, h, L"ToolTip");
    OSUIAnimateCreate(window->ID, &osUIAnimate, xoffset + b * 2, v * 3, 180, h, L"Animate");
    OSUICalenderCreate(window->ID, &calender, xoffset + b * 2, v * 4, 180, 180, L"CalenderC");
    OSUITreeViewCreate(window->ID, &osUITreeView, xoffset + b * 2, v * 8, 180, 180, L"TreeView");



    printf("Hello\n");

}

void OnKeyBoardKey(const void* const receiver, const PXWindow* sender, const KeyBoardKeyInfo keyBoardKeyInfo)
{
   // printf("[#]\n");
}

void TestLoadImage()
{

}

void TestSaveImage()
{
    Image image;

    ImageConstruct(&image);

    // Write image data
    {
        const size_t width = 512u * 1;
        const size_t height = 512u * 1;

        ImageResize(&image, ImageDataFormatRGB, width, height);

        int dimension = 3;

        for(size_t y = 0; y < height; y++)
        {
            for(size_t x = 0; x < width; x++)
            {
                const unsigned char red = x | y;
                const unsigned char green = x ^ y;
                const unsigned char blue = 0xFF * !(x & y);

                ((unsigned char*)image.PixelData)[dimension * width * y + dimension * x + 2] = blue;
                ((unsigned char*)image.PixelData)[dimension * width * y + dimension * x + 1] = green;
                ((unsigned char*)image.PixelData)[dimension * width * y + dimension * x + 0] = red;


                // image.PixelData[4 * width * y + 4 * x + 3] = 255;
            }
        }
    }

    ImageSaveA(&image, "D:/_Data/ImageBMP.bmp", ImageFileFormatBitMap, ImageDataFormatRGB);
    ImageSaveA(&image, "D:/_Data/ImagePNG.png", ImageFileFormatPNG, ImageDataFormatRGB);
    ImageSaveA(&image, "D:/_Data/ImageJPG.jpg", ImageFileFormatJPEG, ImageDataFormatRGB);

    ImageDestruct(&image);
}

void ImageWriteText()
{
    Image image;
    PXFont font;

    Image imageAA;
    //ActionResult dfsdsfdsf = ImageLoadA(&imageAA, "D:/_Data/A.png");

    ImageConstruct(&image);



    ActionResult actionResult = FontLoadA(&font, "D:/_Data/A.fnt");
    ActionResult loadResult = ImageLoadA(&image, "D:/_Data/ImageInput.bmp");

    // Write image data
    {
        const size_t width = 512u * 1;
        const size_t height = 512u * 1;

        ImageResize(&image, ImageDataFormatRGB, width, height);     

        //ImageDrawRectangle(&image, 0,0, width, height, 0xFF, 0xFF, 0xFF, 0xFF);
        ImageDrawRectangle(&image, 10, 10, 10, 10, 0xFF, 0x00, 0x00, 0x00);
        ImageDrawRectangle(&image, 10, 30, 10, 10, 0x00, 0xFF, 0x00, 0x00);
        ImageDrawRectangle(&image, 10, 50, 10, 10, 0x00, 0x00, 0xFF, 0x00);

        ImageDrawTextA(&image, 10, 70, 100, 30, &font, "Hello World");
    }

    ImageSaveA(&image, "D:/_Data/TEST_TextWrite.bmp", ImageFileFormatBitMap, ImageDataFormatRGB);
    ImageSaveA(&image, "D:/_Data/TEST_TextWrite.jpeg", ImageFileFormatJPEG, ImageDataFormatRGB);
    ImageSaveA(&image, "D:/_Data/TEST_TextWrite.png", ImageFileFormatPNG, ImageDataFormatRGBA);

    ImageDestruct(&image);
}

void TestCreateWindow()
{
    PXWindow window;


    PXWindowConstruct(&window);

    window.WindowCreatedCallBack = OnWindowCreated;
    window.KeyBoardKeyCallBack = OnKeyBoardKey;

    PXWindowCreate(&window, 600, 400, "I BIMS", true);

    while(!window.IsRunning)
    {
        //printf(".");
    }

    while(true)
    {
        //printf("\033[0;0H\n");

       // MouseInputPrint(&window.MouseCurrentInput);

        //printf(".");
    }

}

int main()
{

    // ImageLoadA(&jpg, "D:/_Data/__TEST__IMAGE__/TEST.jpg");

     //Image bmpTest;
     //ImageLoadA(&bmpTest, "D:/_Data/Test.bmp");
     //ImageSaveA(&bmpTest, "D:/_Data/Image_S.bmp", ImageFileFormatBitMap, ImageDataFormatRGB);


    ImageWriteText();



    return 0;



 















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
    const ActionResult fileLoadingResult = FileMapToVirtualMemoryA(&dggfgf, "B:\\Daten\\Bilder\\tumblr_oou0htSqtG1shbbpso1_640.png", 0, MemoryReadOnly);
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

    const ActionResult iiuiiii = FileMapToVirtualMemoryA(&dggfgf, filePath, 0, MemoryReadOnly);
    const bool sucessfulddd = iiuiiii == ResultSuccessful;

    size_t parsedBytes = 0;
    const ActionResult fileParsingResult = ResultSuccessful;// FNTParse(&font, file.Data, file.DataSize, &parsedBytes);

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
