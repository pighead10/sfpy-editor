#include "Gui.h"
#include "Vector2.h"
#include "PropertyWindow.h"
#include "Object.h"
#include "ObjectWindow.h"
#include "MenuItem.h"
#include "ObjectItem.h"
#include "TextureWindow.h"
#include "TextureItem.h"
#include "GameManager.h"

Gui::Gui(GameManager* game_manager):game_manager_(game_manager){
}

Gui::~Gui(){
}

void Gui::update(int elapsed){
	desktop.Update(elapsed);
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

void Gui::objectSelected(std::string name){
	using namespace sfg;
	
	game_manager_->objectSelected(name);
	for (auto& it : menu_list_){
		if (it->getType() == GUI_OBJECT){
			if (it->getName() != name){
				it->setActive(false);
			}
			else{
				it->setActive(true);
			}
		}
	}

	//if object is already open, make it the active window
	for (auto& it : window_list_){
		if (it->getName() == name){
			it->makeActive();
			return;
		}
	}
	//otherwise create the object
	window_list_.push_back(std::unique_ptr<PropertyWindow>(new ObjectWindow(this, game_manager_, name,getMenuItem(name,GUI_OBJECT))));
}

void Gui::textureSelected(std::string name){
	using namespace sfg;

	for (auto& it : menu_list_){
		if (it->getType() == Gui::GUI_TEXTURE){
			if (it->getName() != name){
				it->setActive(false);
			}
			else{
				it->setActive(true);
			}
		}
	}

	for (auto& it : window_list_){
		if (it->getType() == Gui::GUI_TEXTURE && it->getName() == name){
			it->makeActive();
			return;
		}
	}

	window_list_.push_back(std::unique_ptr<PropertyWindow>(new TextureWindow(this, game_manager_, name, getMenuItem(name, GUI_TEXTURE))));
}

void Gui::objectAdded(std::string name){
	ObjectItem* item = new ObjectItem(this, name);
	obj_box_->Pack(item->getButton());
	menu_list_.push_back(std::unique_ptr<MenuItem>(item));
}

void Gui::textureAdded(std::string name){
	TextureItem* item = new TextureItem(this, name);
	tex_box_->Pack(item->getButton());
	menu_list_.push_back(std::unique_ptr<MenuItem>(item));
}

void Gui::run(){
	using namespace sfg;


	/*auto notebook = Notebook::Create();

	auto obox = Box::Create(Box::Orientation::VERTICAL, 5.0f);
	auto o1 = Button::Create("Object1");
	auto o2 = Button::Create("Object2");
	auto o3 = Button::Create("Object3");

	auto tbox = Box::Create(Box::Orientation::VERTICAL, 5.0f);
	auto t1 = Button::Create("Texture1");
	auto t2 = Button::Create("Texture2");
	auto t3 = Button::Create("Texture3");
	auto t4 = Button::Create("Texture4");

	obox->Pack(o1);
	obox->Pack(o2);
	obox->Pack(o3);

	tbox->Pack(t1);
	tbox->Pack(t2);
	tbox->Pack(t3);
	tbox->Pack(t4);

	notebook->AppendPage(obox, Label::Create("Objects"));
	notebook->AppendPage(tbox, Label::Create("Textures"));

	auto window = Window::Create();
	window->SetTitle("Selector");
	window->Add(notebook);
	desktop.Add(window);*/

	auto window = Window::Create();
	window->SetTitle("Object Browser");

	selector_ = Notebook::Create();
	obj_box_ = Box::Create(Box::Orientation::VERTICAL, 5.0f);
	tex_box_ = Box::Create(Box::Orientation::VERTICAL, 5.0f);

	selector_->AppendPage(obj_box_,Label::Create("Objects"));
	selector_->AppendPage(tex_box_,Label::Create("Textures"));

	window->Add(selector_);
	desktop.Add(window);


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