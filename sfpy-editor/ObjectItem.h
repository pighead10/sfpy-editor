#pragma once

#include "MenuItem.h"

class ObjectItem : public MenuItem{
public:
	ObjectItem(Gui* parent, std::string name);
	void selected();
};