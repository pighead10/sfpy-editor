#include "Sound.h"

Sound::Sound(){
}

Sound::~Sound(){
}

void Sound::setName(std::string name){
	name_ = name;
}

void Sound::setFilename(std::string filename){
	filename_ = filename;
}

std::string Sound::getName() const{
	return name_;
}

std::string Sound::getFilename() const{
	return filename_;
}
