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
            BF::DataBase dataBase;

            dataBase.Connect
            (
                L"127.0.0.1",
                L"waffledb",
                L"root",
                L""
            );

            dataBase.Execute(L"select* from waffle;");

            dataBase.Disconnect();


            Assert::IsTrue(true);
        }
    };
}
