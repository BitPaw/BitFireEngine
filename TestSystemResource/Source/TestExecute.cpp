#include "pch.h"
#include "CppUnitTest.h"

#include <File/Program.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BF;

namespace TestSystemResource
{
    TEST_CLASS(TestExecute)
    {
		private:
		struct ExeLis : BF::ProgramExecuteResultListener
		{
			virtual void OnProgramExecuted(bool succesful, intptr_t returnResult, ErrorCode errorCode) override
			{				
				printf("Sucess exe \n");
			}
		} executeListener;

        public:
		TEST_METHOD(TestExecuteProgramA)
		{
			char bufA[260];
			char bufb[260];

			strncpy_s(bufb, "C:\\Users\\BitPaw\\Videos\\E\\Server.exe", 420);
			strncpy_s(bufA, "C:\\Users\\BitPaw\\Videos\\E\\PP.input", 420);

			const char* dummy = "A:\\_Cache\\DummyProgram.exe";

			const char* a = "0";
			const char* exe = "N:\\Schule\\Studium\\Semester\\Semester 5\\[VS] Verteilte Systeme\\Aufgabe\\ClusterWorker\\Program\\x64\\Release\\VSServerDelegatorPrimes.exe";

			const char* b = "N:\\Schule\\Studium\\Semester\\Semester 5\\[VS] Verteilte Systeme\\Aufgabe\\ClusterWorker\\Program\\x64\\Release\\_InputServer.txt";
			const char* parameter[2] = { a, b };
			const char** ww = (const char**)&parameter;

			Program::Execute(dummy, "0 \"LigmaBallz\"", &executeListener);
		}

        TEST_METHOD(TestExecuteProgramB)
        {				
			Program::Execute
			(
				"N:/Schule/Studium/Semester/Semester 5/[VS] Verteilte Systeme/Aufgabe/ClusterWorker/Program/VSClient/DummyProgram.exe",
				nullptr,
				&executeListener
			);


				Program program;

			ActionResult fileActionResult = program.Execute("DummyProgram.exe", 0, 0);		


            Assert::IsTrue(fileActionResult == ResultSuccessful);
        }
    };
}
