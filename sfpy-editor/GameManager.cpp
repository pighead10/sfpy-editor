#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "GameManager.h"
#include "Object.h"
#include "Texture.h"
#include "Entity.h"
#include "Gui.h"
#include "Script.h"
#include "Sound.h"


//TODO global scripts!!
//TODO error messages
//TODO backup files

GameManager::GameManager(){
	selected_ = NULL;
}

GameManager::~GameManager(){

}

void GameManager::loadAll(){
	loadGameFromFile("testgame2.game");
	//todo load level
}

Texture* GameManager::getTextureByName(std::string name){
	for (auto& it : textures_){
		if (it->getName() == name){
			return it.get();
		}
	}
	std::cout << "ERROR: No texture found with name: " << name << std::endl;
	return NULL;
}

Object* GameManager::getObjectByName(std::string name){
	for (auto& it : objects_){
		if (it->getName() == name){
			return it.get();
		}
	}
	std::cout << "ERROR: No object found with name: " << name << std::endl;
	return NULL;
}

Sound* GameManager::getSoundByName(std::string name){
	for (auto& it : sounds_){
		if (it->getName() == name){
			return it.get();
		}
	}
	std::cout << "ERROR: No sound found with name: " << name << std::endl;
	return NULL;
}

Script* GameManager::getScriptByName(std::string name){
	for (auto& it : scripts_){
		if (it->getName() == name){
			return it.get();
		}
	}
	std::cout << "ERROR: No script found with name: " << name << std::endl;
	return NULL;
}

void GameManager::sfguiClicked(){
	pass_click_to_sfml = false;
}

void GameManager::run(){
	sf::VideoMode vm(1024, 768);
	sf::RenderWindow window;
	window.create(vm, game_name_);

	window.resetGLStates();

	bool exit_ = false;
	

	gui_ = std::unique_ptr<Gui>(new Gui(this));
	gui_->run();

	loadAll();

	sf::Clock clock;

	while (!exit_){
		sf::Event evt;
		while (window.pollEvent(evt)){
			pass_click_to_sfml = true;
			gui_->handleEvent(evt);
			if (evt.type == sf::Event::Closed){
				exit_ = true;
			}
			else if (pass_click_to_sfml && evt.type == sf::Event::MouseButtonPressed){
				mouseClicked(evt.mouseButton.button, maths::Vector2(evt.mouseButton.x, evt.mouseButton.y));
			}
			else if (evt.type == sf::Event::KeyPressed){
				keyPressed(evt.key.code);
			}
		}
		gui_->update(clock.restart().asSeconds());

		window.clear(sf::Color::White);
		render(&window);
		gui_->display(&window);
		window.display();
	}

	window.close();
}

void GameManager::removeObject(std::string name){
	for (auto& it = entities_.begin(); it != entities_.end();){
		if ((*it)->getType().getName() == name){
			it = entities_.erase(it);
		}
		else{
			it++;
		}
	}
	for (auto& it = objects_.begin(); it != objects_.end();){
		if ((*it)->getName() == name){
			it = objects_.erase(it);
		}
		else{
			it++;
		}
	}
}

void GameManager::removeTexture(std::string name){
	for (auto& it = textures_.begin(); it != textures_.end();){
		if ((*it)->getName() == name){
			textures_.erase(it);
			break;
		}
		else{
			it++;
		}
	}
}

void GameManager::removeScript(std::string name){
	for (auto& it = scripts_.begin(); it != scripts_.end();){
		if ((*it)->getName() == name){
			scripts_.erase(it);
			break;
		}
		else{
			it++;
		}
	}
}

void GameManager::removeSound(std::string name){
	for (auto& it = sounds_.begin(); it != sounds_.end();){
		if ((*it)->getName() == name){
			sounds_.erase(it);
			break;
		}
		else{
			it++;
		}
	}
}

void GameManager::loadGameFromFile(std::string gamefile){
	//Read gamefile to store game properties (objects, sprites, etc)
	using namespace std;

	textures_.clear();
	objects_.clear();
	scripts_.clear();
	sounds_.clear();

	ifstream fin(gamefile);
	string line;
	CFG_TYPE type = TYPE_NONE;
	string prop;
	CFG_PREFIX prefix = PREFIX_NONE;

	Object* current_obj = NULL;
	Texture* current_tex = NULL;
	Script* current_script = NULL;
	Sound* current_sound = NULL;

	while (getline(fin, line)){
		if (line.length() > 0 && line[0] != '#'){ //ignore commented lines
			//Check if prefix signifies that the next line is a saved value
			if (prefix == PREFIX_PROP){
				if (type == TYPE_OBJ){
					std::string p = line;
					if (p[0] == '\''){ //if property starts with ', it is in quotes, so we need to remove quotes
						p = p.substr(1, p.length()-2);
					}
					current_obj->setProperty(prop, p);
				}
				else if (type == TYPE_TEX){
					if (prop == "filename"){
						current_tex->setFilename(line);
					}
					else if (prop == "name"){
						current_tex->setName(line);
					}
				}
				else if (type == TYPE_SCRIPT){
					if (prop == "filename"){
						current_script->setFilename(line);
					}
					else if (prop == "name"){
						current_script->setName(line);
					}
				}
				else if (type == TYPE_SOUND){
					if (prop == "filename"){
						current_sound->setFilename(line);
					}
					else if (prop == "name"){
						current_sound->setName(line);
					}
				}
				prefix = PREFIX_NONE;
			}
			else if (prefix == PREFIX_NAME){
				if (type == TYPE_OBJ){
					current_obj->setName(line);
				}
				else if (type == TYPE_GAME){
					game_name_ = line;
				}
				prefix = PREFIX_NONE;
			}
			else{
				istringstream s(line);
				string word;
				for (int i = 0; s >> word; i++){
					//check if word is a prefix
					if (word == "$type"){
						prefix = PREFIX_TYPE;
					}
					else if (word == "$prop"){
						prefix = PREFIX_PROP;
					}
					else if (word == "$name"){
						prefix = PREFIX_NAME;
					}
					else{
						if (prefix == PREFIX_TYPE){
							if (word == "obj"){
								type = TYPE_OBJ;
								current_obj = new Object();
								addObject(current_obj);
							}
							else if (word == "game"){
								type = TYPE_GAME;
							}
							else if (word == "tex"){
								type = TYPE_TEX;
								current_tex = new Texture();
								addTexture(current_tex);
							}
							else if (word == "sound"){
								type = TYPE_SOUND;
								current_sound = new Sound();
								addSound(current_sound);
							}
							else if (word == "script"){
								type = TYPE_SCRIPT;
								current_script = new Script();
								addScript(current_script);
							}
						}
						else if (prefix == PREFIX_PROP){
							prop = word;
						}
					}
				}
			}
		}
	}
	fin.close();

	//now add all objects to gui (after all properties are set)
	for (auto& it : objects_){
		addObjToGui(it.get());
	}
	for (auto& it : textures_){
		addTexToGui(it.get());
	}
	for (auto& it : scripts_){
		addScriptToGui(it.get());
	}
	for (auto& it : sounds_){
		addSoundToGui(it.get());
	}
}

void GameManager::updateAllEntitySprites(Object* object){
	for (auto& it : entities_){
		if (it->getType().getName() == object->getName()){
			it->updateSprite();
		}
	}
}

void GameManager::objectSelected(std::string name){
	selected_ = getObjectByName(name);
}

void GameManager::addObjToGui(Object* object){
	gui_->objectAdded(object->getName());
}

void GameManager::addTexToGui(Texture* texture){
	gui_->textureAdded(texture->getName());
}

void GameManager::addSoundToGui(Sound* sound){
	gui_->soundAdded(sound->getName());
}

void GameManager::addScriptToGui(Script* script){
	gui_->scriptAdded(script->getName());
}

void GameManager::addEntity(Entity* entity){
	entities_.push_back(std::unique_ptr<Entity>(entity));
}

void GameManager::addObject(Object* object){
	objects_.push_back(std::unique_ptr<Object>(object));
}

void GameManager::addTexture(Texture* texture){
	textures_.push_back(std::unique_ptr<Texture>(texture));
}

void GameManager::addSound(Sound* sound){
	sounds_.push_back(std::unique_ptr<Sound>(sound));
}

void GameManager::addScript(Script* script){
	scripts_.push_back(std::unique_ptr<Script>(script));
}

void GameManager::keyPressed(sf::Keyboard::Key key){
	using namespace sf;
	if (key == Keyboard::Q){
		//gui_->objectSelected(objects_[selected_]->);
	}
	else if (key == Keyboard::S){
		//saveLevel("testgame.level");
	}
	else if (key == Keyboard::P){
		//saveGame("testgame2.game");
	}
	else if (key == Keyboard::L){
		//loadLevelFromFile("testgame.level");
	}
	else if (key == Keyboard::O){
		//loadGameFromFile("testgame2.game");
	}
}

void GameManager::removeEntity(maths::Vector2 position){
	for (auto& it = entities_.begin(); it != entities_.end();){
		if ((*it)->getSprite().getGlobalBounds().contains(position)){
			it = entities_.erase(it);
		}
		else{
			it++;
		}
	}
}

void GameManager::mouseClicked(sf::Mouse::Button button, maths::Vector2 mousePosition){
	using namespace sf;
	if (button == Mouse::Left && selected_ != NULL){
		addEntity(new Entity(this, selected_, mousePosition));
	}
	else if (button == Mouse::Right){
		removeEntity(mousePosition);
	}
}

void GameManager::render(sf::RenderWindow* window){
	for (auto& it : entities_){
		window->draw(it->getSprite());
	}
}

void GameManager::loadLevelFromFile(std::string filename){
	using namespace std;
	ifstream fin(filename);
	string line;
	CFG_TYPE type = TYPE_NONE;
	CFG_PREFIX prefix = PREFIX_NONE;

	entities_.clear();

	while (getline(fin,line)){
		type = TYPE_NONE;
		prefix = PREFIX_NONE;
		istringstream s(line);
		string word;
		Entity* current_entity = NULL;
		for (int i = 0; s >> word; i++){
			if (type == TYPE_NONE){
				if (word == "obj"){
					type = TYPE_OBJ;
					current_entity = new Entity(this);
					addEntity(current_entity);
					prefix = PREFIX_NEXT;
				}
			}
			else if (type == TYPE_OBJ){
				if (prefix == PREFIX_NONE){
					prefix = PREFIX_NEXT;
				}
				else if (prefix == PREFIX_NEXT){
					if (word == "name"){
						prefix = PREFIX_NAME;
					}
					else if (word == "pos"){
						prefix = PREFIX_POSX;
					}
				}
				else if (prefix == PREFIX_NAME){
					current_entity->setType(getObjectByName(word));
					prefix = PREFIX_NEXT;
				}
				else if (prefix == PREFIX_POSX){
					current_entity->setPosition(maths::Vector2(stod(word), current_entity->getPosition().y));
					prefix = PREFIX_POSY;
				}
				else if (prefix == PREFIX_POSY){
					current_entity->setPosition(maths::Vector2(current_entity->getPosition().x, stod(word)));
					prefix = PREFIX_NEXT;
				}
			}
		}
	}
}

void GameManager::saveLevel(std::string filename){
	using namespace std;
	ofstream fout(filename);
	//TODO error message
	for (auto& it : entities_){
		string name = it->getType().getName();
		maths::Vector2 pos = it->getPosition();
		string pos_str = to_string(pos.x) + " " + to_string(pos.y);
		string str = "obj name " + name + " pos " + pos_str + "\n";
		fout << str;
	}
	fout.close();
}

void GameManager::saveGame(std::string filename){
	using namespace std;
	ofstream fout(filename);

	string game_str = "$type game\n$name\n" + game_name_ + "\n\n";

	fout << game_str;

	for (auto& it : objects_){
		string s = "$type obj\n";
		s += "$name\n";
		s += it->getName() + "\n";
		for (auto& prop : it->getProperties()){
			s += "$prop " + prop.first + "\n";
			s += prop.second + "\n";
		}
		s += "\n";
		fout << s;
	}
	
	for (auto& it : textures_){
		string s = "$type tex\n";
		s += "$prop name\n";
		s += it->getName() + "\n";
		s += "$prop filename\n";
		s += it->getFilename() + "\n";
		s += "\n";
		fout << s;
	}

	for (auto& it : scripts_){
		string s = "$type script\n";
		s += "$prop name\n";
		s += it->getName() + "\n";
		s += "$prop filename\n";
		s += it->getFilename() + "\n";
		s += "\n";
		fout << s;
	}

	for (auto& it : sounds_){
		string s = "$type sound\n";
		s += "$prop name\n";
		s += it->getName() + "\n";
		s += "$prop filename\n";
		s += it->getFilename() + "\n";
		s += "\n";
		fout << s;
	}
	fout.close();
}