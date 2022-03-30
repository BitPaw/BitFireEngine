#include <iostream>
#include <Processor/Processor.h>

int main()
{
  
    BF::ProcessorInfo processorInfo{0};

    BF::Processor::FetchInfo(processorInfo);

    std::cout << "Hello World!\n";
}
