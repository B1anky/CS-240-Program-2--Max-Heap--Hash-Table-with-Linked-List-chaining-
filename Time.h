//Brett Sackstein
#ifndef TIME
#define TIME
#include <string>
#include <iostream>
#include <vector>


class Time{
	private:
		int day, hours, mins, secs, daysSeconds, totalSeconds, maxSongs;
	public:
		Time();
		Time(std::string timeIn, int maxSongsIn);
		std::string getTime();
		int getDay();
		int getHour();
		int getMin();
		int getSec();
		int getTotalSec();
		int getSongs();
		void setDay(int daysIn);
		void setHour(int hoursIn);
		void setMin(int minsIn);
		void setSec(int secsIn);
		void setTotalTime(int totalTimeIn);
		void setSongs(int maxSongsIn);
		void deltaTime(int delta);
		void rest(std::string timeString);
		std::vector<std::string> splitstring(std::string a, std::string delim);
		int GetSecondsFromString(std::string& a);
};

#endif
