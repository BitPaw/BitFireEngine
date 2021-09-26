DynamicCollectionsTest.run: DynamicCollectionsTest.o  Tester.o CollectionTester.o DictionaryTest.o LinkedListTest.o ListTest.o QueueTest.o StackTest.o String.o StringTest.o GeneralContainer.lib
	gcc -std=c11 bin/DynamicCollectionsTest.o bin/Tester.o bin/CollectionTester.o bin/DictionaryTest.o bin/LinkedListTest.o bin/ListTest.o bin/QueueTest.o bin/StackTest.o bin/String.o bin/StringTest.o bin/GeneralContainer.lib -o DynamicCollectionsTest.run


DynamicCollectionsTest.o: DynamicCollectionsTest/DynamicCollectionsTest.c
	gcc -c DynamicCollectionsTest/DynamicCollectionsTest.c -o bin/DynamicCollectionsTest.o

Tester.o: DynamicCollectionsTest/TestSystem/Tester.c
	gcc -c DynamicCollectionsTest/TestSystem/Tester.c -o bin/Tester.o

CollectionTester.o: DynamicCollectionsTest/TestSystem/CollectionTester.c
	gcc -c DynamicCollectionsTest/TestSystem/CollectionTester.c  -o bin/CollectionTester.o
