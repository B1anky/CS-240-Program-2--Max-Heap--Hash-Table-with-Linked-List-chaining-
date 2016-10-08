//Brett Sackstein
#include "Song.h"
#include "Time.h"
#include "MaxHeap.h"
#include "DynamicArray.h"
#include "Storage.h"
#include "HashTable.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cctype>
#include <string>

void run(std::string fileName, Time &playListTime, std::vector<std::string> output, std::unique_ptr<Storage>& storage, bool &isInit, bool &keepGoing);
void choiceAdd(int i, std::vector<std::string> &commands, Time &playListTime, std::unique_ptr<Storage> &storage, std::vector<std::string> &output);
void choiceRest(int i, std::vector<std::string> &commands, Time &playListTime);
Time choiceInit(int i, std::vector<std::string> &commands, std::unique_ptr<Storage> &storage);
void printBeforeQuit(std::vector<std::string> output, std::unique_ptr<Storage> &storage);
void choicePlay(int i, std::vector<std::string> &commands, Time &playListTime, std::unique_ptr<Storage> &storage);
void choiceLike(int i, std::vector<std::string> &commands, Time &playListTime, std::unique_ptr<Storage> &storage);
void choiceDislike(int i,  std::vector<std::string> &commands, Time &playListTime, std::unique_ptr<Storage> &storage);

int main(){
	std::string userInput = "";
	bool keepGoing = true;
	Time playListTime;
	std::vector<std::string> currentCommand;
	std::vector<std::string> output;
	std::unique_ptr<Storage> storage;
	bool isInit = false;
	while(keepGoing){
		std::cout << "Please type a command: ";
		getline(std::cin, userInput);
		currentCommand.push_back(userInput);

		std::string option = "";
		for(int j = 0; j < currentCommand[0].length() ; j++){
			if(!isspace(currentCommand[0][j])){
				option += currentCommand[0][j];
			}else{
				break;
			}
		}

		//userInput = "RUN";
		if(option == "RUN"){
			int paramCount = 0;
			std::string fileName = "";
			for(int j = 0; j < currentCommand[0].length(); j++){
				if(!isspace(currentCommand[0][j]) && paramCount == 0){
					//do nothing, it's reading 'RUN'
				}else if(!isspace(currentCommand[0][j]) && paramCount == 1){
					fileName += currentCommand[0][j];
				}else{
					//Hit whitespace
					paramCount++;
				}
			}

			run(fileName, playListTime, output, storage, isInit, keepGoing);
			currentCommand.clear();
		}else if(option == "INIT" && !isInit){
			std::cout << "Initializing ";
			playListTime = choiceInit(0, currentCommand, storage);
			isInit = true;
			currentCommand.clear();
		}else if(option == "PLAY" && isInit){
			choicePlay(0, currentCommand, playListTime, storage);
			currentCommand.clear();
		}else if(option == "LIKE" && isInit){
			choiceLike(0, currentCommand, playListTime, storage);
			currentCommand.clear();
		}else if(option == "DISLIKE" && isInit){
			choiceDislike(0, currentCommand, playListTime, storage);
			currentCommand.clear();
		}else if(option == "ADD" && isInit){
			choiceAdd(0, currentCommand, playListTime, storage, output);
			currentCommand.clear();
		}else if(option == "REST" && isInit){
			choiceRest(0, currentCommand, playListTime);
			currentCommand.clear();
		}else if(option == "QUIT"){
			currentCommand.clear();
			std::cout << playListTime.getTime() << " Quitting..." << std::endl;
			keepGoing = false;
		}else{
			std::cout << playListTime.getTime() << "\033[1;31m Error. Not a recognized command or storage hasn't been initialized.[0m" << std::endl;
			currentCommand.clear();
		}
	}
	return 0;
}

void run(std::string fileName, Time &playListTime, std::vector<std::string> output, std::unique_ptr<Storage>& storage, bool &isInit, bool &keepGoing){
	std::ifstream infile(fileName);
	std::string line;
	std::vector<std::string> commands;

	while (std::getline(infile, line)){
		//Readline character and newline character parsing
		if(!line.empty() && (line[line.length()-1] == '\n' || line[line.length()-1] == '\r')){
			line.erase(line.length()-1);
		}
		//Add commands to a vector because won't know size
		//until run time
		commands.push_back(line);
	}
	std::cout << "\033[1;32m**File has been loaded in**[0m" << std::endl;
	infile.close();

	for(int i = 0; i < commands.size(); i++){
		//std::cout <<"index "<< i <<": "<< commands[i] << std::endl;
		std::string option = "";
		for(int j = 0; j < commands[i].length() ; j++){
			if(!isspace(commands[i][j])){
				option += commands[i][j];
			}else{
				break;
			}
		}

		if(option == "INIT" && !isInit){
			std::cout << "Initializing ";
			playListTime = choiceInit(i, commands, storage);
			isInit = true;
		}else if(option == "PLAY" && isInit){
			choicePlay(i, commands, playListTime, storage);
		}else if(option == "LIKE" && isInit){
			choiceLike(i, commands, playListTime, storage);
		}else if(option == "DISLIKE" && isInit){
			choiceDislike(i, commands, playListTime, storage);
		}else if(option == "ADD" && isInit){
			choiceAdd(i, commands, playListTime, storage, output);
		}else if(option == "REST" && isInit){
			choiceRest(i, commands, playListTime);
		}else if(option == "QUIT"){
			std::cout << playListTime.getTime() << " Quitting..." << std::endl;
			keepGoing = false;
		}else{
			//do nothing, unrecognized command
		}
	}
	return;
}

Time choiceInit(int i, std::vector<std::string> &commands, std::unique_ptr<Storage> &storage){
	std::string timeOfDay = "";
	std::string maxSongsString = "";
	int paramCount = 0;
	for(int j = 0; j < commands[i].length(); j++){

		if(!isspace(commands[i][j]) && paramCount == 0){
			//do nothing, it's reading 'INIT'
		}else if(!isspace(commands[i][j]) && paramCount == 1){
			timeOfDay += commands[i][j];
		}else if(!isspace(commands[i][j]) && paramCount == 2){
			maxSongsString += commands[i][j];
		}else{
			//Hit whitespace
			paramCount++;
		}
	}
	std::cout << "time to " << timeOfDay << ", with a maximum amount of " << maxSongsString << " songs." <<std::endl;
	int maxSongs = atoi(maxSongsString.c_str());
	Time playListTime(timeOfDay, maxSongs);
	std::unique_ptr<Storage> tempNew(new Storage(maxSongs));
	storage.swap(tempNew);
	return playListTime;
}

void choicePlay(int i, std::vector<std::string> &commands, Time &playListTime, std::unique_ptr<Storage>& storage){
	std::string playCountString = "";
	int paramCount = 0;
	for(int j = 0; j < commands[i].length(); j++){
		if(!isspace(commands[i][j]) && paramCount == 0){
			//do nothing, it's reading 'PLAY'
		}else if(!isspace(commands[i][j]) && paramCount == 1){
			playCountString += commands[i][j];
		}else{
			//Hit whitespace
			paramCount++;
		}
	}
	if(atoi(playCountString.c_str()) == 1){
		//Remove only the first song from the top of the heap
		std::cout << playListTime.getTime() << " ";
		Song *toPlay = storage->playSong(playListTime.getTotalSec());
		if(toPlay){
			playListTime.deltaTime(toPlay->getDuration());
		}else{
			std::cout << "\033[1;31mError. No song was added yet.[0m" << std::endl;
		}
	}else{
		int playCount = atoi(playCountString.c_str());
		for(int i = 0; i < playCount; i++){
			std::cout << playListTime.getTime() << " ";
			Song *toPlay = storage->playSong(playListTime.getTotalSec());
			if(toPlay){
				playListTime.deltaTime(toPlay->getDuration());
			}else{
				std::cout << "\033[1;31mError. No song was added yet.[0m" << std::endl;
			}
		}
	}
}

void choiceLike(int i, std::vector<std::string> &commands, Time &playListTime, std::unique_ptr<Storage>& storage){
	std::string songToLike = "";
	int paramCount = 0;
	bool error = false;
	if(commands[i] == "LIKE"){
		error = storage->likeLastPlayed();
		if(error == false){
			std::cout << playListTime.getTime() << "\033[1;31m Error. No song was played yet.[0m" << std::endl;
		}else{
			std::cout << playListTime.getTime() << " " << "Liked the most recently played song." << std::endl;
		}
	}else{
		for(int j = 0; j < commands[i].length(); j++){
			if(!isspace(commands[i][j]) && paramCount == 0){
				//do nothing, it's reading 'LIKE'
			}else if(paramCount == 1){
				songToLike += commands[i][j];
			}else{
				paramCount++;
			}
		}
		//Use hash table
		error = storage->likeSpecificSong(songToLike);
		if(error == false){
			std::cout << playListTime.getTime() << "\033[1;31m Error. Song not liked, because it was not in the playlist.[0m" << std::endl;

		}else{
			std::cout << playListTime.getTime() << " Liked " << songToLike << "." << std::endl;
		}
	}
}

void choiceDislike(int i, std::vector<std::string> &commands, Time &playListTime, std::unique_ptr<Storage>& storage){
	std::string songToDislike = "";
	int paramCount = 0;
	bool error = false;

	if(commands[i] == "DISLIKE"){
		error = storage->dislikeLastPlayed();
		if(error == false){
			std::cout << playListTime.getTime() << "\033[1;31m Error. No song was last played.[0m" << std::endl;
		}else{
			std::cout << playListTime.getTime() << " Disliked the most recently played song." << std::endl;
		}
	}else{
		for(int j = 0; j < commands[i].length(); j++){
			if(!isspace(commands[i][j]) && paramCount == 0){
				//do nothing, it's reading 'DISLIKE'
			}else if(paramCount == 1){
				songToDislike += commands[i][j];
			}else{
				paramCount++;
			}
		}
		//Use hash table
		error = storage->dislikeSpecificSong(songToDislike);
		if(error == false){
			std::cout << playListTime.getTime() << "\033[1;31m Error. Song not disliked, because it was not in the playlist.[0m" << std::endl;
		}else{
			std::cout << playListTime.getTime() << " Disliked " << songToDislike << "." << std::endl;
		}
	}
}

void choiceAdd(int i, std::vector<std::string> &commands, Time &playListTime, std::unique_ptr<Storage>& storage, std::vector<std::string> &output){
	if(storage->getPlayListSize() >= storage->getPlayListCapacity()){
		std::cout << playListTime.getTime() << " " << "\033[1;31mError Adding. Play list is full.[0m" << std::endl;
	}else{
		std::string artist = "";
		std::string title = "";
		std::string durationString = "";
		int paramCount = 0;
		for(int j = 0; j < commands[i].length(); j++){
			if(!isspace(commands[i][j]) && paramCount == 0){
				//do nothing, it's reading 'ADD'
			}else if(commands[i][j] != ',' && paramCount == 1){
				title += commands[i][j];
			}else if(commands[i][j] != ',' && paramCount == 2){
				artist += commands[i][j];
			}else if(commands[i][j] != ',' && paramCount == 3){
				durationString += commands[i][j];
			}else{
				//Hit whitespace
				paramCount++;
			}
		}
		//Need to erase whitespace after title comma
		artist.erase(artist.begin());
		std::cout << playListTime.getTime() << " " << "Adding "<< title << " by " << artist << "." << std::endl;
		storage->add(title, artist, durationString, playListTime.getTotalSec(), playListTime.getSongs());
	}
}

void choiceRest(int i, std::vector<std::string> &commands, Time &playListTime){
	std::string durationString = "";
	int paramCount = 0;
	for(int j = 0; j < commands[i].length(); j++){
		if(!isspace(commands[i][j]) && paramCount == 0){
			//do nothing, it's reading 'REST'
		}else if(!isspace(commands[i][j]) && paramCount == 1){
			durationString += commands[i][j];
		}else{
			//Hit whitespace
			paramCount++;
		}
	}
	std::cout << playListTime.getTime() << " Resting for " << durationString << "." << std::endl;
	playListTime.rest(durationString);
}
/*
void printBeforeQuit(std::vector<std::string> output, std::unique_ptr<Storage>& storage){
	std::cout << "\n----OUTPUT----\n" <<std::endl;
	storage->printList();
	
	for(int i = 0; i < storage.getPlayOrder().getHeapSize(); i++){
		std::cout << storage.getPlayOrder().getData(i)->getAllInfo() << ". Priority: " << storage.getPlayOrder().getData(i)->getPriority() << std::endl;
	}
	
}
*/
