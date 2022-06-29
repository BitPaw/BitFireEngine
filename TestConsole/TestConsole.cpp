#include <stdio.h>


#include <Network/Protocol/SBP/SBPServer.h>
#include <Network/Protocol/SBP/SBPClient.h>
#include <Network/Protocol/SBP/SBPQueue.h>
#include <Time/StopWatch.h>
#include <Media/Font/Font.h>
#include <Media/Font/FNT/FNT.h>
#include <Media/Sound/OGG/OGG.h>
#include <Media/Sound/MP3/MP3.h>
#include <Media/Sound/M4A/M4A.h>

using namespace BF;



void SBPDataPrint(const SBPData& sbpData)
{
    const char commandText[5]
    {
        sbpData.Command.A,
        sbpData.Command.B,
        sbpData.Command.C,
        sbpData.Command.D,
        '\0'
    };

    char sourceText[10];
    char targetText[10];

    if(sbpData.SourceID >= (unsigned int)SourceLimitMaximum)
    {
        const char* textINN = nullptr;

        switch(sbpData.TargetID)
        {
            default:
            case SourceInvalid:
                textINN = "Invalid";
                break;

            case SourceMe:
                textINN = "Me";
                break;

            case SourceServer:
                textINN = "Server";
                break;        
        }

        sprintf(sourceText, "%s", textINN);
    }
    else
    {
        sprintf(sourceText, "%8X", sbpData.Source);
    }

    if(sbpData.TargetID >= (unsigned int)TargetLimitMaximum)
    {
        const char* textINN = nullptr;

        switch(sbpData.TargetID)
        {
            default:
            case TargetInvalid:
                textINN = "Invalid";
                break;

            case TargetServer:
                textINN = "Me->Ser";
                break;

            case TargetAll:
                textINN = "Me->All";
                break;

            case TargetSpecific:
                textINN = "Me->Oth";
                break;

            case TargetYou:
                textINN = "Ser->You";
                break;

            case TargetYouAndOthers:
                textINN = "Othe->You";
                break;

            case TargetEveryBody:
                textINN = "ToAll";
                break;
        }

        sprintf(targetText, "%s", textINN);
    }
    else
    {
        sprintf(targetText, "%8X", sbpData.Target);       
    }

    printf
    (
        "+---------+----------+----------+----------+----------+\n"
        "| Command |  Source  |  Target  |    ID    |   Data   |\n"        
        "| %7s | %8s | %8s | %8X | %6i B |\n"
        "+---------+----------+----------+----------+----------+\n",
        commandText,
        sourceText,
        targetText,
        sbpData.ID,
        sbpData.DataSize
    );

    if(sbpData.DataSize)
    {
        printf("+-------------------[Payload Data]--------------------+\n");
        for(size_t i = 0; i < sbpData.DataSize; ++i)
        {
            const char* text = (char*)sbpData.Data;
            const char byte = text[i];
            const bool printableChar = (byte > 0x20) || (byte < 0x7F);
            const char printChar = printableChar ? byte : '?';

            printf("%c", printChar);

            if(((i+1) % 64) == 0)
            {
                printf("\n");
            }
        }
        printf("\n");
        printf("+-----------------------------------------------------+\n");
    }
}

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

#if 1
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


#if 0
    StopWatch sw;

    FNT font;

    sw.Start();

    font.Load(L"B:\\Daten\\Fonts\\_BitMapFont\\arial.fnt");

    float loadningTime = sw.Reset();

    font.Save(L"A:\\arial_COPY.fnt");

    float savingTime = sw.Reset();

    printf("Loading Took : %3.2fus\n", loadningTime * 1000000);
    printf("Saveing Took : %3.2fus\n", savingTime * 1000000);
#endif
    return 0;
}
