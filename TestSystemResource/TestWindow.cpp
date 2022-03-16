#include "pch.h"
#include "CppUnitTest.h"

#include <Window/Window.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BF;

namespace TestSystemResource
{
    TEST_CLASS(TestWindow)
    {
        public:
        TEST_METHOD(TestWindowCreate)
        {
            BF::Window window;

            window.Create();

            Assert::IsTrue(window.ID != 0);

            window.Destroy();
        }
    };
}
