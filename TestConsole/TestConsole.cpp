#include <iostream>
#include <Processor/Processor.h>
#include <Encryption/MD5/MD5.h>

int main()
{
  
   // BF::ProcessorInfo processorInfo{0};

  //  BF::Processor::FetchInfo(processorInfo);


  
    const char input[] = "";// "The quick brown fox jumps over the lazy dog.";
    const size_t inputSize = sizeof(input);
    const size_t outputSize = 1024;
    char output[outputSize]{0};


    size_t writtenBytes = BF::MD5::Encrypt(input, inputSize, output, outputSize);







    std::cout << "Hello World!\n";

    return 0;
}
