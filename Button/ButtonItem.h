#pragma once

#include "Button.h"
#include <string>

using namespace std;

class ButtonItem : public Button
{
	size_t index;
	string chekeForText;
	bool isCheck;
	
public:
	void draw(Graphics &graphics, int x, int y, size_t w);
	ButtonItem(string text, int width, size_t index);
	void toggle();
	size_t getIndex();
	bool isChecked();
	~ButtonItem();
};

