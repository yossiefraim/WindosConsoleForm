#pragma once

#include "../Panel/Panel.h"
#include "../Button/Button.h"
#include "../Label/Label.h"



class MsgBox : public Panel
{

	struct CloseListener : public MouseListener {
		CloseListener(Control& c) : _c(c) {}
		void mousePressed(Control& b, short x, short y, bool isLeft) {
			_c.hide();
		}
	private:
		Control& _c;
	};


public:
	MsgBox(int height, int width);
	void setText(string text);
	void setTitle(string text);
	void mousePressed(short, short, bool);
	void keyDown(WORD, CHAR);
	void show();
	void hide();
};

