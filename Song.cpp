//Brett Sackstein
#include "Song.h"

Song::Song(){
	artist = "...";
	title = "...";
	duration = 0;
	likeability= 0;
	timeLastPlayed = 0;
	priority = 0;
}

Song::Song(std::string titleIn, std::string artistIn, std::string durationIn, int currentClock){
	artist = artistIn;
	title = titleIn;
	duration = GetSecondsFromString(durationIn);
	likeability = 0;
	timeLastPlayed = currentClock + duration;
	priority = timeLastPlayed + (1000 * likeability); 
}

Song::Song(const Song& s){
	if(this != &s)
	{
		artist = s.artist;
		title = s.title;
		duration = s.duration;
		likeability = s.likeability;
		timeLastPlayed = s.timeLastPlayed;
		priority = s.priority; 
	}
}

Song& Song::operator=(const Song& s){
	//std::cout << "Assign: " <<  s.getAllInfo() << std::endl;
	if(this != &s){
		artist = s.artist;
		title = s.title;
		duration = s.duration;
		likeability = s.likeability;
		timeLastPlayed = s.timeLastPlayed;
		priority = s.priority; 
	}
	//std::cout << "Finish assign\n";
	return *this;
}

std::string Song::getAllInfo()const {
	std::string output = "";
	output += title;
	output += " by ";
	output += artist;
	output += ": ";
	output += timeConvert();
	return output;
}


std::string Song::getArtist()const 
{
	return artist;
}

std::string Song::getTitle()const {return title;}

int Song::getLikeability()const {return likeability;}

int Song::getTimeLastPlayed()const {return timeLastPlayed;}

int Song::getPriority()const {return priority;}

int Song::getDuration()const {return duration;}

std::string Song::getSong()const {
	return getTitle() + " by " + getArtist();
}

void Song::setArtist(std::string artistIn){artist = artistIn;}

void Song::setTitle(std::string titleIn){title = titleIn;}

void Song::setDuration(int durationIn){duration = durationIn;}

void Song::updateTimeLastPlayed(int currentClockTime){
	timeLastPlayed = currentClockTime;
	updatePriority();
}

void Song::updateLikeability(int likeOrNot){
	if(likeOrNot == 1){
		if(likeability > 0){
			likeability++;
		}else{
			likeability = 1;
		}
	}else{
		if(likeability > 0){
			likeability = -1;
		}else{
			likeability--;
		}
	}
	updatePriority();
}

void Song::updatePriority(){
	priority = 1000 * likeability;
}

std::vector<std::string> Song::splitstring(std::string a, std::string delim)
{
	std::vector<std::string>  ret;
	size_t pos = 0;
	std::string token;
	while ((pos = a.find(delim)) != std::string::npos) {
		token = a.substr(0, pos);
		ret.push_back(token);
		//std::cout << token << std::endl;
		a.erase(0, pos + delim.length());
	}
	return ret;
} 

int Song::GetSecondsFromString(std::string& a){
	a+= ":";
	//std::cout << "A:" << a << std::endl;

	std::vector<std::string> s = splitstring(a, ":");
	int hours = 0;
	int mins = 0;
	int secs = 0;
	switch(s.size()){
		case 3: //hour:minute:second
			hours = atoi(s[0].c_str());
			mins = atoi(s[1].c_str());
			secs = atoi(s[2].c_str());
		break;
		case 2://minute:second
			mins = atoi(s[0].c_str());
			secs = atoi(s[1].c_str());
		break;
		case 1:
			secs = atoi(s[0].c_str());
		break;
		case 0:
		default:
			return 0;
	}

	while(hours != 0){
		mins += 60;
		hours--;
	}

	while(mins != 0){
		secs += 60;
		mins--;
	}
	
	return secs;
}

std::string Song::timeConvert() const{
	std::string timeInfo = "";
	//hh::mm::ss
	if(duration >= 3600){
		int hours = (getDuration() / 60 / 60) % 24;
		timeInfo += std::to_string(hours);
		timeInfo += ":";
		int minutes = (getDuration() / 60) % 60;
		if(minutes < 10){
			timeInfo += "0";
		}
		timeInfo += std::to_string(minutes);
		timeInfo += ":";
		int seconds = getDuration() % 60;
		if(seconds < 10){
			timeInfo += "0";
		}
		timeInfo += std::to_string(seconds);
	//mm::ss 10 min - 1 hour
	}else if(getDuration() >= 600 && getDuration() < 3600){
		int minutes = (getDuration() / 60) % 60;
		timeInfo += std::to_string(minutes);
		timeInfo += ":";
		int seconds = getDuration() % 60;
		if(seconds < 10){
			timeInfo += "0";
		}
		timeInfo += std::to_string(seconds);
	//hh::mm::ss 1 min - 10 min
	}else if(getDuration() >= 60 && getDuration() < 600 && getDuration() < 3600){
		timeInfo += "0";
		int minutes = (getDuration() / 60) % 60;
		timeInfo += std::to_string(minutes);
		timeInfo += ":";
		int seconds = getDuration() % 60;
		if(seconds < 10){
			timeInfo += "0";
		}
		timeInfo += std::to_string(seconds);
	//00::ss
	}else{
		timeInfo += "00:";
		int seconds = getDuration() % 60;
		if(seconds < 10){
			timeInfo += "0";
		}
		timeInfo += std::to_string(seconds);
	}
	return timeInfo;
}

//Just compares priority of songs to determine place in heap
bool Song::operator >(Song otherSong){
	//std::cout << "OVERLOADING >" << std::endl;
	if(this->priority > otherSong.priority){
		return true;
	}else{
		return false;
	}
}

