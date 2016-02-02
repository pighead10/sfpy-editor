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
	parent_->subscribeWindowClicked(window_);
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
}

void PropertyWindow::createElements(){
	//Create all elements of window
	//Remember to add ApplyButton
}