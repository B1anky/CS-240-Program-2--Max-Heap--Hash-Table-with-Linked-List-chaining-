//Brett Sackstein
#include "DynamicArray.h"

DynamicArray::DynamicArray(){
	this->capacity = 0;
	this->numSongs = 0;
	songs = 0;
	Log = 0;
}

DynamicArray::DynamicArray(int maxSongs){
	this->capacity = maxSongs;
	songs = new Song[maxSongs];
	this->numSongs = 0;
	Log = 0;
}

Song* DynamicArray::push_back(std::string title, std::string artist, std::string durationString, int playListTime, int maxSongs) {
	Song toAdd(title, artist, durationString, playListTime);
	if (this->numSongs >= this->capacity) {
		std::cout << "HERE" << std::endl;
		Song * nSong = new Song[1<<Log];
		this->capacity =1<<Log;
		Log++;
		for (int i = 0; i < this->numSongs; i++)
			nSong[i] = songs[i];
		delete[] songs;
		songs = nSong;
	}
	songs[this->numSongs] = toAdd;
	return &songs[this->numSongs++] ;
}

size_t DynamicArray::size() {
	return this->numSongs;
}

int DynamicArray::getCapacity(){
	return capacity;
}

Song& DynamicArray::operator[](int index) {
	return songs[index];
}

DynamicArray::~DynamicArray() {
	delete[] songs;
}

