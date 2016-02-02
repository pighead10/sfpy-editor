#include "Script.h"

Script::Script(){
}

Script::~Script(){
}

void Script::setName(std::string name){
	name_ = name;
}

void Script::setFilename(std::string filename){
	filename_ = filename;
}

std::string Script::getName() const{
	return name_;
}

std::string Script::getFilename() const{
	return filename_;
}
