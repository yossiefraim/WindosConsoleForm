#include "Panel.h"


Panel::Panel(int height, int width) : Control(width) {
	setHeight(height);
}

void Panel::getAllControls(vector<Control *> &cont) {
	for (int i = 0; i < controls.size(); i++) {
		cont.push_back(controls[i]);
	}
}

bool Panel::addControl(Control *control, short x, short y) {
	control->setLocation({ x , y });
	if (validSpace(control)) {
		controls.push_back(control);
		return true;
	}
	
	return false;
}

bool Panel::validSpace(Control* c) {
	short bodyTop = MoveBodyTop();
	short bodyLeft = MoveBodyLeft();
	short controllerTop = c->MoveTop();
	short controllerLeft = c->MoveLeft();

	if (controllerTop < bodyTop || controllerLeft < bodyLeft) return false;
	if ((controllerTop + c->getHeight()) > (bodyTop + this->getHeight() - 2)) return false;
	if ((controllerLeft + c->getWidth() - 2) > (bodyLeft + this->getWidth() - 2)) return false;

	if (c->getLayer() == 2) return true;
	return validSpaceWithControllers(c);
}

bool Panel::validSpaceWithControllers(Control* c) {
	int size = controls.size();
	bool valid = true;
	for (int i = 0; i < size; i++) {
		if (controls[i]->getLayer() == 2) continue;
		if (!controls[i]->validSpace(c)) {
			valid = false;
			break;
		}
	}
	return valid;
}

void Panel::mousePressed(short x, short y, bool isLeft) {
	if (x < this->MoveLeft() || (x > this->MoveLeft() + this->getWidth())) return;
	if (y < this->MoveTop() || (y > this->MoveTop() + this->getHeight())) return;

	int size = controls.size();
	for (int i = 0; i < size; i++) {
		controls[i]->mousePressed(x, y, isLeft);
	}
}

void Panel::draw(Graphics &graphics, int x, int y, size_t layer) {
	if (!isVisible()) return;
	if (layer == getLayer()) Control::draw(graphics, MoveLeft(), MoveTop(), layer);
	graphics.setBackground(graphics.convertToColor(getBackGround()));
	graphics.setForeground(graphics.convertToColor(getForeground()));

	int size = controls.size();
	for (int i = 0; i < size; i++) {
		graphics.moveTo(controls[i]->MoveBodyLeft(), controls[i]->MoveBodyTop());
		controls[i]->draw(graphics, controls[i]->MoveBodyLeft(), controls[i]->MoveBodyTop(), layer);
	}
	graphics.resetColors();
}

void Panel::setLocation(COORD coord) {
	COORD tmp = {MoveBodyLeft(),MoveBodyTop()};
	short moveVer, moveHer;
	Control::setLocation(coord);
	int size = controls.size();
	for (size_t i = 0; i < size; i++) {
		moveVer = controls[i]->MoveBodyTop() - tmp.Y;
		moveHer = controls[i]->MoveBodyLeft() - tmp.X;
		controls[i]->setLocation({ coord.X + moveHer, coord.Y + moveVer});
	}
}

void Panel::openMsgBtn(){
	isMsgBoxOpen = true;
}

void Panel::closeMsgBtn(){
	isMsgBoxOpen = false;
}

bool Panel::getMsgOpen(){
	return isMsgBoxOpen;
}

Panel::~Panel() {
	for (int i = 0; i < controls.size(); i++) {
		free(controls[i]);
	}
}
