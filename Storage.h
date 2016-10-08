//Brett Sackstein
#ifndef STORAGE
#define STORAGE

#include "DynamicArray.h"
#include "MaxHeap.h"
#include "Time.h"
#include "HashTable.h"
#include "LinkedList.h"


class Storage{
	private:
		std::unique_ptr<DynamicArray> playList;
		std::unique_ptr<MaxHeap> playOrder;
		std::unique_ptr<HashTable> likeTable;

	public:
		Storage();
		Storage(int maxSongs);
		void add(std::string title, std::string artist, std::string durationString, int playListTime, int maxSongs);
		void setPlayOrder(int &size);
		void setPlayList(int &size);
		void setHashTable(int &size);
		Song* playSong(int currentClockTime);
		bool likeLastPlayed();
		bool likeSpecificSong(std::string toLike);
		bool dislikeLastPlayed();
		bool dislikeSpecificSong(std::string toDislike);
		int getPlayListSize();
		int getPlayListCapacity();
		void printList();
};

#endif