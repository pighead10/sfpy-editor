#pragma once
#include "Vector2.h"
#include <SFML/Graphics.hpp>

//Class for an instance of an Object that has been placed in the world

class Object;
class GameManager;

class Entity{
public:
	Entity(maths::Vector2 position, Object* type, GameManager* gameManager);
	~Entity();

	void setPosition(maths::Vector2 position);
	maths::Vector2 getPosition() const;

	const sf::Sprite& getSprite() const;
	const Object& getType() const;
private:
	void init_sprite();

	sf::Sprite sprite_;

	maths::Vector2 position_;
	Object* type_;
	GameManager* gameManager_;
};