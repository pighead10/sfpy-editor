#pragma once

#include "PropertyWindow.h"

class Sound;

class SoundWindow : public PropertyWindow{
public:
	SoundWindow(Gui* parent, GameManager* game_manager, std::string name, MenuItem* menu_item);
	~SoundWindow();
protected:
	void applySettings();
	void createElements();
	void onDeletePressed();
private:
	sfg::Entry::Ptr nameentry_;
	sfg::Entry::Ptr fileentry_;

	Sound* sound_;
};