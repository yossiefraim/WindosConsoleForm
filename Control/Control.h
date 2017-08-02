#pragma once

#include <Windows.h> 
#include "../Graphics/Graphics.h"
#include <vector>


using namespace std;

enum class BorderType {Single, Double, None};

class Control
{
	bool isSelected, visible;
	COORD location;
	COORD bodyLocation;
	ForegroundColor foreground;
	BackgroundColor background;
	BorderType borderType;
	int width, height, layer;

protected:
	bool ifSelected;

public:
	Control(int width);
	virtual void show();
	virtual void hide();
	int getLayer();
	void setLayer(int);
	void setForeground(ForegroundColor color);
	void setBackGround(BackgroundColor color);
	void setBorder(BorderType type);
	virtual void setLocation(COORD);
	ForegroundColor getForeground();
	BackgroundColor getBackGround();
	COORD getLocation();
	BorderType getBorderType();
	char getBorderTHor();
	char getBorderTVer();
	vector<int> getBorderTCor();
	virtual void draw(Graphics& graphics, int, int, size_t);
	virtual void keyDown(WORD, CHAR) = 0;
	virtual void mousePressed(short, short, bool) = 0;
	virtual void focus();
	virtual void unfocus();
	bool canGetFocus();
	bool validSpace(Control* c);
	bool isFocus();
	bool isVisible();
	short MoveLeft();
	short MoveTop();
	short MoveBodyLeft();
	short MoveBodyTop();
	void setHeight(int);
	void setWidth(int);
	int getWidth();
	int getHeight();
	virtual void getAllControls(vector<Control *> &controls) {}

	static void setFocus(Control* c);
	static Control* getFocus();

	virtual ~Control();
};

static Control* currentFocused = NULL;
