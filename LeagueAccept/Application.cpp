#include <windows.h>
#include "LeagueAccept.h"
#include "resource.h"
#define IDR_START 12
#define IDR_STOP 13
#define IDR_EXIT 14
/*
#include <shellapi.h>
#pragma   comment(lib,   "shell32.lib")
*/
LPCTSTR szAppName = TEXT("League Accept");
LPCTSTR szWndName = TEXT("League Accept");
HMENU hmenu;//The menu handle
LeagueAccept leagueAccept = LeagueAccept();
HINSTANCE myHInstance;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	NOTIFYICONDATA nid;
	UINT WM_TASKBARCREATED;
	POINT pt;//To receive the coordinates of the mouse
	int xx;//The menu options for receiving the return value
	// Do not modify the TaskbarCreated system tray, which is a custom message
	WM_TASKBARCREATED = RegisterWindowMessage(TEXT("TaskbarCreated"));
	switch (message)
	{
	case WM_CREATE://Window creation time news
		nid.cbSize = sizeof(nid);
		nid.hWnd = hwnd;
		nid.uID = 0;
		nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		nid.uCallbackMessage = WM_USER;
		nid.hIcon = LoadIcon(myHInstance, MAKEINTRESOURCE(IDI_ICON1));
		lstrcpy(nid.szTip, szAppName);
		Shell_NotifyIcon(NIM_ADD, &nid);
		hmenu = CreatePopupMenu();//Create menu
		AppendMenu(hmenu, MF_STRING, IDR_START, "Start"); // add two options for the menu
		AppendMenu(hmenu, MF_STRING, IDR_EXIT, "Exit");
		break;
	case WM_USER://Continuous use of the procedure when the news
		if (lParam == WM_LBUTTONDOWN)
		{
			PostMessage(hwnd, WM_USER, NULL, WM_RBUTTONDOWN);
		}

		if (lParam == WM_LBUTTONDBLCLK)
		{
		}

		if (lParam == WM_RBUTTONDOWN)
		{
			GetCursorPos(&pt);//Take the mouse coordinates
			::SetForegroundWindow(hwnd);//To solve the menu and click the menu does not disappear problem
			
			xx = TrackPopupMenu(hmenu, TPM_RETURNCMD, pt.x, pt.y, NULL, hwnd, NULL);//Display menu and the option to get ID
			if (xx == IDR_START) {
				ModifyMenu(hmenu, IDR_START, MF_BYCOMMAND | MF_STRING, IDR_STOP, "Stop");
				leagueAccept.start();
			}
			if (xx == IDR_STOP) {
				ModifyMenu(hmenu, IDR_STOP, MF_BYCOMMAND | MF_STRING, IDR_START, "Start");
				leagueAccept.stop();
			}
			if (xx == IDR_EXIT) {
				leagueAccept.stop();
				exit(0);
			}
			
			if (xx == 0) PostMessage(hwnd, WM_LBUTTONDOWN, NULL, NULL);
			//MessageBox(hwnd, TEXT("The right key"), szAppName, MB_OK);
		}
		break;
	case WM_DESTROY://Window destroyed when news
		Shell_NotifyIcon(NIM_DELETE, &nid);
		PostQuitMessage(0);
		break;
	default:
		/*
		* When the Explorer.exe after the collapse prevention program in the system, in the system tray icon will disappear
		*
		* Principle: Explorer.exe after reload will rebuild the system tray. When the system tray to all established within the system
		* Register to receive TaskbarCreated messages of the top window sends a message, we only need to capture this information, and rebuild the system
		* System tray icon.
		*/
		if (message == WM_TASKBARCREATED)
			SendMessage(hwnd, WM_CREATE, wParam, lParam);
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR szCmdLine, int iCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	HWND handle = FindWindow(NULL, szWndName);
	myHInstance = hInstance;
	if (handle != NULL)
	{
		MessageBox(NULL, TEXT("Application is already running"), szAppName, MB_ICONERROR);
		return 0;
	}

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}

	// Use the WS_EX_TOOLWINDOW property to hide in the taskbar window program button here
	hwnd = CreateWindowEx(WS_EX_TOOLWINDOW,
		szAppName, szWndName,
		WS_POPUP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}