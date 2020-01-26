#pragma once
#include <windows.h>

class MouseWrapper
{
private:
	INPUT buffer[1];
	RECT windowsize;

public:
	MouseWrapper();
	~MouseWrapper();
	LONG screenWidth();
	LONG screenHeight();
	void moveTo(int x,int y);
	void moveTo(POINT p);
	void click();
};
