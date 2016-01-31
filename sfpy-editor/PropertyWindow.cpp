#include "PropertyWindow.h"
#include "Gui.h"

PropertyWindow::PropertyWindow(){
}

PropertyWindow::PropertyWindow(Gui* parent,GameManager* game_manager,std::string name){
	construct(parent, game_manager, name);
}

PropertyWindow::~PropertyWindow(){
}

void PropertyWindow::construct(Gui* parent,GameManager* game_manager,std::string name){
	using namespace sfg;
	parent_ = parent;
	game_manager_ = game_manager;
	name_ = name;
	window_ = Window::Create(Window::BACKGROUND | Window::CLOSE | Window::TITLEBAR | Window::RESIZE);
	apply_button_ = Button::Create("Apply");
	createElements();
	parent_->getDesktop()->Add(window_);
	subscribeEvents();
}

std::string PropertyWindow::getName() const{
	return name_;
}

void PropertyWindow::makeActive(){
	//window_->SetActiveWidget();
}

void PropertyWindow::onWindowClosed(){
	using namespace sfg;
	auto widget = Context::Get().GetActiveWidget();
	parent_->getDesktop()->Remove(widget);
	parent_->removeWindow(this);
}

void PropertyWindow::applySettings(){
	//apply settings directly to GameManager
}

void PropertyWindow::subscribeEvents(){
	window_->GetSignal(sfg::Window::OnCloseButton).Connect(std::bind(&PropertyWindow::onWindowClosed, this));
	apply_button_->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PropertyWindow::applySettings, this));
}

void PropertyWindow::createElements(){
	//Create all elements of window
	//Remember to add ApplyButton
}