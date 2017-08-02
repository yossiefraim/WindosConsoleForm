#pragma once

#include "../Control/Control.h"
#include <string>

using namespace std;

struct MouseListener{
	virtual void mousePressed(Control& b, short x, short y, bool isLeft) = 0;
};

struct EmptyListener: public MouseListener{
	virtual void mousePressed(Control& b, short x, short y, bool isLeft){};
};

class Button : public Control
{
protected:
	string text;
	bool clickable;
	MouseListener* listener;
public:
	Button(int width, string text);

	void draw(Graphics &graphics, int x, int y, size_t w);
	void setValue(string value);
	void mousePressed(short, short, bool);
	string getValue();
	void addListener(MouseListener&);
	void keyDown(WORD, CHAR);

	~Button();
};

