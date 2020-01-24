#pragma once
#include <windows.h>
class MouseWrapper
{
private:
	INPUT buffer[1];
	RECT windowsize;

	LONG screenWidth();
	LONG screenHeight();

public:
	MouseWrapper();
	~MouseWrapper();
	void moveTo(int x,int y);
	void moveTo(POINT p);
	void click();
};

