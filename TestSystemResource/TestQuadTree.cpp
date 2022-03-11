#include "pch.h"
#include "CppUnitTest.h"

#include <Container/QuadTree/QuadTree.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BF;

namespace TestSystemResource
{
    TEST_CLASS(TestQuadTree)
    {
        public:
        TEST_METHOD(TestQuadTreeCreate)
        {
            QuadTree<double, int*> quadTree;

            Assert::IsTrue(fileActionResult == FileActionResult::Successful);
        }
    };
}
