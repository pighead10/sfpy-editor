#include "PropertyWindow.h"

class Object;

class ObjectWindow : public PropertyWindow{
public:
	ObjectWindow(Gui* parent, GameManager* game_manager, std::string name); //no constructor inheritance in VS2013 :(
protected:
	void applySettings();
	void createElements();
private:
	sfg::Entry::Ptr nameentry_;
	sfg::Entry::Ptr spriteentry_;
	sfg::CheckButton::Ptr visbutton_;
	sfg::CheckButton::Ptr colbutton_;

	Object* object_;
};