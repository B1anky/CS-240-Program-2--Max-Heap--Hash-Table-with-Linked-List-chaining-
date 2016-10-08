//Brett Sackstein
#ifndef SONG
#define SONG
#include <string>
#include <vector>
#include <iostream>
class Song{

	private:	
		std::string artist;
		std::string title;
		int duration;
		int likeability;
		int timeLastPlayed;
		int priority;

	public:
		Song();
		Song(std::string titleIn, std::string artistIn, std::string durationIn, int currentClock);
		Song(const Song& s);
		Song& operator=(const Song& s);
		std::string getArtist()const ;
		std::string getTitle()const ;
		std::string getSong()const ;
		std::string timeConvert()const;
		std::string getAllInfo()const ;
		int getLikeability()const ;
		int getTimeLastPlayed()const ;
		int getPriority()const ;
		int getDuration()const ;
		std::vector<std::string> splitstring(std::string a, std::string delim);
		int GetSecondsFromString(std::string& a);
		void setArtist(std::string artistIn);
		void setTitle(std::string titleIn);
		void setDuration(int durationIn);
		void updateLikeability(int likeOrNot);
		void updateTimeLastPlayed(int currentClock);
		void updatePriority();
		bool operator >(Song otherSong);

};

#endif
