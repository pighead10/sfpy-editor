#include "ScriptWindow.h"
#include "Script.h"
#include "GameManager.h"
#include "Gui.h"
#include "NotificationWindow.h"

ScriptWindow::ScriptWindow(Gui* parent, GameManager* game_manager, std::string name, MenuItem* menu_item){
	construct(parent, game_manager, name, menu_item);
}

ScriptWindow::~ScriptWindow(){
}

void ScriptWindow::applySettings(){
	std::string name = nameentry_->GetText();
	Script* compare = game_manager_->getScriptByName(name);
	if (compare != NULL && compare != compare){
		std::cout << "ERROR: Name already in use in Script " + name << std::endl;
		NotificationWindow* note = new NotificationWindow(parent_, "Could not apply settings", "The name you entered is already in use.");
	}
	else{
		std::string filename = fileentry_->GetText();
		if (!isNameValid(name)){
			NotificationWindow* note = new NotificationWindow(parent_, "Could not apply settings", "Invalid name. Make sure name starts with a letter and contains only alphanumeric characters, -, and _.");
		}
		else if (!isFilenameValid(filename, ".py")){
			NotificationWindow* note = new NotificationWindow(parent_, "Could not apply settings", "Invalid file name. Ensure it starts with a letter, contains only alphanumeric characters, - and _, and ends in .py.");
		}
		else{
			script_->setName(name);
			setName(name);
			window_->SetTitle("Script: " + name_);
			script_->setFilename(filename);
		}	
	}
}

void ScriptWindow::onDeletePressed(){
	parent_->requestDeleteScript(getName());
}

void ScriptWindow::createElements(){
	using namespace sfg;
	type_ = Gui::GUI_SCRIPT;
	script_ = game_manager_->getScriptByName(name_);
	window_->SetTitle("Script: " + name_);

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
	fileentry_->SetText(script_->getFilename());

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