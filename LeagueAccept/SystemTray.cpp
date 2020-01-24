#include "SystemTray.h"

SystemTray::SystemTray()
{
	//hWnd init
	this->hWnd = FindWindow("ConsoleWindowClass", NULL);

	this->WM_TASKBAR = 0;

	//Tray init
	this->Tray.cbSize = sizeof(Tray);
	this->Tray.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	this->Tray.hWnd = hWnd;

	this->Tray.uCallbackMessage = WM_LBUTTONDOWN;
	this->Tray.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	this->Tray.uID = 1;
	this->Tray.uCallbackMessage = WM_SYSICON;
	this->Hmenu = CreatePopupMenu();
	InsertMenuW(this->Hmenu, 0xFFFFFFFF, MF_BYPOSITION | MF_STRING, this->WM_TASKBAR, L"About");
	SetForegroundWindow(this->hWnd);
	POINT curPoint;
	GetCursorPos(&curPoint);
	TrackPopupMenu(this->Hmenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_BOTTOMALIGN, curPoint.x, curPoint.y, 0, hWnd, NULL);
	ShowWindow(hWnd, 0);
}

SystemTray::~SystemTray()
{
	Shell_NotifyIconW(NIM_DELETE, &this->Tray);
}

void SystemTray::setToolTip(const std::wstring text)
{
	wcscpy_s(this->Tray.szTip, text.c_str());
}

void SystemTray::show()
{
	Shell_NotifyIconW(NIM_ADD, &Tray);
}

void SystemTray::minimize()
{
	ShowWindow(this->hWnd, SW_HIDE);
}


void SystemTray::restore()
{
	ShowWindow(this->hWnd, SW_SHOW);
}

LRESULT CALLBACK SystemTray::WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if (message == this->WM_TASKBAR && !IsWindowVisible(this->hWnd))
	{
		minimize();
		return 0;
	}

	switch (message)                  /* handle the messages */
	{
	case WM_ACTIVATE:
		Shell_NotifyIconW(NIM_ADD, &this->Tray);
		break;

	case WM_CREATE:
		this->minimize();
		break;

	case WM_SYSCOMMAND:
		/*In WM_SYSCOMMAND messages, the four low-order bits of the wParam parameter
		are used internally by the system. To obtain the correct result when testing the value of wParam,
		an application must combine the value 0xFFF0 with the wParam value by using the bitwise AND operator.*/
		switch (wParam & 0xFFF0)
		{
		case SC_MINIMIZE:
		case SC_CLOSE:
			minimize();
			return 0;
			break;
		}
		break;


		// Our user defined WM_SYSICON message.
	case WM_SYSICON:
	{

		switch (wParam)
		{
		case ID_TRAY_APP_ICON:
			SetForegroundWindow(this->hWnd);
			break;
		}

		if (lParam == WM_LBUTTONUP)
		{
			restore();
		}
		else if (lParam == WM_RBUTTONDOWN)
		{
			// Get current mouse position.
			POINT curPoint;
			GetCursorPos(&curPoint);
			SetForegroundWindow(this->hWnd);

			// TrackPopupMenu blocks the app until TrackPopupMenu returns

			UINT clicked = TrackPopupMenu(this->Hmenu, TPM_RETURNCMD | TPM_NONOTIFY, curPoint.x, curPoint.y, 0, hwnd, NULL);



			SendMessage(hwnd, WM_NULL, 0, 0); // send benign message to window to make sure the menu goes away.
			if (clicked == ID_TRAY_EXIT)
			{
				// quit the application.
				Shell_NotifyIconW(NIM_DELETE, &this->Tray);
				PostQuitMessage(0);
			}
		}
	}
	break;

	// intercept the hittest message..
	case WM_NCHITTEST:
	{
		UINT uHitTest = DefWindowProc(hwnd, WM_NCHITTEST, wParam, lParam);
		if (uHitTest == HTCLIENT)
			return HTCAPTION;
		else
			return uHitTest;
	}

	case WM_CLOSE:

		minimize();
		return 0;
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;

	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
