#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Vector2.h"

class Object;
class Texture;
class Entity;
class Gui;
class Sound;
class Script;

typedef std::vector<std::unique_ptr<Object>> ObjectList;
typedef std::vector<std::unique_ptr<Texture>> TextureList;
typedef std::vector<std::unique_ptr<Entity>> EntityList;
typedef std::vector<std::unique_ptr<Sound>> SoundList;
typedef std::vector<std::unique_ptr<Script>> ScriptList;

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
	Sound* getSoundByName(std::string name);
	Script* getScriptByName(std::string name);

	void run();
	void loadAll();

	void addEntity(Entity* entity);
	void addObject(Object* object);
	void addTexture(Texture* texture);
	void addSound(Sound* sound);
	void addScript(Script* script);

	void removeObject(std::string name);
	void removeTexture(std::string name);
	void removeSound(std::string name);
	void removeScript(std::string name);

	void objectSelected(std::string name);
	void updateAllEntitySprites(Object* object);

	void setGameName(std::string name);

	void sfguiClicked();

	sf::RenderWindow* getWindow();
private:
	void removeEntity(maths::Vector2 position);

	bool pass_click_to_sfml;

	void addObjToGui(Object* object);
	void addTexToGui(Texture* texture);
	void addSoundToGui(Sound* sound);
	void addScriptToGui(Script* script);

	void mouseClicked(sf::Mouse::Button button, maths::Vector2 mousePosition);
	void keyPressed(sf::Keyboard::Key key);

	void render(sf::RenderWindow* window);

	enum CFG_TYPE{
		TYPE_NONE,
		TYPE_OBJ,
		TYPE_GAME,
		TYPE_TEX,
		TYPE_SOUND,
		TYPE_SCRIPT
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
	SoundList sounds_;
	ScriptList scripts_;

	std::string game_name_;

	std::unique_ptr<Gui> gui_;

	Object* selected_;
	sf::RenderWindow window_;
};