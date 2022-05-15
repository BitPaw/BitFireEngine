#include "pch.h"
#include "CppUnitTest.h"

#include <Media/Image/Image.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BF;

namespace TestSystemResource
{
    TEST_CLASS(TestImage)
    {
        public:
        TEST_METHOD(TestLoadBMP)
        {
            Image image;

            const FileActionResult fileActionResult = image.Load(L"C:/Users/BitPaw/Videos/TEST_PNG.png");

            Assert::IsTrue(fileActionResult == FileActionResult::Successful, L"Image PNG loading failed");
        }

        TEST_METHOD(TestLoadPNG)
        {
            Image image;

            const FileActionResult fileActionResult = image.Load(L"C:/Users/BitPaw/Videos/TEST_PNG.png");

            Assert::IsTrue(fileActionResult == FileActionResult::Successful, L"Image PNG loading failed");
        }

        TEST_METHOD(TestLoadPNGSaveBMP)
        {
            Image image;

            const FileActionResult fileLoadResult = image.Load(L"C:/Users/BitPaw/Videos/TEST_PNG.png");

            Assert::IsTrue(fileLoadResult == FileActionResult::Successful, L"Image PNG loading failed");

            const FileActionResult fileSaveResult = image.Save(L"C:/Users/BitPaw/Videos/__Wurst.bmp", ImageFileFormat::BitMap);

            Assert::IsTrue(fileSaveResult == FileActionResult::Successful, L"Image PNG loading failed");
        }
    };
}
