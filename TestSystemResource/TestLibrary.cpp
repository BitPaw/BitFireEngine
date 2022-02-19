#include "pch.h"
#include "CppUnitTest.h"

#include <Library/Library.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BF;

namespace TestSystemResource
{
    TEST_CLASS(TestLibrary)
    {
        public:
        TEST_METHOD(TestRuntimeLibraryLinkMissingDLL)
        {
            Library library;
            const char* dllName = "USER420.dll";
            const bool libraryOpenSuccessful = library.Open(dllName);

            Assert::IsFalse(libraryOpenSuccessful, L"Shoud fail, but didn't");
        }

        TEST_METHOD(TestRuntimeLibraryLinkBeep)
        {
            Library library;

            typedef bool(__cdecl* MessageBeepFunction)(unsigned int);
            const char* dllName = "USER32.dll";
            const char* symbolName = "MessageBeep";

            const bool libraryOpenSuccessful = library.Open(dllName);

            Assert::IsTrue(libraryOpenSuccessful, L"Library failed to open, it's missing or could not be found.");

            const LibraryFunction funtion = library.GetSymbol(symbolName);
            const bool foundFunction = funtion != nullptr;

            Assert::IsTrue(foundFunction, L"Symbol was not found");

            const MessageBeepFunction messageBeepFunction = (MessageBeepFunction)funtion;

            unsigned int sucessCounter = 0;

            for (size_t i = 0; i < 3; i++)
            {
                bool result = messageBeepFunction(0);

                if (result)
                {
                    ++sucessCounter;
                }
            }

            Assert::IsTrue(sucessCounter == 3, L"Beebs failed");

            bool libraryCloseSuccessful = library.Close();

            Assert::IsTrue(libraryCloseSuccessful, L"Library failed to load properly");
        }
    };
}

