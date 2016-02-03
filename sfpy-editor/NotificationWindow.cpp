#include "NotificationWindow.h"
#include "Gui.h"

NotificationWindow::NotificationWindow(Gui* parent, std::string title, std::string message):parent_(parent){
	initgui(title, message);
}

NotificationWindow::~NotificationWindow(){
	using namespace sfg;
	auto widget = Context::Get().GetActiveWidget();

	while (widget->GetName() != "Window"){
		widget = widget->GetParent();
	}
	parent_->getDesktop()->Remove(widget);
}

void NotificationWindow::buttonPressed(){
	delete this;
}

void NotificationWindow::initgui(std::string title, std::string message){
	using namespace sfg;
	auto window = Window::Create();

	window->SetTitle(title);
	auto label = Label::Create(message);

	auto box = Box::Create(Box::Orientation::VERTICAL, 5.0f);
	auto button = Button::Create("Ok");

	box->Pack(label);
	box->Pack(button);
	
	window->Add(box);

	button->GetSignal(Widget::OnLeftClick).Connect(std::bind(&NotificationWindow::buttonPressed, this));
	parent_->subscribeWidgetClicked(button);
	parent_->subscribeWidgetClicked(window);

	parent_->getDesktop()->Add(window);
}