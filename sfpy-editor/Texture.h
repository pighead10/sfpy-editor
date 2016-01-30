#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class Texture{
public:
	Texture();
	~Texture();

	void setName(std::string name);
	void setFilename(std::string filename);

	std::string getName() const;
	std::string getFilename() const;

	const sf::Texture& getTexture() const;

private:
	sf::Texture texture_;

	std::string name_;
	std::string filename_;
};