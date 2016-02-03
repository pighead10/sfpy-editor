#include "PropertyWindow.h"
#include "Gui.h"
#include "MenuItem.h"
#include "GameManager.h"

PropertyWindow::PropertyWindow(){
}

PropertyWindow::PropertyWindow(Gui* parent,GameManager* game_manager,std::string name,MenuItem* menu_item){
	construct(parent, game_manager, name,menu_item);
}

PropertyWindow::~PropertyWindow(){
	parent_->getDesktop()->Remove(window_);
}

void PropertyWindow::construct(Gui* parent,GameManager* game_manager,std::string name,MenuItem* menu_item){
	using namespace sfg;
	menu_item_ = menu_item;
	parent_ = parent;
	game_manager_ = game_manager;
	name_ = name;
	window_ = Window::Create(Window::BACKGROUND | Window::CLOSE | Window::TITLEBAR | Window::RESIZE);
	parent_->subscribeWidgetClicked(window_);
	apply_button_ = Button::Create("Apply");
	delete_button_ = Button::Create("Delete");
	createElements();
	parent_->getDesktop()->Add(window_);
	subscribeEvents();
}

Gui::GUI_TYPE PropertyWindow::getType() const{
	return type_;
}

std::string PropertyWindow::getName() const{
	return name_;
}

bool PropertyWindow::isNameValid(std::string name) const{
	bool valid = true;
	if (name == ""){
		valid = false;
	}
	else if (!isalnum(name[0])){
		valid = false;
	}
	else{
		for (auto& it : name){
			if (!isalnum(it) && it != '_' && it != '-'){
				valid = false;
				break;
			}
		}
	}
	return valid;
}

bool PropertyWindow::isFilenameValid(std::string name, std::string extension) const{
	bool valid = true;
	int disp = name.length() - extension.length();
	if (disp <= 0){
		valid = false;
	}
	else{
		std::string noext = name.substr(0, disp);
		valid = isNameValid(noext);
		if (valid){
			if (name.substr(disp, extension.length()) != extension){
				valid = false;
			}
		}
	}
	return valid;
}

void PropertyWindow::setName(std::string name){
	name_ = name;
	menu_item_->setName(name);
}

void PropertyWindow::makeActive(){
	parent_->getDesktop()->BringToFront(window_);
	//window_->SetActiveWidget();
}

void PropertyWindow::onWindowClosed(){
	using namespace sfg;	
	parent_->removeWindow(this);
}

void PropertyWindow::onDeletePressed(){
}

void PropertyWindow::applySettings(){
	//apply settings directly to GameManager
}

void PropertyWindow::subscribeEvents(){
	window_->GetSignal(sfg::Window::OnCloseButton).Connect(std::bind(&PropertyWindow::onWindowClosed, this));
	apply_button_->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PropertyWindow::applySettings, this));
	delete_button_->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PropertyWindow::onDeletePressed, this));

	parent_->subscribeWidgetClicked(apply_button_);
	parent_->subscribeWidgetClicked(delete_button_);;
}

void PropertyWindow::createElements(){
	//Create all elements of window
	//Remember to add ApplyButton
}