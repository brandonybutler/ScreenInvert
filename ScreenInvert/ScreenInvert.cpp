#include "pch.h"

#define WINVER 0x0600
#define _WIN32_WINNT 0x0600

#include <Windows.h>
#include <windowsx.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

using namespace System;

int main(array<String ^> ^args)
{
	// Hide the console window
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	// Credit goes to user Castorix (https://stackoverflow.com/users/4452971/castorix) for creating the below code
	// on my Stack Overflow post (https://stackoverflow.com/questions/56626942/how-to-invert-the-entire-screen-colours-using-the-windows-magnification-api).
	HDC hDc = GetDC(NULL);
	RECT rcClient;
	GetClientRect(GetDesktopWindow(), &rcClient);

	int nWidth = rcClient.right - rcClient.left;
	int nHeight = rcClient.bottom - rcClient.top;

	HDC hMemDC = CreateCompatibleDC(hDc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDc, nWidth, nHeight);
	HBITMAP hBmOld = (HBITMAP) SelectObject(hMemDC, hBitmap);

	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hDc, 0, 0, SRCCOPY);
	BitBlt(hDc, 0, 0, nWidth, nHeight, hMemDC, 0, 0, DSTINVERT);

	SelectBitmap(hMemDC, hBmOld);
	DeleteDC(hMemDC);
	DeleteObject(hBitmap);
	ReleaseDC(NULL, hDc);

	return 0;
}
