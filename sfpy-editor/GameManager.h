#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Object;
class Texture;
class Entity;

typedef std::vector<std::unique_ptr<Object>> ObjectList;
typedef std::vector<std::unique_ptr<Texture>> TextureList;
typedef std::vector<std::unique_ptr<Entity>> EntityList;

class GameManager{
public:
	GameManager();
	~GameManager();

	void loadGameFromFile(std::string filename);

	void saveLevel(std::string filename);
	void saveGame(std::string filename);

	Texture* getTextureByName(std::string name);
	Object* getObjectByName(std::string name);

	void run();
private:
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
		PREFIX_NAME
	};

	ObjectList objects_; //object types
	TextureList textures_; //loaded textures
	EntityList entities_; //entities placed in world

	std::string game_name_;
};