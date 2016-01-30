#include "Entity.h"
#include "Object.h"
#include "Texture.h"
#include "GameManager.h"

Entity::Entity(GameManager* gameManager): gameManager_(gameManager){
}

Entity::Entity(GameManager* gameManager, Object* type, maths::Vector2 position)
:gameManager_(gameManager),type_(type),position_(position){
	init_sprite();
}

Entity::~Entity(){
}

void Entity::setType(Object* type){
	type_ = type;
	init_sprite();
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

