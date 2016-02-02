#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

class Gui;

class TextDialogBox{
public:
	TextDialogBox(Gui* parent,std::string title,std::string text,std::function<void(std::string)> applyfunc);
	~TextDialogBox();
private:
	void initgui(std::string title, std::string text);
	void applyPressed();

	sfg::Window::Ptr window_;
	sfg::Entry::Ptr entry_;

	Gui* parent_;

	std::function<void(std::string)> applyfunc_;
};