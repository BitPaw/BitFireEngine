#include "pch.h"
#include "CppUnitTest.h"

#include <Media/Font/TTF/TTF.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BF;

namespace TestSystemResource
{
    TEST_CLASS(TestFont)
    {
        public:
        TEST_METHOD(TestLoadTTF)
        {
            TTF ttf;
            const FileActionResult fileActionResult = ttf.Load(L"A:/_WorkSpace/BOOKOSI.TTF");

            Assert::IsTrue(fileActionResult == FileActionResult::Successful);
        }
    };
}
