//Brett Sackstein
#ifndef DYNAMICARRAY
#define DYNAMICARRAY
#include "Song.h"

class  DynamicArray {
	private:
		int numSongs;
		int capacity;
		int Log;
		Song* songs;

	public:
		DynamicArray();
		DynamicArray(int maxSongs);
		Song* push_back(std::string title, std::string artist, std::string durationString, int playListTime, int maxSongs);
		size_t size();
		int getCapacity();
		Song& operator[](int index);
		~DynamicArray();
};

#endif
