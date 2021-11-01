using System;
using System.Collections.Generic;
using System.IO;

namespace MakeFileCreator
{
    class Program
    {
        static string libyrayName = "";
        static string allBinObjects = "";

        static string outPutBuffer = "";


        static string CoreDirectory;

        static void LoopDir(string rootDirectory)
        {
            string[] files = Directory.GetFiles(rootDirectory);

            foreach (string item in files)
            {
                bool validFile = item.EndsWith("hpp") || item.EndsWith("c") || item.EndsWith("cpp");

                if (!validFile)
                {
                    continue;
                }

                string filePath = item.Replace("\\", "/");
                int index = filePath.LastIndexOf('/');
                int lastindex = filePath.LastIndexOf('.');

                string rawPath = filePath.Substring(index + 1, lastindex - (index + 1));

                string binPath = "bin/" + rawPath + ".o";

                   allBinObjects += binPath + " ";

                string finalWrite = binPath + ": " + filePath + "\n\tgcc -c " + filePath + " -o " + binPath + "\n\n";

                outPutBuffer += finalWrite;
            }

            string[] directorys = Directory.GetDirectories(rootDirectory);

            foreach (string directory in directorys)
            {
                LoopDir(directory);
            }
        }

        static void Main()
        {

            string makefilePath = "MakeFile.mak"; 

            File.Delete(makefilePath);

            //rootDirectory = Console.ReadLine();

            //rootDirectory = "A:/_WorkSpace/Git/BitFireEngine_B/BitFireEngine/SystemResource/Source";

            CoreDirectory = Directory.GetCurrentDirectory();

 
             LoopDir(CoreDirectory);

            libyrayName = Path.GetDirectoryName(CoreDirectory);

            string libaryCompile = "bin/" + libyrayName + ".lib: " + allBinObjects + " \n\rar rcs bin/" + libyrayName + ".lib " + allBinObjects;


            File.WriteAllText(makefilePath, libaryCompile + outPutBuffer);
        }
    }
}
