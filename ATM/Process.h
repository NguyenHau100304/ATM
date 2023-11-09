#pragma once
#include "Handles.h"
#include "Display.h"
#include "Defines.h"
#include "GlobalVariable.h"
#include "TempMemory.h"
#include "IndependentFunction.h"
#include <conio.h>
#include <fstream>
#include <string>
#include <cstdlib>







void init() {
	SetConsoleTitleA("ATM");
	listAdmin.load("./data/Admin.txt");
	listAccount.load("./data/", "./data/TheTu.txt");
}


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




void adminMenu() {
	clrscr();
	setConsoleBackgroundColor(BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	clrscr();
	printArt(17, 0, "NameBank.txt", RED, YELLOW);


	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth,g_adminMenuHeight, LIGHT_BLUE);
	setTextBGColor(LIGHT_GREEN);
	//printArt(g_loginRectX + 8, g_loginRectY, "ATM.txt", RED, LIGHT_BLUE);
//	drawBorder(g_adminMenuX - 1, g_adminMenuY - 1, g_adminMenuWidth + 2, g_adminMenuHeight + 2, '*', WHITE, GRAY);

	_getch();

}

void userMenu();














void loginAdminMenu() {
	LOGIN:
	setConsoleBackgroundColor(BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	clrscr();
	printArt(17, 0, "NameBank.txt", RED, YELLOW);

	
	createBox(g_loginRectX, g_loginRectY, g_loginRectWidth, g_loginRectHeight, LIGHT_BLUE);
	printArt(g_loginRectX + 8, g_loginRectY, "ATM.txt", RED, LIGHT_BLUE);
	drawBorder(g_loginRectX - 1, g_loginRectY - 1, g_loginRectWidth + 2, g_loginRectHeight + 2, '*', WHITE, GRAY);

	setTextColor(RED);
	setTextBGColor(LIGHT_BLUE);
	gotoxy(g_loginRectX + 14, g_loginRectY + 7);
	cout << "ADMIN LOGIN";


	gotoxy(userInputX - 6, userInputY);
	setTextBGColor(BLACK);
	setTextColor(RED);
	cout << "User:                         ";
	

	gotoxy(passInputX - 5, passInputY);
	setTextBGColor(BLACK);
	setTextColor(RED);
	cout << "PIN:                          ";

	gotoxy(g_loginRectX + 5, g_loginRectY + 18);
	setTextBGColor(LIGHT_BLUE);
	setTextColor(WHITE);
	cout << "Ngan Hang TNHH 5TV Dip Do Bank";

	gotoxy(userInputX, userInputY);
/***************************************************************

						KEYBOARD EVENT

****************************************************************/
	
	char c = '\0';
	short wrongPw = 0;
	string inputId = "", inputPass = "";
	bool isInputId = true;
	while (true) {
		if (_kbhit()) {
			setTextBGColor(BLACK);
			setTextColor(WHITE);
			c = _getch();
			if (c == 0 || c == 224)
				c = _getch();

			if (c == '\r' || c == -32) {
				if (c == -32)
					c = _getch();
				if (isInputId) {
					gotoxy(passInputX + inputPass.length(), passInputY);
					isInputId = false;
				}
				else {
					if (c == '\r') {
						if (isCurrent(listAdmin.getAdministratorById(inputId), inputPass)) {
							adminMenu();
							goto LOGIN;
						}
						else {
							if (++wrongPw == 3) {
								clrscr();
								cout << "Da thu qua nhieu lan!. Yeu cau doi 30s de nhap lai!!!\n";
								_getch();
								exit(0);
							}
							else {
								Beep(600,200);
								gotoxy(passInputX - 2, passInputY + 1);
								setTextBGColor(LIGHT_BLUE);
								setTextColor(RED);
								cout << "Ban da nhap sai mat khau!";
								gotoxy(passInputX + inputPass.length(), passInputY);
								_getch();
							}
						}
						
					}
					else {
						gotoxy(userInputX + inputId.length(), userInputY);
						isInputId = true;
					}
				}
				goto CONTINUE;
			}
			else if (c == '\b') {
				if (isInputId && !inputId.empty()) {
					cout << "\b  \b";
					inputId.pop_back();
				}
				else if (!inputPass.empty()) {
					cout << "\b  \b";
					inputPass.pop_back();
				}
				goto CONTINUE;
			}
			else if(c != 32 && c != '\n' && c != '\t' && c != '\0') {
				if (isInputId) {
					cout << c;
					inputId = inputId + c;
				}
				else
				{
					cout << '*';
					inputPass = inputPass + c;
				}
			}
		CONTINUE:
			if (isInputId)
				gotoxy(userInputX + inputId.length(), userInputY);
			else
				gotoxy(passInputX + inputPass.length(), passInputY);
		}
	}




}

void loginUserMenu();


void loadListUsers();

