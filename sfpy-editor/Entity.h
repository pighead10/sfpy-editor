#pragma once
#include "Vector2.h"
#include <SFML/Graphics.hpp>

//Class for an instance of an Object that has been placed in the world

class Object;
class GameManager;

class Entity{
public:
	Entity(GameManager* gameManager);
	Entity(GameManager* gameManager, Object* type_, maths::Vector2 position);
	~Entity();

	void setPosition(maths::Vector2 position);
	maths::Vector2 getPosition() const;

	const sf::Sprite& getSprite() const;
	const Object& getType() const;

	void setType(Object* type);
private:
	void init_sprite();

	sf::Sprite sprite_;

	maths::Vector2 position_;
	Object* type_;
	GameManager* gameManager_;
};