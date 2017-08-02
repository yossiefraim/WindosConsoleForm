#include "TextBox.h"


TextBox::TextBox(int width) : Control(width) , curserPosition(){}

void TextBox::setValue(string val) {
	value = val.substr(0, getWidth() - 2);
	curserPosition = value.substr(0, getWidth() - 2).length() + 1;
}

string TextBox::getValue() {
	return value;
}

void TextBox::draw(Graphics& graphics, int x, int y, size_t layer) {
	if (getLayer() != layer) return;
	Control::draw(graphics, x, y, layer);
	graphics.setBackground(graphics.convertToColor(getBackGround()));
	graphics.setForeground(graphics.convertToColor(getForeground()));
	string toPrint = value.substr(0, getWidth() - 2);
	if (toPrint.length() < getWidth() - 2) {
		toPrint = toPrint + string(getWidth() - 2 - toPrint.length(), ' ');
	}
	graphics.write(MoveBodyLeft(), MoveBodyTop(), toPrint);
	if (isFocus()) {
		if(Control::getFocus() == this) graphics.setCursorVisibility(true);
	} 
	graphics.resetColors();
}

int TextBox::getCurserPosition() {
	return curserPosition;
}

void TextBox::moveCurser(Graphics g){
	if (getCurserPosition() > getWidth()-2){
		g.moveTo(MoveBodyLeft() + getCurserPosition() - 2, MoveBodyTop());
	}
	else if (curserPosition == 1){
		g.moveTo(MoveBodyLeft(), MoveBodyTop());
	} else {
		g.moveTo(MoveBodyLeft() + getCurserPosition() - 1, MoveBodyTop());
	}
}

void TextBox::keyDown(WORD kind, CHAR c) {

	switch (kind)
	{
		case VK_DOWN:
		case VK_UP:
		case VK_RETURN:
			break;

		case VK_RIGHT:
			moveRight();
			break;

		case VK_LEFT:
			moveLeft();
			break;

		case VK_RWIN:
			moveRight();
			break;

		case VK_LWIN:
			moveLeft();
			break;

		case VK_BACK:
			deleteLeft();
			break;

		case VK_DELETE:
			deleteRight();
			break;

		default:
			addCharecter(c);
			break;
	}
}

void TextBox::mousePressed(short x, short y, bool b){
	Control::mousePressed(x, y, b);
}


void TextBox::moveRight(){
	int x = MoveBodyLeft() + getWidth();
	if (MoveBodyLeft() + curserPosition > MoveBodyLeft() +  getWidth() - 3) return;
	curserPosition++;
}

void TextBox::moveLeft(){
	if (curserPosition ==  1) return;
	curserPosition--;
}

void TextBox::deleteLeft(){
	if (curserPosition == 1 || !value.length()) {
		moveLeft();
		return;
	}
	value.erase(curserPosition - 2, 1);
	moveLeft();
}

void TextBox::deleteLast(){
	value.erase(getWidth() - 2, 1);
}

void TextBox::deleteRight(){
	if (curserPosition > value.length()) return;
	value.erase(curserPosition - 1, 1);
}

void TextBox::addCharecter(CHAR c){
	if (value.length() == getWidth() - 2) {
		return;
	}
	else if (!value.length()) {
		value = string("");
		value.insert(0, 1, c);
	}
	else value.insert(curserPosition - 1, 1, c);
	moveRight();
}


TextBox::~TextBox() {}
