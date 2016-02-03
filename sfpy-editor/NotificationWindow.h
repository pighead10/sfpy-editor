#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

class Gui;

class NotificationWindow{
public:
	NotificationWindow(Gui* parent, std::string title, std::string message);
	~NotificationWindow();
private:
	void buttonPressed();
	void initgui(std::string title, std::string message);

	Gui* parent_;
};