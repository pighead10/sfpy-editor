#include "TextDialogBox.h"
#include "Gui.h"
#include "GameManager.h"

TextDialogBox::TextDialogBox(Gui* parent, std::string title, std::string text, std::function<void(std::string)> applyfunc):applyfunc_(applyfunc),parent_(parent){
	initgui(title, text);
}

TextDialogBox::~TextDialogBox(){
	using namespace sfg;
	/*auto widget = Context::Get().GetActiveWidget();

	while (widget->GetName() != "Window"){
		widget = widget->GetParent();
	}
	parent_->getDesktop()->Remove(widget);*/

	parent_->getDesktop()->Remove(window_);
}

void TextDialogBox::applyPressed(){
	applyfunc_(entry_->GetText());
	delete this;
}

void TextDialogBox::initgui(std::string title,std::string text){
	using namespace sfg;
	window_ = Window::Create();
	window_->SetTitle(title);

	parent_->subscribeWidgetClicked(window_);

	auto box = Box::Create(Box::Orientation::VERTICAL, 5.0f);
	entry_ = Entry::Create();
	auto label = Label::Create(text);

	auto applybutton = Button::Create("Apply");

	box->Pack(entry_);
	box->Pack(label);
	box->Pack(applybutton);

	window_->Add(box);

	applybutton->GetSignal(Widget::OnLeftClick).Connect(std::bind(&TextDialogBox::applyPressed,this));
	parent_->subscribeWidgetClicked(applybutton);
	parent_->getDesktop()->Add(window_);
	
}