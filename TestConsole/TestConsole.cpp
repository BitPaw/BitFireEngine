#include <stdio.h>


#include <Network/Protocol/SBP/SBPServer.h>
#include <Network/Protocol/SBP/SBPQueue.h>
#include <Time/StopWatch.h>

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

    if(sbpData.Source >= (unsigned int)SourceLimitMaximum)
    {
        const char* textINN = nullptr;

        switch(sbpData.Target)
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

    if(sbpData.Target >= (unsigned int)TargetLimitMaximum)
    {
        const char* textINN = nullptr;

        switch(sbpData.Target)
        {
            default:
            case TargetInvalid:
                textINN = "Invalid";
                break;

            case TargetMeToServer:
                textINN = "Me->Ser";
                break;

            case TargetMeToAll:
                textINN = "Me->All";
                break;

            case TargetMeToOthers:
                textINN = "Me->Oth";
                break;

            case TargetYouOnly:
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
    sbpData[1].Set(MakeInt('C', 'o', 'n', '#'), SourceMe, TargetMeToServer, -1, 0, (void*)1u);
    sbpData[2].Set(MakeInt('I', '\'', 'a', 'm'), SourceMe, TargetMeToAll, -1, 0, (void*)2u);
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

    SBPServer server;    

    server.Start(25565);

    while(true)
    {
       server.SendTextToAll(L"Ping Hello");

       Sleep(1000);
    }   

    return 0;
}
