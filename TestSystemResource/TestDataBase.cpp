#include "pch.h"
#include "CppUnitTest.h"

#include <DataBase/DataBase.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BF;

namespace TestSystemResource
{
    TEST_CLASS(TestDataBase)
    {
        public:
        TEST_METHOD(TestDataBaseConnect)
        {
            DataBase dataBase;
            dataBase.ConnectToServer(L"BFDB");

            Assert::IsTrue(true);
        }
    };
}
