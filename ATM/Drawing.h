#pragma once
#include "Display.h"
#include <fstream>
#include <string>
#include <conio.h>
#include <cstdlib>
void printArt(short x, short y, string path, int color, int bgcolor = YELLOW) {
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


bool confirmProcess(string title) {
	createBox(g_adminMenuX, g_adminMenuY + 3, g_adminMenuWidth, 7, AQUA);
	gotoxy((g_adminMenuWidth / 2 + g_adminMenuX) - (title.length() / 2), g_adminMenuY + 4);
	setTextBGColor(AQUA);
	setTextColor(BLACK);
	cout << title;

	drawBorder(g_adminMenuX + 10, g_adminMenuY + 6, 24, 3, 1, WHITE, AQUA);
	gotoxy((g_adminMenuX + 10 + 24 / 2) - 1, g_adminMenuY + 7);
	cout << "NO";

	drawBorder(g_adminMenuX + 44, g_adminMenuY + 6, 24, 3, 1, WHITE, AQUA);
	gotoxy((g_adminMenuX + 44 + 24 / 2) - 2, g_adminMenuY + 7);
	cout << "YES";

	bool choose = false;
	drawBorder(g_adminMenuX + 10, g_adminMenuY + 6, 24, 3, 1, WHITE, YELLOW);
	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if (c == -32)
				c = _getch();

			if (c == 32 || c == KEY_LEFT || c == KEY_RIGHT) {
				choose = choose ? false : true;
				Beep(600, 50);
			}

			if (c == '\r') {
				Beep(800, 50);
				return choose;
			}
			if (choose) {
				drawBorder(g_adminMenuX + 10, g_adminMenuY + 6, 24, 3, 1, WHITE, AQUA);
				drawBorder(g_adminMenuX + 44, g_adminMenuY + 6, 24, 3, 1, WHITE, YELLOW);
			}
			else {
				drawBorder(g_adminMenuX + 44, g_adminMenuY + 6, 24, 3, 1, WHITE, AQUA);
				drawBorder(g_adminMenuX + 10, g_adminMenuY + 6, 24, 3, 1, WHITE, YELLOW);
			}
		}
		showCursor(false);
	}
	return true;
}



void loadingScreen(string title, short delay) {
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	gotoxy(g_loadingX, g_loadingY - 1);
	cout << title;
	drawBorder(g_loadingX, g_loadingY, g_loadingWidth, g_loadingHeight, 1, 15, BLUE);
	drawLoading(g_loadingX + 1, g_loadingY + 1, g_loadingWidth - 1, RED, 1);
}

void printListPerPage(int page, int sort, ListAccount& list) {
	POINT TAGs[3] = {
		{20, 3},
		{45, 3},
		{69, 3}
	};
	string NAMETAGs[2] = {
		"HO VA TEN",
		"SO DU"
	};
	for (int i = 0; i < 2; ++i) {
		setTextBGColor(WHITE);
		setTextColor(BLACK);
		gotoxy(TAGs[i].x + ((TAGs[i + 1].x - TAGs[i].x) / 2) - NAMETAGs[i].length() / 2 - 1, TAGs[i].y);
		cout << NAMETAGs[i];
	}
	if(sort > 0){
		setTextBGColor(LIGHT_BLUE);
		setTextColor(BLACK);
		gotoxy(TAGs[sort - 1].x + ((TAGs[sort].x - TAGs[sort - 1].x) / 2) - NAMETAGs[sort - 1].length() / 2 - 1, TAGs[sort - 1].y);
		cout << NAMETAGs[sort - 1];
	}
	else if (sort < 0) {
		sort = abs(sort);
		setTextBGColor(LIGHT_RED);
		setTextColor(BLACK);
		gotoxy(TAGs[sort - 1].x + ((TAGs[sort].x - TAGs[sort - 1].x) / 2) - NAMETAGs[sort - 1].length() / 2 - 1, TAGs[sort - 1].y);
		cout << NAMETAGs[sort - 1];
	}
	setTextBGColor(WHITE);
	short x = 0, y = 5;
	for (int i = 0; i < 24; ++i) {
		gotoxy(x + 1, y);
		cout << "   ";
		gotoxy(x + 5, y);
		cout << setFill(14);
		gotoxy(x + 20, y);
		cout << setFill(24);
		gotoxy(x + 45, y);
		cout << setFill(23);
		gotoxy(x + 69, y);
		cout << setFill(9);
		++y;
	}
	list.display(24 * (page - 1), 24 * page - 1, 0, 5, listIdBlocked);
}



void drawTableList() {
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	setTextBGColor(WHITE);
	clrscr();
	setTextColor(RED);
	gotoxy(19, 0);
	cout << "  DANH SACH CAC TAI KHOAN";
	gotoxy(4, 1);
	setTextColor(BLUE);
	cout << "RIGHT/LEFT turn page - PAGE UP/PAGE DOWN change sort - ESC quit";


	setTextColor(BLACK);
	gotoxy(0, 2);
	drawBorder(0, 2, 82, 28, 1, BLACK, WHITE);
	gotoxy(0, 4);
	cout << char(204); // nga 3 trai
	gotoxy(81, 4);
	cout << char(185); // nga 3 phai
	gotoxy(1, 4);
	for (int i = 1; i <= 80; ++i)
		cout << char(205);
	POINT TAGs[6] = {
		{1, 3},//STT
		{5, 3},//ID
		{20, 3},//NAME
		{45, 3},//MONEY
		{69, 3},
		{81, 3}
	};
	string NAMETAGs[5] = {
		"STT",
		"ID",
		"HO VA TEN",
		"SO DU",
		"TINH TRANG"
	};
	for (int i = 0; i < 5; ++i) {
		if (i < 4) {
			gotoxy(TAGs[i + 1].x - 1, TAGs[i].y - 1);
			cout << char(203);
			for (int j = 0; j < 26; ++j) {
				gotoxy(TAGs[i + 1].x - 1, 3 + j);
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