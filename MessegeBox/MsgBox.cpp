#include "MsgBox.h"


MsgBox::MsgBox(int height, int width) : Panel(height, width)
{
	setLayer(2);
	ifSelected = false;
	Label *title = new Label(width - 2, "Are you Sure?");
	Label *text = new Label(width - 2, "Press OK");
	Button *okBtn = new Button(width / 2, Label::makeStringInTheMiddle(width/2, "OK!"));
	CloseListener *closeListener = new CloseListener(*this);
	okBtn->addListener(*closeListener);
	title->setLayer(2);
	text->setLayer(2);
	okBtn->setLayer(2);
	title->setBorder(BorderType::Single);
	text->setBorder(BorderType::Single);
	okBtn->setBorder(BorderType::Single);
	addControl(title, 1,1);
	addControl(text,1,4);
	addControl(okBtn, (width / 4), height-4);
}

void MsgBox::mousePressed(short x, short y, bool isLeft) {
	if (x < this->MoveLeft() || (x > this->MoveLeft() + this->getWidth()) ||
		y < this->MoveTop() || (y > this->MoveTop() + this->getHeight())) {
		if (isVisible()){
			hide();
		}
	}

	controls[2]->mousePressed(x, y, isLeft);
}

void MsgBox::setText(string text) {
	static_cast<Label*>(controls[1])->setValue(text);
}

void MsgBox::setTitle(string text) {
	static_cast<Label*>(controls[0])->setValue(text);
}

void MsgBox::keyDown(WORD click, CHAR chr){
	if (click == VK_RETURN) {
		hide();
	}
}

void MsgBox::show(){
	Control::show();
	openMsgBtn();
}

void MsgBox::hide(){
	Control::hide();
	closeMsgBtn();
}

