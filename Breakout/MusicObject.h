#pragma once
#include "SFML\Audio.hpp"

#include "SFML\Audio.hpp"

class MusicObject
{
public:
	MusicObject();
	~MusicObject();
	
	void setMusic(std::string lfilename, std::string lname);

	std::string filename;
	std::string name;
};