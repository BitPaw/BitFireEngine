bin/ZEEGame.run: bin/ZEEGameSystem.o bin/Main.o
	gcc bin/ZEEGameSystem.o bin/Main.o -o bin/ZEEGameSystem.run 

bin/ZEEGameSystem.o: Source/ZEEGameSystem.cpp
	gcc -c Source/ZEEGameSystem.cpp -o bin/ZEEGameSystem.o

bin/Main.o: Source/Main.cpp
	gcc -c Source/Main.cpp -o bin/Main.o
