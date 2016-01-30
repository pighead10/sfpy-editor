#include <fstream>
#include <string>
#include <sstream>
#include "GameManager.h"
#include "Object.h"
#include "Texture.h"
#include "Entity.h"


//TODO global scripts!!
//TODO error messages
//TODO backup files

GameManager::GameManager(){
}

GameManager::~GameManager(){

}

void GameManager::run(){
	sf::VideoMode vm(1024, 768);
	sf::RenderWindow window;
	window.create(vm, game_name_);

	bool exit_ = false;

	while (!exit_){
		sf::Event evt;
		while (window.pollEvent(evt)){
			if (evt.type == sf::Event::Closed){
				exit_ = true;
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

	ifstream fin(gamefile);
	string line;
	CFG_TYPE type = TYPE_NONE;
	string prop;
	CFG_PREFIX prefix = PREFIX_NONE;

	Object* current_obj;
	Texture* current_tex;

	while (getline(fin, line)){
		if (line.length() > 0 && line[0] != '#'){ //ignore commented lines
			//Check if prefix signifies that the next line is a saved value
			if (prefix == PREFIX_PROP){
				if (type == TYPE_OBJ){
					current_obj->addProperty(prop, line);
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
								objects_.push_back(unique_ptr<Object>(current_obj));
							}
							else if (word == "game"){
								type = TYPE_GAME;
							}
							else if (word == "tex"){
								type = TYPE_TEX;
								current_tex = new Texture();
								textures_.push_back(unique_ptr<Texture>(current_tex));
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

void GameManager::saveLevel(std::string filename){
	using namespace std;
	ofstream fout(filename);
	//TODO error message
	for (auto& it : entities_){
		string name = it->getType().getName();
		maths::Vector2 pos = it->getPosition();
		string pos_str = "(" + to_string(pos.x) + ", " + to_string(pos.y) + ")";
		string str = name + pos_str + "\n";
		fout << str;
	}
	fout.close();
}

void GameManager::saveGame(std::string filename){
	using namespace std;
	ifstream fout(filename);

}