#include "Control.h"

Control::Control(int _width) : 
			width(_width), 
			isSelected(false),
			ifSelected(true),
			visible(true), 
			height(1),
			layer(0){
	setBorder(BorderType::None);
	setLocation({ 0, 0 });
	width += 2;
	height += 2;
	background = BackgroundColor::Black;
	foreground = ForegroundColor::Green;
}

ForegroundColor Control::getForeground() {
	return foreground;
}
BackgroundColor Control::getBackGround() {
	return background;
}


int Control::getLayer() {
	return layer;
}

void Control::setLayer(int l) {
	layer = l;
}

void Control::focus(){
	isSelected = true;
}
void Control::unfocus(){
	isSelected = false;
}
void Control::setForeground(ForegroundColor color){
	foreground = color;
}
void Control::show() {
	visible = true;
	ifSelected = true;
}
void Control::hide() {
	visible = false;
	ifSelected = false;
}
void Control::setBackGround(BackgroundColor color){
	background = color;
}


void Control::setBorder(BorderType type){
	borderType = type;
}

BorderType Control::getBorderType(){
	return borderType;
}
char Control::getBorderTHor(){

	if (getBorderType() == BorderType::Double) {
		return 205;
	}
	else if (getBorderType() == BorderType::Single) {
		return 196;
	}
	else if (getBorderType() == BorderType::None) {
		return NULL;
	}
}

char Control::getBorderTVer(){
	
	if (getBorderType() == BorderType::Single) {
		return 179;
	}
	else if (getBorderType() == BorderType::Double) {
		return 186;
	}
	else if (getBorderType() == BorderType::None) {
		return NULL;
	}
}

vector<int> Control::getBorderTCor(){
	if (getBorderType() == BorderType::Single) {
		return{ 218, 191 , 192, 217 };
	}
	else if (getBorderType() == BorderType::Double) {
		return{ 201, 187, 200 , 188 };
	}
	else if (getBorderType() == BorderType::None) {
		return{0,0,0,0};
	}
}
void Control::setLocation(COORD coord){
	location = coord;
	bodyLocation = { coord.X + 1, coord.Y + 1 };
}

COORD Control::getLocation(){
	return location;
}
void Control::draw(Graphics &graphics, int x, int y, size_t w){
	if (isFocus()) {
		graphics.setForeground(graphics.convertToColor(ForegroundColor::White));
	} else {
		graphics.setForeground(graphics.convertToColor(getForeground()));
	}
	graphics.setBackground(graphics.convertToColor(getBackGround()));
		string str(width, getBorderTHor());
			vector<int> corners = getBorderTCor();
			str[0] = corners[0];
			str[width - 1] = corners[1];
				graphics.write(MoveLeft(), MoveTop(), str);
	
	for (int i = 0; i < height - 1; i++){
		string strv(width, ' ');
		strv[0] = getBorderTVer();
		strv[width-1] = getBorderTVer();
		graphics.write(MoveLeft(), (MoveTop() + 1 ) + i, strv);
	}
	str[0] = corners[2];
	str[width - 1] = corners[3];
	graphics.write(location.X, location.Y + (height - 1), str);
	graphics.resetColors();
}

void Control::mousePressed(short x, short y, bool isLeft){

	if (x < this->MoveLeft() || (x > this->MoveLeft() + this->getWidth())) return;
	if (y < this->MoveTop() || (y > this->MoveTop() + this->getHeight())) return;

	Control::setFocus(this);
}

bool Control::validSpace(Control* control){

	if ((control->MoveLeft() + control->getWidth()) < MoveLeft() ||
		(MoveLeft() + getWidth()) < control->MoveLeft()) {
		return true;
	}
	else if ( (control->MoveTop() + control->getHeight() ) > MoveTop() ||
		(MoveTop() + getHeight()) < control->MoveTop()) {
		return true;;
	}
	return false;
}
bool Control::isFocus(){
	return isSelected;
}
bool Control::isVisible(){
	return visible;
}
bool Control::canGetFocus() {
	return ifSelected;
}

short Control::MoveLeft(){
	return location.X;
}
short Control::MoveTop(){
	return location.Y;
}

short Control::MoveBodyLeft(){
	return bodyLocation.X;
}
short Control::MoveBodyTop(){
	return bodyLocation.Y;
}

int Control::getWidth(){
	return width;
}
int Control::getHeight(){
	return height;
}

void Control::setHeight(int h) {
	height = h;
}

void Control::setWidth(int w) {
	width = w;
}

	
void Control::setFocus(Control* control){
	if (currentFocused != NULL)
		currentFocused->unfocus();
	currentFocused = control;
	control->focus();
}

Control* Control::getFocus(){
	return currentFocused;
}


Control::~Control(){

}