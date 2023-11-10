#pragma once
#include "Display.h"
#include <fstream>
#include <string>
void printArt(short x, short y, string path, int color, int bgcolor = LIGHT_GREEN) {
	gotoxy(x, y);
	ifstream fin(path);
	if (fin.good()) {
		while (!fin.eof()) {
			string s;
			std::getline(fin, s);
			setTextColor(color);
			setTextBGColor(bgcolor);
			cout << s;
			gotoxy(x, ++y);
		}
	}
	else
		throw runtime_error("Cannot open file");
	resetTextColor();

}


void drawBorder(short x, short y, short width, short height, char c = ' ', short color = WHITE, short bgcolor = BLACK) {
	setTextBGColor(bgcolor);
	setTextColor(color);
	if ((int)c != 1) {
		for (int i = 0; i < height; ++i) {
			gotoxy(x, y + i);
			if (i == 0 || i == height - 1)
				for (int j = 0; j < width; ++j)
					cout << c;
			else {
				cout << c;
				gotoxy(x + width - 1, y + i);
				cout << c;
			}
		}
	}
	else {
		for (int i = 0; i < height; ++i) {
			gotoxy(x, y + i);
			if (i == 0 || i == height - 1) {
				cout << ((i == 0) ? char(201) : char(200));
				for (int j = 1; j < width - 1; ++j)
					cout << char(205);
				cout << ((i == 0) ? char(187) : char(188));
			}
			else {
				cout << char(186);
				gotoxy(x + width - 1, y + i);
				cout << char(186);
			}
		}
	}

}

void drawLoading(short x, short y, short width, short color, short delay) {
	setTextBGColor(color);
	gotoxy(x, y);
	while (--width) {
		cout << ' ';
		Sleep(delay);
	}
}


void loadingScreen(string title, short delay) {
	setConsoleBackgroundColor(BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	clrscr();
	gotoxy(g_loadingX, g_loadingY - 1);
	cout << title;
	drawBorder(g_loadingX, g_loadingY, g_loadingWidth, g_loadingHeight, 1, 15, BLUE);
	drawLoading(g_loadingX + 1, g_loadingY + 1, g_loadingWidth - 1, RED, 1);
}

void printListPerPage(int page) {






}
void drawTableList() {
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	setTextBGColor(LIGHT_BLUE);
	clrscr();
	setTextColor(RED);
	gotoxy(19, 0);
	cout << "DANH SACH CAC TAI KHOAN";
	setTextColor(BLACK);
	gotoxy(0, 3);
	drawBorder(0, 3, 60, 27, 1, WHITE, LIGHT_BLUE);
	gotoxy(0, 5);
	cout << char(204); // nga 3 trai
	gotoxy(59, 5);
	cout << char(185); // nga 3 phai
	gotoxy(1, 5);
	for (int i = 1; i <= 58; ++i)
		cout << char(205);
	POINT TAGs[5] = {
		{1, 4},//STT
		{5, 4},//ID
		{20, 4},//NAME
		{45, 4},//MONEY
		{59, 4}
	};
	string NAMETAGs[4] = {
		"STT",
		"ID",
		"HO VA TEN",
		"SO DU"
	};
	for (int i = 0; i < 4; ++i) {
		if (i < 3) {
			gotoxy(TAGs[i + 1].x - 1, TAGs[i].y - 1);
			cout << char(203);
			for (int j = 0; j < 25; ++j) {
				gotoxy(TAGs[i + 1].x - 1, 4 + j);
				cout << char(186);
			}
			gotoxy(TAGs[i + 1].x - 1, TAGs[i].y + 1);
			cout << char(206);
			gotoxy(TAGs[i + 1].x - 1, 29);
			cout << char(202);
		}
		gotoxy(TAGs[i].x + ((TAGs[i + 1].x - TAGs[i].x) / 2) - NAMETAGs[i].length() / 2 - 1, TAGs[i].y);
		cout << NAMETAGs[i];
	}




}