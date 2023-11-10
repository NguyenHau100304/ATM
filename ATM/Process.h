#pragma once
#include "Defines.h"
#include "GlobalVariable.h"
#include "TempMemory.h"
#include "Drawing.h"
#include <iomanip>
#include <conio.h>
#include <cstdlib>






void init() {
	resizeConsole(1100, 650);
	listAdmin.load("./data/Admin.txt");
	listAccount.load("./data/", "./data/TheTu.txt");
	setConsoleBackgroundColor(BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	clrscr();
	loadingScreen("Loading...", 5);
}

void waiting(int second) {
	setConsoleBackgroundColor(LIGHT_GREEN);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(RED);
	clrscr();
	cout << "Ban nhap sai qua nhieu lan. Yeu cau doi " << second << " giay de dang nhap lai.\n";
	cout << "Con lai:";
	++second;
	while (--second) {
		gotoxy(9, 1);
		cout << "           ";
		gotoxy(9, 1);
		cout << second << " giay";
		showCursor(false);
		Sleep(1000);
	}
	showCursor(true);
}

void printListUsers() {
	loadingScreen("Loading data...", 10);
	drawTableList();
	listAccount.display(0, 5, 0, 4);
	_getch();
	
}
void adminMenu() {
	loadingScreen("Loading profile...", 0);
ADMINMENU:
	setConsoleBackgroundColor(BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	clrscr();
	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth,g_adminMenuHeight, LIGHT_BLUE);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', YELLOW, RED);
	setTextBGColor(LIGHT_GREEN);

	printArt(17, 0, "MenuAdmin.txt", RED, YELLOW);
/***********************************************

				CREATE BUTTON

************************************************/

	POINT BUTTON[5] = {
		{g_adminMenuX + 6, g_adminMenuY + 2}, 	{g_adminMenuX + 40, g_adminMenuY + 2},
		{g_adminMenuX + 6, g_adminMenuY + 8},   {g_adminMenuX + 40, g_adminMenuY + 8},
		{g_adminMenuX + 23, g_adminMenuY + 15}
	};
	string nameButton[5]{
		"XEM DANH SACH TAI KHOAN",
		"THEM TAI KHOAN",
		"XOA TAI KHOAN",
		"MO KHOA TAI KHOAN",
		"DANG XUAT"
	};

	for (int i = 0; i < 5; ++i) {
		drawBorder(BUTTON[i].x, BUTTON[i].y, 28, 3, 1, YELLOW, LIGHT_BLUE);
		gotoxy(BUTTON[i].x + 1 + (13 - nameButton[i].length() / 2), BUTTON[i].y + 1);
		cout << nameButton[i];
	}
	
/***********************************************************************

							CHOOSE PROCESS

************************************************************************/

	short choose = 0;
	while (true) {
		drawBorder(BUTTON[choose].x, BUTTON[choose].y, 28, 3, 1, YELLOW, LIGHT_GREEN);
		showCursor(false);
		if (_kbhit) {
			Beep(600, 50);
			char c = _getch();
			if (c == 32 || c == -32) {
				if (c == -32)
					c = _getch();
				if(c == KEY_RIGHT)
					if(++choose == 5)
						choose = 0;
				if (c == KEY_LEFT)
					if (--choose == -1)
						choose = 4;

			}
			else if(c == '\r'){
				if (choose == 0) {
					printListUsers();
					goto ADMINMENU;
				}


			}
		}
		for (int i = 0; i < 5; ++i)
			drawBorder(BUTTON[i].x, BUTTON[i].y, 28, 3, 1, YELLOW, LIGHT_BLUE);
	}
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

	gotoxy(g_loginRectX + 8, g_loginRectY + 18);
	setTextBGColor(LIGHT_BLUE);
	setTextColor(WHITE);
	cout << "BANG HAI TAC MU ROM BANK";

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
								if (++wrongTime == 2) {
									clrscr();
									cout << "Ban da nhap sai qua nhieu lan!!!\n";
									_getch();
									exit(0);
								}
								clrscr();
								waiting(30);
								goto LOGIN;
							}
							else {
								Beep(600,200);
								gotoxy(passInputX - 2, passInputY + 1);
								setTextBGColor(LIGHT_BLUE);
								setTextColor(RED);
								cout << "Ban da nhap sai mat khau!";
								_getch();
								gotoxy(passInputX - 2, passInputY + 1);
								cout << "                         ";
								gotoxy(passInputX + inputPass.length(), passInputY);
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
				else if(isNumber(c) && inputPass.length() < 6)
				{
					Beep(600, 50);
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

