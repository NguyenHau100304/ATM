#pragma once
#include "Display.h"
#include <fstream>
#include <string>
#include <conio.h>
#include <cstdlib>


namespace drawing {

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


	void drawTransList() {
		setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
		setTextBGColor(WHITE);
		clrscr();
		setTextColor(BLACK);
		gotoxy(0, 0);
		drawBorder(0, 0, 82, 30, 1, BLACK, WHITE);
		gotoxy(0, 2);
		cout << char(204); // nga 3 trai
		gotoxy(81, 2);
		cout << char(185); // nga 3 phai
		gotoxy(1, 2);
		for (int i = 1; i <= 80; ++i)
			cout << char(205);
		gotoxy(32, 1);
		setTextColor(RED);
		cout << "LICH SU GIAO DICH";
	}

	void drawTableList() {
		setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
		setTextBGColor(WHITE);
		clrscr();
		setTextColor(RED);
		gotoxy(19, 0);
		cout << "         DANH SACH CAC TAI KHOAN";


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


	void drawNut(short x, short y, short color, short bgcolor) {
		setTextBGColor(bgcolor);
		setTextColor(color);
		gotoxy(x, y);
		cout << char(32) << char(220) << char(32);
		gotoxy(x, y + 1);
		cout << char(32) << char(223) << char(32);
	}

}