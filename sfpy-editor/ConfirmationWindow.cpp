#include "ConfirmationWindow.h"
#include "Gui.h"
#include "GameManager.h"

ConfirmationWindow::ConfirmationWindow(Gui* parent,std::string title, std::string message, std::string arg,
	std::function<void(std::string)> yesfunc, std::function<void(std::string)> nofunc) :nofunc_(nofunc), yesfunc_(yesfunc),
	parent_(parent), arg_(arg){
	initgui(title,message);
}

ConfirmationWindow::~ConfirmationWindow(){
	using namespace sfg;
	auto widget = Context::Get().GetActiveWidget();

	while (widget->GetName() != "Window"){
		widget = widget->GetParent();
	}
	parent_->getDesktop()->Remove(widget);

}

void ConfirmationWindow::yesSelected(){
	yesfunc_(arg_);
	delete this;
}

void ConfirmationWindow::noSelected(){
	nofunc_(arg_);
	delete this;
}

void ConfirmationWindow::initgui(std::string title,std::string message){
	using namespace sfg;
	window_ = Window::Create();
	window_->SetTitle(title);

	parent_->subscribeWidgetClicked(window_);

	auto layout = Box::Create(Box::Orientation::VERTICAL);
	auto box1 = Box::Create(Box::Orientation::HORIZONTAL);

	auto label = Label::Create(message);
	box1->Pack(label);

	auto box2 = Box::Create(Box::Orientation::HORIZONTAL);
	auto yesbutton = Button::Create("Yes");
	auto nobutton = Button::Create("No");

	box2->Pack(yesbutton);
	box2->Pack(nobutton);

	layout->Pack(box1);
	layout->Pack(box2);

	window_->Add(layout);

	
	parent_->subscribeWidgetClicked(yesbutton);
	parent_->subscribeWidgetClicked(nobutton);
	yesbutton->GetSignal(Widget::OnLeftClick).Connect(std::bind(&ConfirmationWindow::yesSelected, this));
	nobutton->GetSignal(Widget::OnLeftClick).Connect(std::bind(&ConfirmationWindow::noSelected, this));

	parent_->getDesktop()->Add(window_);
}