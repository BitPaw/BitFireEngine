#include <stdio.h>

#include <Network/Protocol/SilverBulletProtocolData.h>
#include <Container/QueueMapping.h>

using namespace BF;

int main()
{
    const unsigned int size = 5;
    SilverBulletProtocolData silverBulletProtocolData[size];

    {
        silverBulletProtocolData[0].Set((unsigned int)MakeInt('A', 'B', 'C', 'D'), SourceFillData, TargetEveryBody, -1, -1);
        silverBulletProtocolData[1].Set(MakeInt('A', 'B', 'C', 'D'), SourceFillData, TargetEveryBody, -1, -1);
        silverBulletProtocolData[2].Set(MakeInt('A', 'B', 'C', 'D'), SourceFillData, TargetEveryBody, -1, -1);
        silverBulletProtocolData[3].Set(MakeInt('A', 'B', 'C', 'D'), SourceFillData, TargetEveryBody, -1, -1);
        silverBulletProtocolData[4].Set(MakeInt('A', 'B', 'C', 'D'), SourceFillData, TargetEveryBody, -1, -1);
    }



    QueueMapping queueMapping;
    
    queueMapping.Allocate(1024);


    for(size_t i = 0; i < size; i++)
    {
        queueMapping.Enqueue(&silverBulletProtocolData[i], sizeof(SilverBulletProtocolData));
    }


    return 0;
}
