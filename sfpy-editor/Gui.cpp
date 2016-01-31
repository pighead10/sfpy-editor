#include "Gui.h"
#include "Vector2.h"
#include "PropertyWindow.h"
#include "Object.h"
#include "ObjectWindow.h"

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

void Gui::onButtonClick(){
	label_->SetText("Hello world from Gui.cpp!");
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

void Gui::objectSelected(Object* object){
	using namespace sfg;
	//if object is already open, make it the active window
	for (auto& it : window_list_){
		if (it->getName() == object->getName()){
			it->makeActive();
			return;
		}
	}
	//otherwise create the object
	window_list_.push_back(std::unique_ptr<PropertyWindow>(new ObjectWindow(this, game_manager_, object->getName())));
}

void Gui::run(){
	using namespace sfg;


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