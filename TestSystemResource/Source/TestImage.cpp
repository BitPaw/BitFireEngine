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

            const ActionResult fileActionResult = image.Load(L"C:/Users/BitPaw/Videos/TEST_PNG.png");

            Assert::IsTrue(fileActionResult == ResultSuccessful, L"Image PNG loading failed");
        }

        TEST_METHOD(TestLoadPNG)
        {
            Image image;

            const ActionResult fileActionResult = image.Load(L"C:/Users/BitPaw/Videos/TEST_PNG.png");

            Assert::IsTrue(fileActionResult == ResultSuccessful, L"Image PNG loading failed");
        }

        TEST_METHOD(TestLoadPNGSaveBMP)
        {
            Image image;

            const ActionResult fileLoadResult = image.Load(L"C:/Users/BitPaw/Videos/TEST_PNG.png");

            Assert::IsTrue(fileLoadResult == ResultSuccessful, L"Image PNG loading failed");

            const ActionResult fileSaveResult = image.Save(L"C:/Users/BitPaw/Videos/__Wurst.bmp", ImageFileFormat::BitMap);

            Assert::IsTrue(fileSaveResult == ResultSuccessful, L"Image PNG loading failed");
        }
    };
}
