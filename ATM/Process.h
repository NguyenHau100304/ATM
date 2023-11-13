#pragma once
#include "Defines.h"
#include "GlobalVariable.h"
#include "TempMemory.cpp"
#include "IndependentFunction.h"
#include "Drawing.h"
#include <conio.h>
#include <cstdlib>






void init() {
	resizeConsole(1100, 650);
	listAdmin.load("./data/Admin.txt");
	listAccount.load("./data/", "./data/TheTu.txt");
	listIdBlocked.load("./data/AccountBlocked/ALL.txt");
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

	int page = 1, chooseSort = 1;
	int maxPage = (listAccount.getSize() / 24) + 1;

	listAccount.sortIf(compareUserbyName);
	printListPerPage(1, 1);
	gotoxy(83, 28);
	cout << "Trang " << page << '/' << maxPage;
	showCursor(false);
	
	while (true) {
		if (_kbhit()) {
			char c = _getch();

			if (c == ESC)
				return;

			if (c == -32)
				c = _getch();

			if (c == PAGE_DOWN || c == PAGE_UP)
				if (++chooseSort == 4)
					chooseSort = 1;


			if (c == KEY_RIGHT)
				if (++page == maxPage + 1)
					page = 1;
			if (c == KEY_LEFT)
				if (--page == 0)
					page = maxPage;

			switch (chooseSort)
			{
			case 1:
				listAccount.sortIf(compareUserbyName);
				break;
			case 2:
				listAccount.sortIf(compareUserbyId);
				break;
			case 3:
				listAccount.sortIf(compareUserbyMoney);
				break;
			default:
				break;
			}
			gotoxy(83, 28);
			cout << "Trang " << page << '/' << maxPage;
			printListPerPage(page, chooseSort);
			showCursor(false);
		}
	}
	_getch();
	
}


void addUserToList() {
	setConsoleBackgroundColor(BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	clrscr();
	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, LIGHT_BLUE);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', YELLOW, RED);
	setTextBGColor(LIGHT_GREEN);

	printArt(17, 0, "MenuAdmin.txt", RED, YELLOW);

	
	drawBorder(g_initMenuX + 25, g_initMenuY + 1, 28, 3, 1, RED, LIGHT_BLUE);
	gotoxy(g_adminMenuX + 27, g_adminMenuY + 2);
	setTextColor(RED);
	setTextBGColor(LIGHT_BLUE);
	cout << "NHAP THONG TIN TAI KHOAN";


	setTextBGColor(LIGHT_BLUE);
	setTextColor(BLACK);

	POINT hoverText[] = {
		{g_adminMenuX + 12, g_adminMenuY + 5},
		{g_adminMenuX + 12, g_adminMenuY + 8},
		{g_adminMenuX + 12, g_adminMenuY + 11},
		{g_adminMenuX + 12, g_adminMenuY + 14}
	};
	string titleHoverText[4] = {
		"ID: ",
		"HO VA TEN: ",
		"PASSWORD: ",
		"SO DU: "
	};
	for (int i = 0; i < 4; ++i) {
		setTextBGColor(LIGHT_BLUE);
		gotoxy(hoverText[i].x, hoverText[i].y);
		cout << setw(12) << right << titleHoverText[i];
		setTextBGColor(WHITE);
		gotoxy(hoverText[i].x + 12, hoverText[i].y);
		cout << setfill(30);

		hoverText[i].x += 12;
	}

	gotoxy(hoverText[3].x + 18, hoverText[3].y + 2);
	setTextBGColor(YELLOW);
	setTextColor(RED);
	cout << "TAO TAI KHOAN";
	
	//----------------------------------------------------------------
	setTextBGColor(WHITE);
	setTextColor(BLACK);
	gotoxy(hoverText[0].x, hoverText[0].y);
	showCursor(true);
	char c = '\0';
	string input[4] = {
		"", "", "", ""
	};
	int curr = 0;
	while (true) {
		if (_kbhit()) {
			setTextBGColor(BLACK);
			setTextColor(WHITE);
			c = _getch();

			// ESC
			if (c == ESC)
				return;
			// KY TU KHOA
			if (c == 0 || c == 224)
				c = _getch();
			// CHUYEN DONG
			if (c == '\r' || c == -32) {
				if (c == -32)
					c = _getch();
				if (c == KEY_UP)
					if (--curr == -1)
						curr = 4;
				if (c == KEY_DOWN || c == '\r')
					if (++curr == 5)
						curr = 0;
				
				// MOVE CURSOR
				if (curr != 4) {
					gotoxy(hoverText[3].x + 18, hoverText[3].y + 2);
					setTextBGColor(YELLOW);
					setTextColor(RED);
					cout << "TAO TAI KHOAN";
					gotoxy(hoverText[curr].x + input[curr].length(), hoverText[curr].y);
				}
				else {
					gotoxy(hoverText[3].x + 18, hoverText[3].y + 2);
					setTextBGColor(GREEN);
					setTextColor(RED);
					cout << "TAO TAI KHOAN";
				}
			}// NHAP KY TU
			else {







			}
		}
	}




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
			char c = _getch();
			if (c == 32 || c == -32) {
				Beep(600, 50);
				if (c == -32)
					c = _getch();
				if(c == KEY_RIGHT || c == 32)
					if(++choose == 5)
						choose = 0;
				if (c == KEY_LEFT)
					if (--choose == -1)
						choose = 4;

			}
			else if(c == '\r'){
				Beep(800, 50);
				if (choose == 0) {
					printListUsers();
					goto ADMINMENU;
				}
				else if (choose == 1) {
					addUserToList();
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
	showCursor(true);
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

			if (c == ESC)
				return;

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
							Beep(800, 50);
							adminMenu();
							goto LOGIN;
						}
						else if(!inputId.empty() && !inputPass.empty()) {
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
								Beep(1000,200);
								gotoxy(passInputX - 2, passInputY + 1);
								setTextBGColor(LIGHT_BLUE);
								setTextColor(RED);
								cout << "Ban da nhap sai mat khau!";
								showCursor(false);
								_getch();
								showCursor(true);
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
				else if (!isInputId && !inputPass.empty()) {
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

void loginUserMenu() {

}


void loadListUsers();




void runProcess() {
__INIT__:
	setConsoleBackgroundColor(BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	clrscr();
	createBox(g_initMenuX, g_initMenuY, g_initMenuWidth, g_initMenuHeight, LIGHT_BLUE);
	drawBorder(g_initMenuX, g_initMenuY, g_initMenuWidth, g_initMenuHeight, '*', YELLOW, GRAY);
	setTextBGColor(LIGHT_GREEN);
	printArt(17, 0, "NameBank.txt", RED, YELLOW);

	drawBorder(g_initMenuX + 25, g_initMenuY + 2, 28, 3, '*', YELLOW, LIGHT_BLUE);

	gotoxy(g_initMenuX + 27, g_initMenuY + 3);
	setTextColor(RED);
	setTextBGColor(LIGHT_BLUE);
	cout << "CHON HINH THUC DANG NHAP";
	POINT BUTTON[3] = {
		{g_initMenuX + 6, g_initMenuY + 6},
		{g_initMenuX + 40, g_initMenuY + 6},
		{g_initMenuX + 23, g_initMenuY + 10}
	};
	string nameButton[3]{
		"QUAN TRI VIEN",
		"NGUOI DUNG",
		"THOAT"
	};
	for (int i = 0; i < 3; ++i) {
		drawBorder(BUTTON[i].x, BUTTON[i].y, 28, 3, 1, YELLOW, LIGHT_BLUE);
		gotoxy(BUTTON[i].x + 1 + (13 - nameButton[i].length() / 2), BUTTON[i].y + 1);
		cout << nameButton[i];
	}


	short choose = 0;
	while (true) {
		drawBorder(BUTTON[choose].x, BUTTON[choose].y, 28, 3, 1, YELLOW, LIGHT_GREEN);
		showCursor(false);
		if (_kbhit) {
			char c = _getch();
			if (c == 32 || c == -32) {
				Beep(600, 50);
				if (c == -32)
					c = _getch();
				if (c == KEY_RIGHT || c == 32)
					if (++choose == 3)
						choose = 0;
				if (c == KEY_LEFT)
					if (--choose == -1)
						choose = 2;

			}
			else if (c == '\r') {
				Beep(800, 50);
				if (choose == 0) {
					loginAdminMenu();
					goto __INIT__;
				}
				else if (choose == 1) {
					loginUserMenu();
					goto __INIT__;
				}
				else {
					resetTextBGColor();
					resetTextColor();
					clrscr();
					return;
				}
			}
		}
		for (int i = 0; i < 3; ++i)
			drawBorder(BUTTON[i].x, BUTTON[i].y, 28, 3, 1, YELLOW, LIGHT_BLUE);
	}
	_getch();



}
