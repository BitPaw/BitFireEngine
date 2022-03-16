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
            struct PseudoSprite
            {
                char ID;
                Rectangle<float> Border;     

                PseudoSprite(char id, Rectangle<float> border)
                {
                    ID = id;
                    Border = border;
                }
            };

            QuadTree<float, PseudoSprite*> quadTree(0, 0, 100, 100);


            PseudoSprite spriteList[3] = 
            {
                PseudoSprite('A', Rectangle<float>(0,0,50,50)),
                PseudoSprite('B', Rectangle<float>(75,75,10,10)),
                PseudoSprite('C', Rectangle<float>(25,25,25,25))
            };

            for (size_t i = 0; i < 1; i++)
            {
                PseudoSprite& sprite = spriteList[i];

                QuadTreeResult quadTreeResult = quadTree.Insert(sprite.Border.X, sprite.Border.Y, sprite.Border.Width, sprite.Border.Height, &sprite);
       
                Assert::IsTrue(quadTreeResult == QuadTreeResult::Success);
            }

            Assert::IsTrue(true);
        }
    };
}
