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
