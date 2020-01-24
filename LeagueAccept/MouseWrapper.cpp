#include "MouseWrapper.h"

MouseWrapper::MouseWrapper()
{
	GetClientRect(GetDesktopWindow(), &this->windowsize);
	this->buffer->type = INPUT_MOUSE;
	this->buffer->mi.dx = (0 * (0xFFFF / this->screenWidth()));
	this->buffer->mi.dy = (0 * (0xFFFF / this->screenHeight()));
	this->buffer->mi.mouseData = 0;
	this->buffer->mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	this->buffer->mi.time = 0;
	this->buffer->mi.dwExtraInfo = 0;
}

MouseWrapper::~MouseWrapper()
{
	DeleteObject(this->buffer);
}

void MouseWrapper::moveTo(int x,int y)
{
	this->buffer->mi.dx = (x * (0xFFFF / this->screenWidth));
	this->buffer->mi.dy = (y * (0xFFFF / this->screenHeight));
	this->buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);
	SendInput(1, this->buffer, sizeof(INPUT));
}

void MouseWrapper::moveTo(POINT p)
{
	return this->moveTo(p.x, p.y);
}

void MouseWrapper::click()
{
	this->buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
	SendInput(1, this->buffer, sizeof(INPUT));

	Sleep(10);

	this->buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
	SendInput(1, this->buffer, sizeof(INPUT));
}

LONG MouseWrapper::screenWidth() {
	return this->windowsize.top;
}

LONG MouseWrapper::screenHeight() {
	return this->windowsize.bottom;
}