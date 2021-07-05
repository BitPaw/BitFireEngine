#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BitFireEngineTest
{
	TEST_CLASS(StringTest)
	{
	public:
		
		TEST_METHOD(ContructorCString) // ContructorCString
		{
			BF::AsciiString stringA("ABC");

			Assert::AreEqual(3u, stringA.Size(), L"String lengh is not the same lengh as expected");
			Assert::AreEqual('A', stringA[0], L"First character is incorrect.");
			Assert::AreEqual('B', stringA[1], L"Secound character is incorrect.");
			Assert::AreEqual('C', stringA[2], L"Third character is incorrect.");
		}

		TEST_METHOD(ContructorStdString)
		{
			std::string stdString("ABC");
			BF::AsciiString stringA(stdString);

			Assert::AreEqual(3u, stringA.Size(), L"String lengh is not the same lengh as expected");
			Assert::AreEqual('A', stringA[0], L"First character is incorrect.");
			Assert::AreEqual('B', stringA[1], L"Secound character is incorrect.");
			Assert::AreEqual('C', stringA[2], L"Third character is incorrect.");
		}

		
		TEST_METHOD(Addable)
		{
			BF::AsciiString stringA("ABC");
			BF::AsciiString stringB("123");

			BF::AsciiString stringC = stringA + stringB;

			Assert::AreEqual(6u, stringC.Size(), L"String lengh is not the same lengh as expected");
			Assert::AreEqual('A', stringA[0], L"First character is incorrect.");
			Assert::AreEqual('B', stringA[1], L"Secound character is incorrect.");
			Assert::AreEqual('C', stringA[2], L"Third character is incorrect.");
			Assert::AreEqual('1', stringA[3], L"Fourth character is incorrect.");
			Assert::AreEqual('2', stringA[4], L"Fith character is incorrect.");
			Assert::AreEqual('3', stringA[5], L"Sixth character is incorrect.");
		}
		
		TEST_METHOD(SubString)
		{
			BF::List<BF::AsciiString> strings;
			BF::AsciiString csvText("1,2,3,4,5,6");

			csvText.Splitt(',', strings);

			Assert::AreEqual(6u, csvText.Size(), L"Splitted Size is wrong, expected different size.");
			Assert::IsTrue(strings[0] == "1", L"First text is incorrect.");
			Assert::IsTrue(strings[1] == "2", L"Secound text is incorrect.");
			Assert::IsTrue(strings[2] == "3", L"Third text is incorrect.");
			Assert::IsTrue(strings[3] == "4", L"Fourth text is incorrect.");
			Assert::IsTrue(strings[4] == "5", L"Fith text is incorrect.");
			Assert::IsTrue(strings[5] == "6", L"Sixth text is incorrect.");
		}
	};
}
