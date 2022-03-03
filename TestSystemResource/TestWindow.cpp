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
            WindowID windowID = Window::Create();

            Assert::IsTrue(windowID != 0);
        }
    };
}
