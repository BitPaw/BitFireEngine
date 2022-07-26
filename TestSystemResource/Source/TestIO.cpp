#include "pch.h"
#include "CppUnitTest.h"

#include <File/File.h>
#include <File/FileStream.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BF;

namespace TestSystemResource
{
    TEST_CLASS(TestIO)
    {
        public:
        TEST_METHOD(TestListAllFiles)
        {
            wchar_t** list = nullptr;
            size_t listSite = 0;

            File::FilesInFolder("C:/Windows/*.*", &list, listSite);

            Assert::IsTrue(list != nullptr);
        }

        TEST_METHOD(TestOpenFIleDialog)
        {
            //char fileNameBuffer[255];
            //OpenFileDialog::Open(fileNameBuffer);

            OPENFILENAMEA fileNameBuffer;

            memset(&fileNameBuffer, 0, sizeof(OPENFILENAMEA));

            bool hello = GetOpenFileNameA(&fileNameBuffer);

            Assert::IsTrue(hello);
        }      


        TEST_METHOD(TestWriteFile)
        {
            const char* filePath = "%temp%/BFE_TEST.txt";

            BF::FileStream fs2(20480);

            for (int i = 0; i < 1000; ++i)
            {
                printf("%i\n", i);

                fs2.Write("a\n", 3u);
            }

            const ActionResult resuilt =  fs2.WriteToDisk(filePath);

            Assert::IsTrue(resuilt == ResultSuccessful);

            const ErrorCode errorCode = File::Remove(filePath);

            Assert::IsTrue(errorCode == ErrorCode::Successful);
        }
    };
}
