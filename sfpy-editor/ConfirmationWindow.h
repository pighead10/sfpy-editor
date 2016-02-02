#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

class Gui;

class ConfirmationWindow{
public:
	ConfirmationWindow(Gui* parent,std::string title, std::string message, std::string arg,
		std::function<void(std::string)> yesfunc,std::function<void(std::string)> nofunc);
	~ConfirmationWindow();
private:
	void initgui(std::string title,std::string message);

	void yesSelected();
	void noSelected();

	sfg::Window::Ptr window_;

	std::function<void(std::string)> yesfunc_;
	std::function<void(std::string)> nofunc_;
	std::string arg_;

	Gui* parent_;
};