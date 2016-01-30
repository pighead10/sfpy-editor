#include "Entity.h"
#include "Object.h"
#include "Texture.h"
#include "GameManager.h"

Entity::Entity(maths::Vector2 position, Object* type, GameManager* gameManager) :type_(type),gameManager_(gameManager){
	init_sprite();
}

Entity::~Entity(){
}

void Entity::init_sprite(){
	std::string texname = type_->getProperty("texture");
	Texture* tex = gameManager_->getTextureByName(texname);
	sprite_ = sf::Sprite(tex->getTexture());
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

