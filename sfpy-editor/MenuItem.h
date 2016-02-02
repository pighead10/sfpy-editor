#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include "Gui.h"

class MenuItem{
public:
	virtual ~MenuItem();

	void setActive(bool active);
	virtual void selected();
	sfg::Button::Ptr getButton();

	void setName(std::string name);
	std::string getName() const;
	Gui::GUI_TYPE getType() const;
protected:
	void init(Gui* parent,std::string name,Gui::GUI_TYPE type);
	sfg::Button::Ptr button_;
	std::string name_;
	std::string id_;
	Gui* parent_;
	Gui::GUI_TYPE type_;
};