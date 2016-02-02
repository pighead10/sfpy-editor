#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Vector2.h"

class Object;
class Texture;
class Entity;
class Gui;

typedef std::vector<std::unique_ptr<Object>> ObjectList;
typedef std::vector<std::unique_ptr<Texture>> TextureList;
typedef std::vector<std::unique_ptr<Entity>> EntityList;

class GameManager{
public:
	GameManager();
	~GameManager();

	void loadGameFromFile(std::string filename);
	void loadLevelFromFile(std::string filename);

	void saveLevel(std::string filename);
	void saveGame(std::string filename);

	Texture* getTextureByName(std::string name);
	Object* getObjectByName(std::string name);

	void run();
	void loadAll();

	void addEntity(Entity* entity);
	void addObject(Object* object);
	void addTexture(Texture* texture);

	void objectSelected(std::string name);
	void updateAllEntitySprites(Object* object);
private:
	void addObjToGui(Object* object);
	void addTexToGui(Texture* texture);

	void mouseClicked(sf::Mouse::Button button, maths::Vector2 mousePosition);
	void keyPressed(sf::Keyboard::Key key);

	void render(sf::RenderWindow* window);

	enum CFG_TYPE{
		TYPE_NONE,
		TYPE_OBJ,
		TYPE_GAME,
		TYPE_TEX
	};

	enum CFG_PREFIX{
		PREFIX_NONE,
		PREFIX_TYPE,
		PREFIX_PROP,
		PREFIX_NAME,
		PREFIX_NEXT,
		PREFIX_POSX,
		PREFIX_POSY,
	};

	ObjectList objects_; //object types
	TextureList textures_; //loaded textures
	EntityList entities_; //entities placed in world

	std::string game_name_;

	std::unique_ptr<Gui> gui_;

	Object* selected_;
};