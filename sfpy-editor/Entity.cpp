#include "Entity.h"
#include "Object.h"
#include "Texture.h"
#include "GameManager.h"
#include <iostream>

Entity::Entity(GameManager* gameManager): gameManager_(gameManager){
}

Entity::Entity(GameManager* gameManager, Object* type, maths::Vector2 position)
:gameManager_(gameManager),type_(type){
	updateSprite();
	setPosition(position);
}

Entity::~Entity(){
}

void Entity::setType(Object* type){
	//Change the Object type of the entity.
	//Update the sprite in case the new type has a different texture, so the sprite would need to be reloaded.
	type_ = type;
	updateSprite();
}

void Entity::updateSprite(){
	//Set the sprite to have the texture described by the type of the entity if it exists.
	std::string texname = type_->getProperty("texture");
	Texture* tex = gameManager_->getTextureByName(texname);
	if (tex != NULL){
		sprite_ = sf::Sprite(tex->getTexture());
		sprite_.setPosition(position_);
	}
	else{
		std::cout << "ERROR: Attempt to set sprite to nonexistent texture: " << texname << std::endl;
	}
}

const sf::Sprite& Entity::getSprite() const{
	return sprite_;
}

void Entity::setPosition(maths::Vector2 position){
	position_ = position;
	sprite_.setPosition(position);
}

maths::Vector2 Entity::getPosition() const{
	return position_;
}

const Object& Entity::getType() const{
	return *type_;
}

