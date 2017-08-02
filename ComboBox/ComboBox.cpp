#include "ComboBox.h"
#include <iostream>

ComboBox::ComboBox(int width,
	vector<string> options) : ListPanel(getHeight(),
		width, 
		options), 
	closeHeight(5),
	isOpen(false), choosenIndex(0){
	setLayer(1);
	int len = options.size();
	openHeight = (len + 1) * 3 + 2;
	setHeight(openHeight);
	int wid = getWidth();
	Label *choosen = new Label(getWidth() - 7, options[0]);
	choosen->setLayer(1);
	choosen->setBorder(BorderType::Single);
	addControl(choosen, MoveBodyLeft(), MoveBodyTop());
	Button *toggleBtn = new Button(1, "+");
	toggleBtn->setBackGround(BackgroundColor::Black);
	toggleBtn->setBorder(BorderType::Single);
	ToggleListener* lsnr = new ToggleListener(*this);
	toggleBtn->addListener(*lsnr);
	toggleBtn->setLayer(1);
	addControl(toggleBtn, MoveBodyLeft() + getWidth() - 5, MoveBodyTop());

	string str = string(Control::getWidth(),' ');
	for (int i = 0; i < len; i++) {
		string insert = (options[i]+str).substr(0, getWidth() - options[i].length() - 3);
		ButtonItem *btn = new ButtonItem(insert, getWidth() - 4, i);
		btn->setLayer(1);
		btn->setBorder(BorderType::None);
		SelectListener* lsnr = new SelectListener(*this);
		btn->addListener(*lsnr);
		addControl(btn, MoveBodyLeft(), MoveBodyTop() + ((i+1) * 3));
	}

	setHeight(closeHeight);
}


size_t ComboBox::getSelectedIndex() {
	return choosenIndex;
}

void ComboBox::setSelectedIndex(size_t index) {
	choosenIndex = index;
	string item = static_cast<Button*>(controls[index + 2])->getValue();
	item = item.substr(4, getWidth());
	static_cast<Label*>(controls[0])->setValue(item);
	closeList();
}


void ComboBox::draw(Graphics &graphics, int, int, size_t layer) {
	int la = getLayer();
	if (getLayer() != layer) return;
	Control::draw(graphics, MoveLeft(), MoveTop(), layer);
	graphics.setBackground(graphics.convertToColor(getBackGround()));
	graphics.setForeground(graphics.convertToColor(getForeground()));
	for (int i = 0; i < 2; i++) {
		graphics.moveTo(controls[i]->MoveBodyLeft(), controls[i]->MoveBodyTop());
		controls[i]->draw(graphics, controls[i]->MoveBodyLeft(), controls[i]->MoveBodyTop(), layer);
	}
	if (isOpen) {
		int size = controls.size();
		for (int i = 2; i < size; i++) {
			graphics.moveTo(controls[i]->MoveBodyLeft(), controls[i]->MoveBodyTop());
			controls[i]->draw(graphics, controls[i]->MoveBodyLeft(), controls[i]->MoveBodyTop(), layer);
		}
	}
	graphics.resetColors();
}

void ComboBox::onDownKey() {
	if (!isOpen) return;
	int item = itemInFocus();
	if (item != -1) {
		controls[item]->unfocus();
		if (item >= controls.size() - 1) item = 2;
		else item += 1;
	}
	else item = 2;
	controls[item]->focus();
}
void ComboBox::onUpKey() {
	if (!isOpen) return;
	int item = itemInFocus();
	if (item != -1) {
		controls[item]->unfocus();
		if (item == 2) item = controls.size() - 1;
		else item -= 1;
	}
	else item = 2;
	controls[item]->focus();
}

void ComboBox::onEnterKey(){
	if (itemInFocus() == -1 || !isOpen) return;
	setSelectedIndex(itemInFocus() - 2);
}

void ComboBox::mousePressed(short x, short y , bool isLeft) {
	if (x < this->MoveLeft() || (x > this->MoveLeft() + this->getWidth()) ||
		y < this->MoveTop() || (y > this->MoveTop() + this->getHeight())) {
		closeList();
		return;
	}
	Control::setFocus(this);
	if (x == MoveBodyLeft() + getWidth() - 5 && y == MoveBodyTop()) {
		controls[1]->mousePressed(x, y, isLeft);
	}
	int size = controls.size();
	for (int i = 0; i < size; i++) {
		controls[i]->mousePressed(x, y, isLeft);
	}
}

void ComboBox::unfocus(){
	ListPanel::unfocus();
	closeList();
}

void ComboBox::toggle() {
	if (isOpen) closeList();
	else openList();
}

void ComboBox::closeList() {
	isOpen = false;
	setHeight(closeHeight);
}

void ComboBox::openList() {
	isOpen = true;
	setHeight(openHeight);
}

ComboBox::~ComboBox()
{
	Panel::~Panel();
	free(choosenItem);
	free(toogleBtn);
}
