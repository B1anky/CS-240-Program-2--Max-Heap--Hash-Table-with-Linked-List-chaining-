//Brett Sackstein
#include "Storage.h"

Storage::Storage(){
	//literally do nothing
}

Storage::Storage(int maxSongs){
	setPlayOrder(maxSongs);
	setPlayList(maxSongs);
	setHashTable(maxSongs);
}

void Storage::add(std::string title, std::string artist, std::string durationString, int playListTime, int maxSongs){
	Song* toAdd = playList->push_back(title, artist, durationString, playListTime, maxSongs);
	playOrder->Enqueue(toAdd, playListTime);
	Item *hashAdd = new Item();
	hashAdd->key = toAdd;
	likeTable->insertItem(hashAdd);
}

Song* Storage::playSong(int currentClockTime){
	if(playOrder->getHeapSize() > 1){
		Song *toPlay = playOrder->Dequeue(currentClockTime);
		if(toPlay){
			toPlay->updateTimeLastPlayed(currentClockTime + toPlay->getDuration());
			playOrder->Enqueue(toPlay, currentClockTime);
			return toPlay;
		}else{
			return NULL;
		}
		
	}else if(playOrder->getHeapSize() == 1){
		Song *toPlay = playOrder->getData(0);
		toPlay->updateTimeLastPlayed(currentClockTime + toPlay->getDuration());
		playOrder->setLastPlayed(toPlay);
		std::cout << "Playing " << toPlay->getAllInfo() << std::endl;
		return toPlay;
	}else{
		return NULL;
	}
}

bool Storage::likeLastPlayed(){
	if(playOrder->getLastPlayed()){
		playOrder->getLastPlayed()->updateLikeability(1);
		return true;
	}else{
		return false;
	}
}

bool Storage::likeSpecificSong(std::string toLike){
	if(likeTable->getItemByKey(toLike)){
		likeTable->getItemByKey(toLike)->key->updateLikeability(1);
		return true;
	}else{
		return false;
	}
}

bool Storage::dislikeLastPlayed(){
	if(playOrder->getLastPlayed()){
		playOrder->getLastPlayed()->updateLikeability(0);
		return true;
	}else{
		return false;
	}
}

bool Storage::dislikeSpecificSong(std::string toDislike){
	if(likeTable->getItemByKey(toDislike)){
		likeTable->getItemByKey(toDislike)->key->updateLikeability(0);
		return true;
	}else{
		return false;
	}
}

void Storage::setPlayOrder(int &size){
	playOrder = std::unique_ptr<MaxHeap>(new MaxHeap(size));
}

void Storage::setPlayList(int &size){
	playList = std::unique_ptr<DynamicArray>(new DynamicArray(size));
}

void Storage::setHashTable(int &size){
	likeTable = std::unique_ptr<HashTable>(new HashTable(size));
}

int Storage::getPlayListCapacity(){
	return playList->getCapacity();
}

int Storage::getPlayListSize(){
	return playList->size();
}

void Storage::printList(){
	for(int i = 0; i < playOrder->getHeapSize(); i++){
		std::cout << playOrder->getData(i)->getAllInfo() << ". Priority: " << playOrder->getData(i)->getPriority() << std::endl;
	}
}
