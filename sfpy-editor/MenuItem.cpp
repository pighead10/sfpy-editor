#include "MenuItem.h"
#include "Gui.h"

MenuItem::MenuItem(Gui* parent,std::string name,Gui::GUI_TYPE type){
	init(parent, name,type);
}

MenuItem::~MenuItem(){
	button_->GetParent()->Remove(button_);
}

void MenuItem::setActive(bool active){
	if (active){
		//sfg::Context::Get().GetEngine().SetProperty(id_, "Color", sf::Color(1, 1, 1));
	}
	else{
		//sfg::Context::Get().GetEngine().SetProperty(id_, "Color", sf::Color(198, 203, 196)); //default
	}
}

void MenuItem::selected(){
	parent_->itemSelected(getName(), getType());
}

void MenuItem::setName(std::string name){
	name_ = name;
	button_->SetLabel(name);
}

std::string MenuItem::getName() const{
	return name_;
}

sfg::Button::Ptr MenuItem::getButton(){
	return button_;
}

Gui::GUI_TYPE MenuItem::getType() const{
	return type_;
}

void MenuItem::init(Gui* parent, std::string name,Gui::GUI_TYPE type){
	type_ = type;
	parent_ = parent;
	name_ = name;
	button_ = sfg::Button::Create(name);
	button_->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MenuItem::selected, this));
}