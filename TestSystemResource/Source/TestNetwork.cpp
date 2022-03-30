#include "pch.h"
#include "CppUnitTest.h"
#include <Network/Server.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BF;

namespace TestSystemResource
{
    TEST_CLASS(TestNetwork)
    {
        public:
		TEST_METHOD(TestServerStart)
		{
			Server server;
			const SocketActionResult serverCreateResult = server.Start(25666);

			Assert::IsTrue(serverCreateResult == SocketActionResult::Successful);

			/*const SocketActionResult serverCreateResult = */ server.Stop();

			//Assert::IsTrue(serverCreateResult == SocketActionResult::Successful);
		}

        TEST_METHOD(TestServerClient)
        {
			const short port = 25666;

			Server server;
			SocketActionResult serverCreateResult = server.Start(port);

			Client client;
			unsigned int counter = 0;
			char buffer[50];

			SocketActionResult socketActionResult = client.ConnectToServer("localhost", port);

			for (size_t i = 0; i < 10 && client.IsCurrentlyUsed(); i++)
			{
				size_t readSize = sprintf_s(buffer, 50, "Hello x%i", ++counter);

				SocketActionResult socketActionResult = client.Send(buffer, readSize);

				Assert::IsTrue(socketActionResult == SocketActionResult::Successful, L"Sending failure");

				Sleep(500);
			}
		
			client.Disconnect();

			server.Stop();           
        }      
    };
}
