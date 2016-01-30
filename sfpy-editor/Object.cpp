#include "Object.h"

Object::Object(){
}

Object::Object(){
}

void Object::addProperty(std::string name, std::string value){
	properties_[name] = value;
}

void Object::setName(std::string name){
	name_ = name;
}

std::string Object::getName() const{
	return name_;
}

std::string Object::getProperty(std::string name) const{
	auto result = properties_.find(name);
	if (result == properties_.end()){
		return "";
	}
	else{
		return properties_.at(name);
	}
}