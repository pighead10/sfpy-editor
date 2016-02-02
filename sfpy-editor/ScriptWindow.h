#pragma once

#include "PropertyWindow.h"

class Script;

class ScriptWindow : public PropertyWindow{
public:
	ScriptWindow(Gui* parent, GameManager* game_manager, std::string name, MenuItem* menu_item);
	~ScriptWindow();
protected:
	void applySettings();
	void createElements();
	void onDeletePressed();
private:
	sfg::Entry::Ptr nameentry_;
	sfg::Entry::Ptr fileentry_;

	Script* script_;
};