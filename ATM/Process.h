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
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	loadingScreen("Loading...", 5);
}

void waiting(int second) {
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	setTextBGColor(YELLOW);
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
	int maxPage = listAccount.getSize() / 24;
	maxPage += (listAccount.getSize() % 24 ? 1 : 0);
	listAccount.load("./data/", "./data/TheTu.txt");
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
				listAccount.load("./data/", "./data/TheTu.txt");
				break;
			case 2:
				listAccount.sortIf(compareUserbyName);
				break;
			case 3:
				listAccount.sortIf(compareUserbyMoney);
				break;
			default:
				break;
			}
			gotoxy(83, 28);
			setTextColor(BLACK);
			cout << "Trang " << page << '/' << maxPage;
			printListPerPage(page, chooseSort);
			showCursor(false);
		}
	}
	_getch();
	
}


void addUserToList() {
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, LIGHT_GREEN);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', YELLOW, RED);
	setTextBGColor(YELLOW);

	printArt(17, 0, "MenuAdmin.txt", RED, YELLOW);

	
	drawBorder(g_initMenuX + 25, g_initMenuY + 1, 28, 3, 1, RED, LIGHT_GREEN);
	gotoxy(g_adminMenuX + 27, g_adminMenuY + 2);
	setTextColor(RED);
	setTextBGColor(LIGHT_GREEN);
	cout << "NHAP THONG TIN TAI KHOAN";


	setTextBGColor(LIGHT_GREEN);
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
		"SO DU: ",
		"TIEN TE: "
	};
	for (int i = 0; i < 4; ++i) {
		setTextBGColor(LIGHT_GREEN);
		gotoxy(hoverText[i].x, hoverText[i].y);
		cout << setw(12) << right << titleHoverText[i];
		setTextBGColor(GRAY);
		gotoxy(hoverText[i].x + 12, hoverText[i].y);
		cout << setfill(30);
		hoverText[i].x += 12;
	}

	gotoxy(hoverText[0].x, hoverText[0].y + 1);
	setTextColor(RED);
	setTextBGColor(LIGHT_GREEN);
	cout << "F3 generate new ID";

	gotoxy(hoverText[3].x + 16, hoverText[3].y + 2);
	setTextBGColor(YELLOW);
	setTextColor(RED);
	cout << "TAO TAI KHOAN";
	
	


	//----------------------------------------------------------------
	setTextBGColor(GRAY);
	setTextColor(BLACK);
	gotoxy(hoverText[0].x, hoverText[0].y);
	showCursor(true);
	char c = '\0';
	string input[5] = {
		 "", "", "", ""
	};

	do {
		input[0] = getRandomId();
	} while (listAccount.isHasUser(input[0]));
	gotoxy(hoverText[0].x, hoverText[0].y);
	cout << input[0];

	int curr = 1;
	while (true) {
		setCursorColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		// MOVE CURSOR
		if (curr != 4) {
			gotoxy(hoverText[curr].x + input[curr].length(), hoverText[curr].y);
			showCursor(true);
		}
		else {
			gotoxy(hoverText[3].x + 16, hoverText[3].y + 2);
			setTextBGColor(GREEN);
			setTextColor(RED);
			cout << "TAO TAI KHOAN";
			showCursor(false);
		}
		if (_kbhit()) {
			setTextBGColor(BLACK);
			setTextColor(GRAY);
			c = _getch();

			// ESC
			if (c == ESC)
				return;
			// KY TU KHOA
			if (c == 0 || c == 224)
				c = _getch();

			//F3
			if (c == KEY_F3) {
				do {
					input[0] = getRandomId();
				} while (listAccount.isHasUser(input[0]));
				gotoxy(hoverText[0].x, hoverText[0].y);
				setTextBGColor(GRAY);
				setTextColor(BLACK);
				cout << input[0];
				continue;
			}

			// CHUYEN DONG
			if (c == '\r' || c == -32) {
				if (c == -32)
					c = _getch();
				if (c == KEY_UP)
					if (--curr == 0)
						curr = 4;
				if (c == KEY_DOWN)
					if (++curr == 5)
						curr = 1;
				if(c == '\r')
					if (++curr == 4) {
						if (!input[0].empty() && !input[1].empty() && !input[2].empty()) {
							if (input[3] != "USD" && input[3] != "VND")
								input[3] = "VND";
							User newUser(input[0], "123456", Name(input[1]), Money(stoi(input[2]), input[3]));
							listAccount.append(newUser);
							listAccount.saveCard("./data/TheTu.txt");
							listAccount.save("./data/");
							Beep(1000, 200);
							
							return;
						}
					}
				if (curr != 4) {
					gotoxy(hoverText[3].x + 16, hoverText[3].y + 2);
					setTextBGColor(YELLOW);
					setTextColor(RED);
					cout << "TAO TAI KHOAN";
				}
			}//BACKSPACE
			else if (c == '\b') {
				setTextBGColor(GRAY);
				setTextColor(GRAY);
				if (input[curr].length() > 0) {
					cout << "\b  \b";
					input[curr].pop_back();
				}

			}
			// NHAP KY TU
			else {
				if (curr != 4) {
					setTextBGColor(GRAY);
					setTextColor(BLACK);
					if(curr == 1){
						cout << char(toupper(c));
						input[curr].push_back(toupper(c));
					}
					else if(curr == 2 && isNumber(c)) {
						cout << c;
						input[curr].push_back(c);
					}
					else if(curr == 3) {
						cout << char(toupper(c));
						input[curr].push_back(char(toupper(c)));
					}
				}
			}
			
		}
	}




	_getch();
}


void adminMenu() {
	loadingScreen("Loading profile...", 0);
__INIT__:
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth,g_adminMenuHeight, LIGHT_GREEN);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', WHITE, RED);
	setTextBGColor(YELLOW);

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
		drawBorder(BUTTON[i].x, BUTTON[i].y, 28, 3, 1, BLACK, LIGHT_GREEN);
		gotoxy(BUTTON[i].x + 1 + (13 - nameButton[i].length() / 2), BUTTON[i].y + 1);
		cout << nameButton[i];
	}
	
/***********************************************************************

							CHOOSE PROCESS

************************************************************************/

	short choose = 0;
	while (true) {
		drawBorder(BUTTON[choose].x, BUTTON[choose].y, 28, 3, 1, BLACK, YELLOW);
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
				switch (choose)
				{
				case 0: {
					printListUsers();
					goto __INIT__;
					break;
				}
				case 1: {
					addUserToList();
					goto __INIT__;
					break;
				}
				case 2: {

					goto __INIT__;
					break;
				}
				case 3: {

					goto __INIT__;
				}
				case 4: {
					return;
				}
				default:
					break;
				}
			}
		}
		for (int i = 0; i < 5; ++i)
			drawBorder(BUTTON[i].x, BUTTON[i].y, 28, 3, 1, BLACK, LIGHT_GREEN);
	}
	_getch();

}






void userMenu();














void loginAdminMenu() {
LOGIN:
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	printArt(17, 0, "NameBank.txt", RED, YELLOW);


	createBox(g_loginRectX, g_loginRectY, g_loginRectWidth, g_loginRectHeight, LIGHT_GREEN);
	printArt(g_loginRectX + 8, g_loginRectY, "ATM.txt", RED, LIGHT_GREEN);
	drawBorder(g_loginRectX - 1, g_loginRectY - 1, g_loginRectWidth + 2, g_loginRectHeight + 2, '*', WHITE, RED);

	setTextColor(RED);
	setTextBGColor(LIGHT_GREEN);
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
	setTextBGColor(LIGHT_GREEN);
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
								setTextBGColor(LIGHT_GREEN);
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
				if (isInputId && inputId.length() < 15) {
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
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	createBox(g_initMenuX, g_initMenuY, g_initMenuWidth, g_initMenuHeight, LIGHT_GREEN);
	drawBorder(g_initMenuX, g_initMenuY, g_initMenuWidth, g_initMenuHeight, '*', YELLOW, BLUE);
	setTextBGColor(YELLOW);
	printArt(17, 0, "NameBank.txt", RED, YELLOW);

	drawBorder(g_initMenuX + 25, g_initMenuY + 2, 28, 3, '*', RED, LIGHT_GREEN);

	gotoxy(g_initMenuX + 27, g_initMenuY + 3);
	setTextColor(RED);
	setTextBGColor(LIGHT_GREEN);
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
		drawBorder(BUTTON[i].x, BUTTON[i].y, 28, 3, 1, BLACK, LIGHT_GREEN);
		gotoxy(BUTTON[i].x + 1 + (13 - nameButton[i].length() / 2), BUTTON[i].y + 1);
		cout << nameButton[i];
	}


	short choose = 0;
	while (true) {
		drawBorder(BUTTON[choose].x, BUTTON[choose].y, 28, 3, 1, BLACK, YELLOW);
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
			drawBorder(BUTTON[i].x, BUTTON[i].y, 28, 3, 1, BLACK, LIGHT_GREEN);
	}
	_getch();



}
