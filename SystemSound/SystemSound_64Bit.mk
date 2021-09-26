bin/SystemSound.lib: bin/AudioConfig.o bin/AudioSource.o bin/SystemSound.o
	ar rcs bin/SystemSound.lib bin/AudioConfig.o bin/AudioSource.o bin/SystemSound.o

bin/AudioConfig.o: Source/AudioConfig.cpp
	gcc -c Source/AudioConfig.cpp -o bin/AudioConfig.o

bin/AudioSource.o: Source/AudioSource.cpp
	gcc -c Source/AudioSource.cpp -o bin/AudioSource.o

bin/SystemSound.o: Source/SystemSound.cpp
	gcc -c Source/SystemSound.cpp -o bin/SystemSound.o
