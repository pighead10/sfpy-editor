#include "PropertyWindow.h"

class Texture;

class TextureWindow : public PropertyWindow{
public:
	TextureWindow(Gui* parent, GameManager* game_manager, std::string name, MenuItem* menu_item);
	~TextureWindow();
protected:
	void applySettings();
	void createElements();
private:
	sfg::Entry::Ptr nameentry_;
	sfg::Entry::Ptr fileentry_;

	Texture* texture_;
};