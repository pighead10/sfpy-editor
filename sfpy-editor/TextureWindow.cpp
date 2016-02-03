#include "TextureWindow.h"
#include "Texture.h"
#include "GameManager.h"
#include "Gui.h"
#include "NotificationWindow.h"

TextureWindow::TextureWindow(Gui* parent, GameManager* game_manager, std::string name, MenuItem* menu_item){
	construct(parent, game_manager, name, menu_item);
}

TextureWindow::~TextureWindow(){
}

void TextureWindow::applySettings(){
	std::string name = nameentry_->GetText();
	Texture* compare = game_manager_->getTextureByName(name);
	if (compare != NULL && compare != compare){
		std::cout << "ERROR: Name already in use in texture " + name << std::endl;
		NotificationWindow* note = new NotificationWindow(parent_, "Could not apply settings", "The name you entered is already in use.");
	}
	else{
		std::string filename = fileentry_->GetText();
		if (!isNameValid(name)){
			NotificationWindow* note = new NotificationWindow(parent_, "Could not apply settings", "Invalid name. Make sure name starts with a letter and contains only alphanumeric characters, -, and _.");
		}
		else if (!isFilenameValid(filename, ".png")){
			NotificationWindow* note = new NotificationWindow(parent_, "Could not apply settings", "Invalid file name. Ensure it starts with a letter, contains only alphanumeric characters, - and _, and ends in .png.");
		}
		else{
			texture_->setName(name);
			setName(name);
			window_->SetTitle("Texture: " + name_);
			texture_->setFilename(filename);
		}
	}
}

void TextureWindow::onDeletePressed(){
	parent_->requestDeleteTexture(getName());
}

void TextureWindow::createElements(){
	using namespace sfg;
	type_ = Gui::GUI_TEXTURE;
	texture_ = game_manager_->getTextureByName(name_);
	window_->SetTitle("Texture: " + name_);

	auto namebox = Box::Create(Box::Orientation::HORIZONTAL, 5);
	auto filebox = Box::Create(Box::Orientation::HORIZONTAL, 5);
	auto donebox = Box::Create(Box::Orientation::HORIZONTAL, 5);
	auto layoutbox = Box::Create(Box::Orientation::VERTICAL, 5);


	nameentry_ = Entry::Create();
	nameentry_->SetRequisition(maths::Vector2(200, 0));
	nameentry_->SetText(name_);

	auto namelabel = Label::Create("Name");
	namebox->Pack(namelabel);
	namebox->Pack(nameentry_);

	fileentry_ = Entry::Create();
	fileentry_->SetRequisition(maths::Vector2(200, 0));
	fileentry_->SetText(texture_->getFilename());
	
	auto filelabel = Label::Create("File name");
	filebox->Pack(filelabel);
	filebox->Pack(fileentry_);

	donebox->Pack(delete_button_);
	donebox->Pack(apply_button_);

	layoutbox->Pack(namebox);
	layoutbox->Pack(filebox);
	layoutbox->Pack(donebox);
	
	window_->Add(layoutbox);
}