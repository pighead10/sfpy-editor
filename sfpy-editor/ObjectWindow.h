#include "PropertyWindow.h"

class Object;

class ObjectWindow : public PropertyWindow{
public:
	ObjectWindow(Gui* parent, GameManager* game_manager, std::string name,MenuItem* menu_item); //no constructor inheritance in VS2013 :(
	~ObjectWindow();
protected:
	void applySettings();
	void createElements();
	void onDeletePressed();
private:
	sfg::Entry::Ptr nameentry_;
	sfg::Entry::Ptr spriteentry_;
	sfg::CheckButton::Ptr visbutton_;
	sfg::CheckButton::Ptr colbutton_;
	sfg::CheckButton::Ptr behindbutton_;

	Object* object_;
};