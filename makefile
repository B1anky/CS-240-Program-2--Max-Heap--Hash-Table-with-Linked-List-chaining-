
FLAGS = -g -Wall -pedantic -Wextra -Wno-sign-compare -Wno-unused-but-set-variable -Wno-unused-parameter -std=c++11

all: clean program2

program2: Time.o Song.o MaxHeap.o DynamicArray.o HashTable.o LinkedList.o Storage.o program2.o 
	g++ $(FLAGS) Time.o Song.o MaxHeap.o DynamicArray.o HashTable.o LinkedList.o Storage.o program2.o -o program2

Time.o: Time.cpp  Time.h
	g++ $(FLAGS) -c Time.cpp -o Time.o

Song.o: Song.cpp Song.h
	g++ $(FLAGS) -c Song.cpp -o Song.o

program2.o: program2.cpp
	g++ $(FLAGS) -c program2.cpp -o program2.o

MaxHeap.o: MaxHeap.cpp MaxHeap.h
	g++ $(FLAGS) -c MaxHeap.cpp -o MaxHeap.o

DynamicArray.o: DynamicArray.cpp DynamicArray.h
	g++ $(FLAGS) -c DynamicArray.cpp -o DynamicArray.o

Storage.o: Storage.cpp Storage.h
	g++ $(FLAGS) -c Storage.cpp -o Storage.o

HashTable.o: HashTable.cpp HashTable.h
	g++ $(FLAGS) -c HashTable.cpp -o HashTable.o

LinkedList.o: LinkedList.cpp LinkedList.h
	g++ $(FLAGS) -c LinkedList.cpp -o LinkedList.o

clean:
	rm -f *.o program2

