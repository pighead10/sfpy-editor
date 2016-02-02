#include "SoundWindow.h"
#include "Sound.h"
#include "GameManager.h"
#include "Gui.h"

SoundWindow::SoundWindow(Gui* parent, GameManager* game_manager, std::string name, MenuItem* menu_item){
	construct(parent, game_manager, name, menu_item);
}

SoundWindow::~SoundWindow(){
}

void SoundWindow::applySettings(){
	std::string name = nameentry_->GetText();
	Sound* compare = game_manager_->getSoundByName(name);
	if (compare != NULL && compare != compare){
		std::cout << "ERROR: Name already in use in Sound " + name << std::endl;
	}
	else{
		sound_->setName(name);
		setName(name);
		window_->SetTitle("Sound: " + name_);
		std::string filename = fileentry_->GetText();
		sound_->setFilename(filename);
	}
}

void SoundWindow::onDeletePressed(){
	parent_->requestDeleteSound(getName());
}

void SoundWindow::createElements(){
	using namespace sfg;
	type_ = Gui::GUI_SOUND;
	sound_ = game_manager_->getSoundByName(name_);
	window_->SetTitle("Sound: " + name_);

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
	fileentry_->SetText(sound_->getFilename());

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