#include "MusicObject.h"

MusicObject::MusicObject()
{
}

MusicObject::~MusicObject()
{
}

void MusicObject::setMusic(std::string lfilename, std::string lname)
{
	filename = lfilename;
	name = lname;
}
