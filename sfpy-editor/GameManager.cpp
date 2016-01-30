#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "GameManager.h"
#include "Object.h"
#include "Texture.h"
#include "Entity.h"



//TODO global scripts!!
//TODO error messages
//TODO backup files

GameManager::GameManager(){
	selected_ = 0;
}

GameManager::~GameManager(){

}

void GameManager::loadAll(){
	loadGameFromFile("testgame.game");
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
	std::cout << "ERROR: No object count with name: " << name << std::endl;
	return NULL;
}

void GameManager::run(){
	sf::VideoMode vm(1024, 768);
	sf::RenderWindow window;
	window.create(vm, game_name_);

	bool exit_ = false;

	loadAll();

	while (!exit_){
		sf::Event evt;
		while (window.pollEvent(evt)){
			if (evt.type == sf::Event::Closed){
				exit_ = true;
			}
			else if (evt.type == sf::Event::MouseButtonPressed){
				mouseClicked(evt.mouseButton.button, maths::Vector2(evt.mouseButton.x, evt.mouseButton.y));
			}
			else if (evt.type == sf::Event::KeyPressed){
				keyPressed(evt.key.code);
			}
		}

		window.clear(sf::Color::White);
		render(&window);
		window.display();
	}

	window.close();
}

void GameManager::loadGameFromFile(std::string gamefile){
	//Read gamefile to store game properties (objects, sprites, etc)
	using namespace std;

	textures_.clear();
	objects_.clear();

	ifstream fin(gamefile);
	string line;
	CFG_TYPE type = TYPE_NONE;
	string prop;
	CFG_PREFIX prefix = PREFIX_NONE;

	Object* current_obj = NULL;
	Texture* current_tex = NULL;

	while (getline(fin, line)){
		if (line.length() > 0 && line[0] != '#'){ //ignore commented lines
			//Check if prefix signifies that the next line is a saved value
			if (prefix == PREFIX_PROP){
				if (type == TYPE_OBJ){
					std::string p = line;
					if (p[0] == '\''){ //if property starts with ', it is in quotes, so we need to remove quotes
						p = p.substr(1, p.length()-2);
					}
					current_obj->addProperty(prop, p);
				}
				else if (type == TYPE_TEX){
					if (prop == "filename"){
						current_tex->setFilename(line);
					}
					else if (prop == "name"){
						current_tex->setName(line);
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

void GameManager::keyPressed(sf::Keyboard::Key key){
	using namespace sf;
	if (key == Keyboard::Q){
		selected_++;
		if (selected_ >= objects_.size()){
			selected_ = 0;
		}
	}
	else if (key == Keyboard::S){
		saveLevel("testgame.level");
	}
	else if (key == Keyboard::L){
		loadLevelFromFile("testgame.level");
	}
}

void GameManager::mouseClicked(sf::Mouse::Button button, maths::Vector2 mousePosition){
	using namespace sf;
	if (button == Mouse::Left){
		addEntity(new Entity(this, objects_[selected_].get(), mousePosition));
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
	ifstream fout(filename);

	string game_str = "$type game\n$name\n" + game_name_ + "\n\n";

	fout >> game_str;

	for (auto& it : objects_){
		string s = "$type obj\n";
		s += "$name\n";
		s += it->getName() + "\n";
		for (auto& prop : it->getProperties()){
			s += "$prop " + prop.first + "\n";
			s += prop.second + "\n";
		}
		s += "\n";
		fout >> s;
	}
	
	for (auto& it : textures_){
		string s = "$type tex\n";
		s += "$prop name\n";
		s += it->getName() + "\n";
		s += "$prop filename\n";
		s += it->getFilename() + "\n";
		s += "\n";
		fout >> s;
	}
	fout.close();
}