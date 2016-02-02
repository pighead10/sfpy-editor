#include "ObjectItem.h"
#include "Gui.h"

ObjectItem::ObjectItem(Gui* parent, std::string name){
	init(parent, name,Gui::GUI_OBJECT);
}

void ObjectItem::selected(){
	parent_->objectSelected(name_);
}