#include "Label.h"


Label::Label(int width, string value):Control(width)
{
	ifSelected = false;
	if (width - value.size() < 2) this->value = value;
	else {this->value = makeStringInTheMiddle(width, value);}
}


void Label::draw(Graphics &graphics, int x , int y, size_t layer) {
	if (getLayer() != layer) return;
	Control::draw(graphics, x, y, layer);
	graphics.setBackground(graphics.convertToColor(getBackGround()));
	graphics.setForeground(graphics.convertToColor(getForeground()));
	graphics.write(MoveBodyLeft(),MoveBodyTop(), value);
	graphics.resetColors();
}

void Label::setValue(string val) {
	value = makeStringInTheMiddle(getWidth() - 2, val);
}

string Label::makeStringInTheMiddle(int width, string value) {
	
	int mid = (width / 2) - (value.length() / 2);
	string str;
	str.resize(width - value.length());
	str.insert(mid, value);
	return str;
}

string Label::getValue() {
	return value;
}

Label::~Label()
{
}