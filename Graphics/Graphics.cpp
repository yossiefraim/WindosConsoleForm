#include "Graphics.h"

Graphics::Graphics(DWORD stdHandle)
	: _console(GetStdHandle(stdHandle)), _background(Color::Black), _foreground(Color::White)
{
	updateConsoleAttributes();
}

void Graphics::clearScreen()
{
	DWORD d;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(_console, &csbi);
	auto size = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputAttribute(_console, csbi.wAttributes, size, { 0, 0 }, &d);
	FillConsoleOutputCharacter(_console, L' ', size, { 0, 0 }, &d);
}

void Graphics::moveTo(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(_console, c);
}

void Graphics::setBackground(Color color)
{
	_background = color;
	updateConsoleAttributes();
}

void Graphics::setForeground(Color color)
{
	_foreground = color;
	updateConsoleAttributes();
}

void Graphics::write(string s)
{
	WriteConsoleA(_console, s.c_str(), s.size(), nullptr, nullptr);
}

void Graphics::write(wstring s)
{
	WriteConsoleW(_console, s.c_str(), s.size(), nullptr, nullptr);
}

void Graphics::write(int x, int y, string s)
{
	moveTo(x, y);
	write(s);
}

void Graphics::write(int x, int y, wstring s)
{
	moveTo(x, y);
	write(s);
}

void Graphics::resetColors() {
	_background = Color::Black;
	_foreground = Color::White;
	updateConsoleAttributes();
}

void Graphics::setCursorVisibility(bool isVisible){
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(_console, &cci);
	cci.bVisible = isVisible;
	SetConsoleCursorInfo(_console, &cci);
}

void Graphics::updateConsoleAttributes(){
	DWORD attributes = 0;

	switch (_foreground)
	{
	case Color::Black:	break;
	case Color::Blue:	attributes |= FOREGROUND_BLUE; break;
	case Color::Green:	attributes |= FOREGROUND_GREEN; break;
	case Color::Red:	attributes |= FOREGROUND_RED; break;
	case Color::Cyan:	attributes |= FOREGROUND_BLUE | FOREGROUND_GREEN; break;
	case Color::Purple:	attributes |= FOREGROUND_BLUE | FOREGROUND_RED; break;
	case Color::Orange: attributes |= FOREGROUND_GREEN | FOREGROUND_RED; break;
	case Color::White:	attributes |= FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED; break;
	}

	switch (_background)
	{
	case Color::Black:	break;
	case Color::Blue:	attributes |= BACKGROUND_BLUE; break;
	case Color::Green:	attributes |= BACKGROUND_GREEN; break;
	case Color::Red:	attributes |= BACKGROUND_RED; break;
	case Color::Cyan:	attributes |= BACKGROUND_BLUE | BACKGROUND_GREEN; break;
	case Color::Purple:	attributes |= BACKGROUND_BLUE | BACKGROUND_RED; break;
	case Color::White:	attributes |= BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED; break;
	}

	SetConsoleTextAttribute(_console, attributes);
}

bool isInside(int x, int y, int left, int top, int width, int height)
{
	x -= left;
	y -= top;
	return x >= 0 && y >= 0 && x < width && y < height;
}

Color Graphics::convertToColor(BackgroundColor b) {
	Color color = Color::Black;
	
	if (b == BackgroundColor::Black) {
		color = Color::Black;
	}
	else if (b == BackgroundColor::Blue) {
		color = color = Color::Blue;
	}
	else if (b == BackgroundColor::Red) {
		color = color = Color::Red;
	}
	else if (b == BackgroundColor::Green) {
		color = color = Color::Green;
	}
	else if (b == BackgroundColor::Purple) {
		color = color = Color::Purple;
	}
	else if (b == BackgroundColor::Cyan) {
		color = color = Color::Cyan;
	}
	else if (b == BackgroundColor::White) {
		color = color = Color::White;
	}

	return color;
}

Color Graphics::convertToColor(ForegroundColor f) {
	Color color = Color::White;
	
	if (f == ForegroundColor::Black) {
		color = Color::Black;
	}
	else if (f == ForegroundColor::Blue) {
		color = Color::Blue;
	}
	else if (f == ForegroundColor::Green) {
		color = Color::Green;
	}
	else if (f == ForegroundColor::Red) {
		color = Color::Red;
	}
	else if (f == ForegroundColor::Cyan) {
		color = Color::Cyan;
	}
	else if (f == ForegroundColor::Purple) {
		color = Color::Purple;
	}
	else if (f == ForegroundColor::White) {
		color = Color::White;
	}

	return color;
}