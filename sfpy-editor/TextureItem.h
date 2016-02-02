#pragma once

#include "MenuItem.h"

class TextureItem : public MenuItem{
public:
	TextureItem(Gui* parent, std::string name);
	void selected();
};