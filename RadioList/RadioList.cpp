#include "RadioList.h"


RadioList::RadioList(int height, int width, vector<string> options) : ListPanel(height, width, options)
{
	int len = options.size();
	for (int i = 0; i < len; i++) {
		ButtonItem *btn = new ButtonItem(options[i], getWidth() - 4, i);
		btn->setBorder(BorderType::Single);
		SelectListener* lsnr = new SelectListener(*this);
		btn->addListener(*lsnr);
		addControl(btn, MoveBodyLeft(), MoveBodyTop() + (i * 3));
	}
}

void RadioList::onEnterKey() {
	if (itemInFocus() == -1) return;
	setSelectedIndex(itemInFocus());
}


size_t RadioList::getSelectedIndex() {
	
	getAllControls(controls);
	int size = controls.size();
	for (int i = 0; i < size; i++) {
		if (static_cast<ButtonItem*>(controls[i])->isChecked()) 
			return static_cast<ButtonItem*>(controls[i])->getIndex();
	}
	return -1;
}

void RadioList::setSelectedIndex(size_t index) {
	clearAllFocus();
	static_cast<ButtonItem*>(controls[index])->toggle();
	switchFocus(index);
}

void RadioList::mousePressed(short x, short y, bool isLeft) {
	Control::mousePressed(x, y, isLeft);
	int size = controls.size();
	for (int i = 0; i < size; i++) {
		controls[i]->mousePressed(x, y, isLeft);
	}
}

