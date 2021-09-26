bin/OSDefine.o: Source/OSDefine.h
	gcc -c Source/OSDefine.h -o bin/OSDefine.o


bin/FileName.o: Path
\t gcc -c Path -o FileName.o
