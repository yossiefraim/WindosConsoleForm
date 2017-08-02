#include "Button.h"

Button::Button(int width, string text) : Control(width), text(text), clickable(true), listener(&EmptyListener()){

}

void Button::draw(Graphics& graphics, int x, int y, size_t layer){
	if (getLayer() != layer) return;
	Control::draw(graphics, x, y, layer);
	graphics.setBackground(graphics.convertToColor(getBackGround()));
	graphics.setForeground(graphics.convertToColor(getForeground()));
	graphics.write(MoveBodyLeft(), MoveBodyTop(), getValue());
	graphics.resetColors();
}



void Button::keyDown(WORD click, CHAR chr){
	if (click == VK_RETURN) {
		listener->mousePressed(*this, 0, 0, true);
	}
}

void Button::mousePressed(short a, short b, bool isLeft) {
	if (clickable && a > MoveLeft() && a < MoveLeft() + getWidth() && b > MoveTop() && b < MoveTop() + getHeight()) {
		listener->mousePressed(*this, a, b, isLeft);
	}
}

void Button::setValue(string value){
	text = value;
}
void Button::addListener(MouseListener& listnr){
	listener = &listnr;
}
string Button::getValue(){
	return text;
}

Button::~Button(){
	free(listener);
}
