#pragma once
#include <windows.h>
#include <shellapi.h>
#include <string>
#undef UNICODE
#define UNICODE
#define WM_SYSICON          (WM_USER + 1)
#define ICO1 101
#define ID_TRAY_APP_ICON    1001
#define ID_TRAY_EXIT        1002

class SystemTray
{
private:
	NOTIFYICONDATAW Tray;
	HWND hWnd;
	UINT WM_TASKBAR;
	HMENU Hmenu;
public:
	SystemTray();
	~SystemTray();
	void setToolTip(const std::wstring text);
	void show();
	void restore();
	void minimize();
	LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
};

