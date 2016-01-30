#include "Texture.h"

Texture::Texture(){

}

Texture::~Texture(){

}

const sf::Texture& Texture::getTexture() const{
	return texture_;
}

void Texture::setName(std::string name){
	name_ = name;
}

void Texture::setFilename(std::string filename){
	filename_ = filename;
	texture_.loadFromFile(filename);
}

std::string Texture::getName() const{
	return name_;
}

std::string Texture::getFilename() const{
	return filename_;
}