#include "Gui.h"
#include "Vector2.h"
#include "PropertyWindow.h"
#include "Object.h"
#include "ObjectWindow.h"
#include "MenuItem.h"
#include "TextureWindow.h"
#include "GameManager.h"
#include "Texture.h"
#include "ConfirmationWindow.h"
#include "Sound.h"
#include "SoundWindow.h"
#include "Script.h"
#include "ScriptWindow.h"
#include "TextDialogBox.h"

Gui::Gui(GameManager* game_manager):game_manager_(game_manager),
objcount_(0),texcount_(0),scriptcount_(0),soundcount_(0),save_name_(""){
}

Gui::~Gui(){
}

void Gui::update(int elapsed){
	desktop.Update(elapsed);
}

void Gui::subscribeWindowClicked(sfg::Window::Ptr window){
	window->GetSignal(sfg::Widget::OnMouseLeftPress).Connect(std::bind(&GameManager::sfguiClicked, game_manager_));
}

void Gui::handleEvent(sf::Event evt){
	desktop.HandleEvent(evt);
}

void Gui::display(sf::RenderWindow* window){
	sfgui_.Display(*window);
}

sfg::Desktop* Gui::getDesktop(){
	return &desktop;
}

void Gui::removeWindow(PropertyWindow* window){
	for (auto& it = window_list_.begin(); it != window_list_.end();){
		if (it->get() == window){
			window_list_.erase(it);
			break;
		}
		else{
			it++;
		}
	}
}

MenuItem* Gui::getMenuItem(std::string name,GUI_TYPE type){
	for (auto& it : menu_list_){
		if (it->getName() == name && it->getType() == type){
			return it.get();
		}
	}
	std::cout << "ERROR: No menu item exists with correct type and name: " + name << std::endl;
	return NULL;
}

void Gui::itemSelected(std::string name, GUI_TYPE type){
	using namespace sfg;

	for (auto& it : menu_list_){
		if (it->getType() == type){
			if (it->getName() != name){
				it->setActive(false);
			}
			else{
				it->setActive(true);
			}
		}
	}

	for (auto& it : window_list_){
		if (it->getType() == type && it->getName() == name){
			it->makeActive();
			return;
		}
	}

	PropertyWindow* window = NULL;
	if (type == GUI_OBJECT){
		window = new ObjectWindow(this, game_manager_, name, getMenuItem(name, type));
		game_manager_->objectSelected(name);
	}
	else if (type == GUI_TEXTURE){
		window = new TextureWindow(this, game_manager_, name, getMenuItem(name, type));
	}
	else if (type == GUI_SOUND){
		window = new SoundWindow(this, game_manager_, name, getMenuItem(name, type));
	}
	else if (type == GUI_SCRIPT){
		window = new ScriptWindow(this, game_manager_, name, getMenuItem(name, type));
	}

	window_list_.push_back(std::unique_ptr<PropertyWindow>(window));
}

void Gui::objectAdded(std::string name){
	MenuItem* item = new MenuItem(this, name,GUI_OBJECT);
	obj_box_->Pack(item->getButton());
	menu_list_.push_back(std::unique_ptr<MenuItem>(item));
	objcount_++;
}

void Gui::textureAdded(std::string name){
	MenuItem* item = new MenuItem(this, name, GUI_TEXTURE);
	tex_box_->Pack(item->getButton());
	menu_list_.push_back(std::unique_ptr<MenuItem>(item));
	texcount_++;
}

void Gui::scriptAdded(std::string name){
	MenuItem* item = new MenuItem(this, name, GUI_SCRIPT);
	script_box_->Pack(item->getButton());
	menu_list_.push_back(std::unique_ptr<MenuItem>(item));
	scriptcount_++;
}

void Gui::soundAdded(std::string name){
	MenuItem* item = new MenuItem(this, name, GUI_SOUND);
	sound_box_->Pack(item->getButton());
	menu_list_.push_back(std::unique_ptr<MenuItem>(item));
	soundcount_++;
}

std::string Gui::getNextItemName(int count,std::string name,GUI_TYPE type){
	for (int n = count;;n++){
		std::string s = name + std::to_string(n);
		if (getMenuItem(s, type) == NULL){
			return s;
		}
	}
	return "";
}

void Gui::removeMenuItem(std::string name, GUI_TYPE type){
	for (auto& it = menu_list_.begin(); it != menu_list_.end();it++){
		if (type == (*it)->getType() && name == (*it)->getName()){
			menu_list_.erase(it);
			return;
		}
	}
	std::cout << "ERROR: Attempting to remove menu item " << name << " that doesn't exist." << std::endl;
}

void Gui::removeWindow(std::string name, GUI_TYPE type){
	for (auto& it = window_list_.begin(); it != window_list_.end();it++){
		if (type == (*it)->getType() && name == (*it)->getName()){
			window_list_.erase(it);
			return;
		}
	}
	std::cout << "ERROR: Attempting to remove window item " << name << " that doesn't exist." << std::endl;
}

//these are separate functions are different objects may need different behaviour in future
void Gui::removeObject(std::string name){
	removeMenuItem(name, GUI_OBJECT);
	removeWindow(name, GUI_OBJECT);
}

void Gui::removeTexture(std::string name){
	removeMenuItem(name, GUI_TEXTURE);
	removeWindow(name, GUI_TEXTURE);
}

void Gui::removeSound(std::string name){
	removeMenuItem(name, GUI_SOUND);
	removeWindow(name, GUI_SOUND);
}

void Gui::removeScript(std::string name){
	removeMenuItem(name, GUI_SCRIPT);
	removeWindow(name, GUI_SCRIPT);
}

void Gui::fileMenuSelect(){
	int selected = file_->GetSelectedItem();
	if (selected == 1){ //add object
		Object* obj = new Object();
		std::string n = getNextItemName(objcount_, "Obj", GUI_OBJECT);
		obj->setName(n);
		obj->setProperty("visible", "True");
		obj->setProperty("collidable", "True");
		obj->setProperty("position", "Vector2(0,0)");
		obj->setProperty("velocity", "Vector2(0,0)");

		obj->setProperty("texture", "");
		obj->setProperty("name", n);
		game_manager_->addObject(obj);
		objectAdded(n);
	}
	else if (selected == 2){ //add texture
		Texture* tex = new Texture();
		std::string n = getNextItemName(texcount_, "Tex", GUI_TEXTURE);
		tex->setName(n);
		tex->setFilename("");
		game_manager_->addTexture(tex);
		textureAdded(n);
	}
	else if (selected == 3){ //add sounds
		Sound* sound = new Sound();
		std::string n = getNextItemName(soundcount_, "Sound", GUI_SOUND);
		sound->setName(n);
		sound->setFilename("");
		game_manager_->addSound(sound);
		soundAdded(n);
	}
	else if (selected == 4){ //add scripts
		Script* script = new Script();
		std::string n = getNextItemName(scriptcount_, "Script", GUI_SCRIPT);
		script->setName(n);
		script->setFilename("");
		game_manager_->addScript(script);
		scriptAdded(n);
	}
	else if (selected == 5){ //save
		save();
	}
	else if (selected == 6){ //save as
		saveAs();
	}
	else if (selected == 7){ //load
		load();
	}
	file_->SelectItem(0);
}

void Gui::requestDeleteObject(std::string name){
	using namespace sfg;
	ConfirmationWindow* window = new ConfirmationWindow(
		this,
		"Warning: Deleting object",
		"You are about to delete object " + name + ". This will remove all placed entities of this object. Do you want to continue?",
		name,
		std::bind(&Gui::deleteObject_yes,this,std::placeholders::_1),
		std::bind(&Gui::deleteObject_no,this,std::placeholders::_1));
	game_manager_->objectSelected("");
}

void Gui::deleteObject_yes(std::string name){
	game_manager_->removeObject(name);
	removeObject(name);
}

void Gui::deleteObject_no(std::string name){
	//don't delete object...
}

void Gui::requestDeleteTexture(std::string name){
	using namespace sfg;
	ConfirmationWindow* window = new ConfirmationWindow(
		this,
		"Warning: Deleting texture",
		"You are about to delete texture " + name + ". Objects using this texture will appear invisible. Do you want to continue?",
		name,
		std::bind(&Gui::deleteTexture_yes, this, std::placeholders::_1),
		std::bind(&Gui::deleteTexture_no, this, std::placeholders::_1));
}

void Gui::requestDeleteScript(std::string name){
	using namespace sfg;
	ConfirmationWindow* window = new ConfirmationWindow(
		this,
		"Warning: Deleting script",
		"You are about to delete script " + name + ". Do you want to continue?",
		name,
		std::bind(&Gui::deleteScript_yes, this, std::placeholders::_1),
		std::bind(&Gui::deleteScript_no, this, std::placeholders::_1));
}

void Gui::requestDeleteSound(std::string name){
	using namespace sfg;
	ConfirmationWindow* window = new ConfirmationWindow(
		this,
		"Warning: Deleting sound",
		"You are about to delete texture " + name + ". Objects will no longer be able to play this sound. Do you want to continue?",
		name,
		std::bind(&Gui::deleteSound_yes, this, std::placeholders::_1),
		std::bind(&Gui::deleteSound_no, this, std::placeholders::_1));
}

void Gui::deleteTexture_yes(std::string name){
	game_manager_->removeTexture(name);
	removeTexture(name);
}

void Gui::deleteTexture_no(std::string name){
	//don't delete object...
}

void Gui::deleteSound_yes(std::string name){
	game_manager_->removeSound(name);
	removeSound(name);
}

void Gui::deleteSound_no(std::string name){
	//don't delete object...
}

void Gui::deleteScript_yes(std::string name){
	game_manager_->removeScript(name);
	removeScript(name);
}

void Gui::deleteScript_no(std::string name){
	//don't delete object...
}

void Gui::clearAll(){
	window_list_.clear();
	menu_list_.clear();
	objcount_ = 0;
	texcount_ = 0;
	soundcount_ = 0;
	scriptcount_ = 0;
	save_name_ = "";
}

void Gui::save(){
	if (save_name_ == ""){
		saveAs();
	}
	else{
		game_manager_->saveLevel(save_name_ + ".level");
		game_manager_->saveGame(save_name_ + ".game");
	}
}

void Gui::saveAs(){
	TextDialogBox* box = new TextDialogBox(this, "Save file as", "Enter file path and name for your game to be saved as. No file extension is necessary (e.g: 'examples/mygame'). Leave blank to cancel.",
		std::bind(&Gui::saveFileSelected, this, std::placeholders::_1));
}

void Gui::saveFileSelected(std::string filename){
	if (filename != ""){
		save_name_ = filename;
		save();
	}
}

void Gui::load(){
	TextDialogBox* box = new TextDialogBox(this, "Load game", "Enter file path and name for the game you want to load. No file extension is necessary (e.g: 'examples/mygame'). Leave blank to cancel.",
		std::bind(&Gui::loadFileSelected, this, std::placeholders::_1));
}

void Gui::loadFileSelected(std::string filename){
	if (filename != ""){
		clearAll();
		game_manager_->loadGameFromFile(filename + ".game");
		game_manager_->loadLevelFromFile(filename + ".level");
		save_name_ = filename;
	}
}

void Gui::run(){
	using namespace sfg;

	auto window = Window::Create();
	window->SetTitle("Object Browser");

	subscribeWindowClicked(window);

	selector_ = Notebook::Create();
	obj_box_ = Box::Create(Box::Orientation::VERTICAL, 5.0f);
	tex_box_ = Box::Create(Box::Orientation::VERTICAL, 5.0f);
	sound_box_ = Box::Create(Box::Orientation::VERTICAL, 5.0f);
	script_box_ = Box::Create(Box::Orientation::VERTICAL, 5.0f);

	selector_->AppendPage(obj_box_,Label::Create("Objects"));
	selector_->AppendPage(tex_box_,Label::Create("Textures"));
	selector_->AppendPage(sound_box_, Label::Create("Sounds"));
	selector_->AppendPage(script_box_, Label::Create("Scripts"));

	window->Add(selector_);
	desktop.Add(window);

	auto menubox = Box::Create(Box::Orientation::HORIZONTAL, 5.0f);

	file_ = ComboBox::Create();
	file_->AppendItem("File");
	file_->AppendItem("Add object");
	file_->AppendItem("Add texture");
	file_->AppendItem("Add sound");
	file_->AppendItem("Add script");
	file_->AppendItem("Save");
	file_->AppendItem("Save as");
	file_->AppendItem("Load");

	file_->SelectItem(0);

	file_->GetSignal(ComboBox::OnSelect).Connect(std::bind(&Gui::fileMenuSelect, this));

	menubox->Pack(file_);
	desktop.Add(menubox);


	/*label_ = Label::Create("Hello world!");

	auto button = Button::Create("Greet sfgui!");
	button->GetSignal(Widget::OnLeftClick).Connect(std::bind(&Gui::onButtonClick, this));

	auto box = Box::Create(Box::Orientation::VERTICAL, 5.0f);
	box->Pack(label_);
	box->Pack(button, false);

	auto window = Window::Create();
	window->SetTitle("Hello world!");
	window->Add(box);

	desktop.Add(window);*/
}