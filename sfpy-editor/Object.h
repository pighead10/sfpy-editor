#pragma once

#include <map>
#include <string>

typedef std::map<std::string, std::string> PropertyMap;

//Class for each individual object type (not object that is placed on the map)

class Object{
public:
	Object();
	~Object();


	void addProperty(std::string name, std::string value);
	void setName(std::string name);

	std::string getProperty(std::string name) const;
	std::string getName() const;
private:
	std::string name_;
	PropertyMap properties_;
};