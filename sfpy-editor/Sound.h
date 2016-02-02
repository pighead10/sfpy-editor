#pragma once

#include <string>

//TODO ADD PROPERTIES

class Sound{
public:
	Sound();
	~Sound();

	void setName(std::string name);
	void setFilename(std::string filename);

	std::string getName() const;
	std::string getFilename() const;
private:
	std::string name_;
	std::string filename_;
};