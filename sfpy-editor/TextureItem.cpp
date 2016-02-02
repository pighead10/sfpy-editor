#include "TextureItem.h"

TextureItem::TextureItem(Gui* parent, std::string name){
	init(parent, name, Gui::GUI_TEXTURE);
}

void TextureItem::selected(){
	parent_->textureSelected(name_);
}