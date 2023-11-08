#pragma once
#include <iostream>
#include<Windows.h>
#include "Defines.h"



using namespace std;

template <typename DataType>
void print(DataType output, int color = 7);



void resizeConsole(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void setConsoleWindowSize(int width, int height) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD newSize;
	newSize.X = width;
	newSize.Y = height;
	SetConsoleScreenBufferSize(hConsole, newSize);
	SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}


int getWindowMouseX() {
	POINT p;
	GetCursorPos(&p);
	return p.x;
}

int getWindowMouseY() {
	POINT p;
	GetCursorPos(&p);
	return p.y;
}

int getConsoleWindowPositionX() {
	HWND consoleWindow = GetConsoleWindow();
	RECT rect;
	GetWindowRect(consoleWindow, &rect);
	return rect.left;
}

int getConsoleWindowPositionY() {
	HWND consoleWindow = GetConsoleWindow();
	RECT rect;
	GetWindowRect(consoleWindow, &rect);
	return rect.top;
}


int getCursorX() {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.X + 1;

}

int getCursorY() {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.Y + 1;
}

void setTextBGColor(int color) {
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void gotoxy(int x, int y) {
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void showCursor(bool cursorVisibility) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, cursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void setTextColor(int color) {
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}


void setConsoleBackgroundColor(int colorCode) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorCode);
}

void createBox(int x1, int y1, int x2, int y2, int color) {
	setTextBGColor(color);

	for (int i = y1; i <= y2; ++i) {
		gotoxy(x1, i);
		for (int j = x1; j <= x2; ++j)
			cout << ' ';
	}


	setTextBGColor(BLACK);
}

char getKeyPressed()
{
	HANDLE hStdin;
	DWORD cNumRead;
	INPUT_RECORD irInBuf[128];
	int counter = 0;

	hStdin = GetStdHandle(STD_INPUT_HANDLE);

	if (hStdin == INVALID_HANDLE_VALUE)
	{
		std::cerr << "GetStdHandle returned invalid handle" << std::endl;
		return '\0';
	}

	while (counter++ <= 128)
	{
		if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead))
		{
			std::cerr << "ReadConsoleInput failed" << std::endl;
			return '\0';
		}

		for (unsigned int i = 0; i < cNumRead; i++)
		{
			if (irInBuf[i].EventType == KEY_EVENT)  // Kiểm tra sự kiện từ bàn phím
			{
				KEY_EVENT_RECORD ker = irInBuf[i].Event.KeyEvent;

				// Kiểm tra xem phím có được nhấn hay không (không phải là sự kiện phím được thả ra)
				if (ker.bKeyDown)
				{
					return ker.uChar.AsciiChar;  // Trả về kí tự tương ứng với phím được nhấn
				}
			}
		}
	}

	return '\0';  // Trả về '\0' nếu không có phím nào được nhấn
}




void clrscr() {
	system("cls");
}

void resetTextColor() {
	setTextColor(7);
}

void resetTextBGColor() {
	setTextBGColor(BLACK);
}



template <typename DataType>
void print(DataType output, int color) {
	setTextColor(color);
	cout << output;
	resetTextColor();
}