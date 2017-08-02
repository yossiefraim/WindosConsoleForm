#include "ButtonItem.h"


ButtonItem::ButtonItem(string text, int width, size_t index)
	: Button(width, "[ ] " + text), chekeForText("[X] " + text), index(index), isCheck(false){}

bool ButtonItem::isChecked(){
	return isCheck;
}
void ButtonItem::draw(Graphics &graphics, int x, int y, size_t layer){
	if (getLayer() != layer) return;
	Control::draw(graphics, MoveLeft(), MoveTop(), layer);
	if (isFocus()){
		graphics.setBackground(graphics.convertToColor(getForeground()));
		graphics.setForeground(graphics.convertToColor(getBackGround()));
	} else if (isChecked()){
		graphics.setBackground(graphics.convertToColor(BackgroundColor::Cyan));
		graphics.setForeground(graphics.convertToColor(ForegroundColor::White));
	} else {
		graphics.setBackground(graphics.convertToColor(getBackGround()));
		graphics.setForeground(graphics.convertToColor(getForeground()));
	}
	graphics.write(MoveBodyLeft(), MoveBodyTop(), getValue());
	graphics.resetColors();
}
void ButtonItem::toggle(){
	isCheck = !isCheck;
	string tmp = text;
	text = chekeForText;
	chekeForText = tmp;
}
size_t ButtonItem::getIndex(){
	return index;
}
ButtonItem::~ButtonItem(){}
