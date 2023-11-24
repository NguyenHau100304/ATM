#pragma once
#include <iostream>
#include <Windows.h>
#include "Defines.h"



using std::cout;





void resizeConsole(short width, short height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void setCursorColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setConsoleWindowSize(short width, short height) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD newSize;
	newSize.X = width;
	newSize.Y = height;
	SetConsoleScreenBufferSize(hConsole, newSize);
	SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}


short getWindowMouseX() {
	POINT p;
	GetCursorPos(&p);
	return p.x;
}

short getWindowMouseY() {
	POINT p;
	GetCursorPos(&p);
	return p.y;
}

short getConsoleWindowPositionX() {
	HWND consoleWindow = GetConsoleWindow();
	RECT rect;
	GetWindowRect(consoleWindow, &rect);
	return rect.left;
}

short getConsoleWindowPositionY() {
	HWND consoleWindow = GetConsoleWindow();
	RECT rect;
	GetWindowRect(consoleWindow, &rect);
	return rect.top;
}


short getCursorX() {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.X + 1;

}

short getCursorY() {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.Y + 1;
}

void setTextBGColor(short color) {
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

void gotoxy(short x, short y) {
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

void setTextColor(short color) {
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


void setConsoleBackgroundColor(short colorCode) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorCode);
}

void createBox(short x1, short y1, int w, short h, short color) {
	setTextBGColor(color);
	gotoxy(x1, y1);
	for (short i = 0; i < h; ++i) {
		gotoxy(x1, y1 + i);
		for (int j = 0; j < w; ++j) {
			cout << ' ';
		}
			
	}
	setTextBGColor(BLACK);
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

