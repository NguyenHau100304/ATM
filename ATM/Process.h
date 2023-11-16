#pragma once
#include "Defines.h"
#include "GlobalVariable.h"
#include "TempMemory.cpp"
#include "IndependentFunction.h"
#include "Drawing.h"







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

	int page = 1, chooseSort = 0;
	int maxPage = listAccount.getSize() / 24;
	maxPage += (listAccount.getSize() % 24 ? 1 : 0);
	ListAccount list(listAccount);
	ListAccount filerList;
	string input = "";
	printListPerPage(1, 0, list);

	gotoxy(83, 3);
	cout << "F3 - search";


	setTextColor(LIGHT_RED);
	gotoxy(83, 8);
	cout << "HOT KEY:";

	setTextColor(AQUA);
	gotoxy(83, 10);
	cout << "ARROW LEFT - turn page left";
	gotoxy(83, 12);
	cout << "ARROW RIGHT - turn page right";
	gotoxy(83, 14);
	cout << "PAGE UP - change sort greater";
	gotoxy(83, 16);
	cout << "PAGE DOWN - change sort less";
	gotoxy(83, 18);
	cout << "ESC - quit";

	gotoxy(83, 28);
	cout << "Trang " << page << '/' << maxPage;

	showCursor(false);
	bool isSearch = false, isCurrentSearch = false;
	while (true) {
		if (_kbhit) {
			char c = _getch();
			if (c == 0)
				c = _getch();
			if (c == PAGE_DOWN || c == PAGE_UP) {
				if (c == PAGE_UP)
				{
					setTextColor(AQUA);
					setTextBGColor(YELLOW);
					gotoxy(83, 14);
					cout << "PAGE UP - change sort greater";
					Beep(600, 50);
					Sleep(50);
					setTextBGColor(WHITE);
					gotoxy(83, 14);
					cout << "PAGE UP - change sort greater";
					if (chooseSort < 0)
						chooseSort = 0;
					else if (++chooseSort == 3)
						chooseSort = 0;
				}
				else {
					setTextColor(AQUA);
					setTextBGColor(YELLOW);
					gotoxy(83, 16);
					cout << "PAGE DOWN - change sort less";
					Beep(600, 50);
					Sleep(50);
					setTextBGColor(WHITE);
					gotoxy(83, 16);
					cout << "PAGE DOWN - change sort less";
					if (chooseSort > 0)
						chooseSort = 0;
					else if (--chooseSort == -3) {
						chooseSort = 0;
					}
				}
				goto __FORMATLIST__;
			}
			if (c == -32) {
				c = _getch();
				if (c == KEY_RIGHT) {
					setTextColor(AQUA);
					setTextBGColor(YELLOW);
					gotoxy(83, 12);
					cout << "ARROW RIGHT - turn page right";
					Beep(600, 50);
					Sleep(50);
					setTextBGColor(WHITE);
					gotoxy(83, 12);
					cout << "ARROW RIGHT - turn page right";
					if (++page == maxPage + 1)
						page = 1;
				}
				if (c == KEY_LEFT) {
					setTextColor(AQUA);
					setTextBGColor(YELLOW);
					gotoxy(83, 10);
					cout << "ARROW LEFT - turn page left";
					Beep(600, 50);
					Sleep(50);
					setTextBGColor(WHITE);
					gotoxy(83, 10);
					cout << "ARROW LEFT - turn page left";
					if (--page == 0)
						page = maxPage;
				}
				goto __FORMATLIST__;
			}
			if (!isSearch) {
				if (c == ESC) {
					setTextColor(AQUA);
					setTextBGColor(YELLOW);
					gotoxy(83, 18);
					cout << "ESC - quit";
					Beep(800, 50);
					Sleep(50);
					setTextBGColor(WHITE);
					gotoxy(83, 18);
					cout << "ESC - quit";
					list.~ListAccount();
					return;
				}

				if (c == KEY_F3) {
					isSearch = true;
					gotoxy(83, 5);
					cout << "BACK - ESC       FIND - Enter";
					gotoxy(83, 4);
					setTextBGColor(BLACK);
					setTextColor(GRAY);
					cout << "Find..                       ";
					setTextColor(WHITE);
					gotoxy(83, 4);
					showCursor(true);
					continue;
				}
			}
			else {
				if (isCurrentSearch) {
					list = listAccount;
					isCurrentSearch = false;
				}
				setTextBGColor(BLACK);
				setTextColor(WHITE);
				gotoxy(83 + input.length(), 4);
				showCursor(true);
				if (c == ESC || c == KEY_F3) {
					setTextBGColor(WHITE);
					gotoxy(83, 4);
					cout << "                              ";
					gotoxy(83, 5);
					cout << "                              ";
					isSearch = false;
					input.clear();
					list = listAccount;
					goto __PRINTLIST__;
				}
				if (c == '\r') {
					list = list.searching(input);
					isCurrentSearch = true;
					goto __PRINTLIST__;
				}
				else if (c == '\b')
				{
					if (!input.empty()) {
						cout << "\b  \b";
						input.pop_back();
						gotoxy(83 + input.length(), 4);
					}
					if (input.empty()) {
						gotoxy(83, 4);
						setTextBGColor(BLACK);
						setTextColor(GRAY);
						cout << "Find..                       ";
						setTextColor(WHITE);
					}
				}
				else if (c >= 32) {
					gotoxy(83 + input.length(), 4);
					cout << char(toupper(c));
					input.push_back(toupper(c));
					if (input.length() == 1) {
						gotoxy(84, 4);
						cout << setFill(28);
						gotoxy(83 + input.length(), 4);
					}
				}
			}
			if (!isSearch) {
		__FORMATLIST__:
			switch (chooseSort)
			{
			case 0:
				if(!isSearch)
					list = listAccount;
				break;
			case 1:
				list.sortIf(compareUserbyName);
				break;
			case 2:
				list.sortIf(compareUserbyMoneyGreater);
				break;
			case -1:
				list.sortIf(compareUserbyNameGreater);
				break;
			case -2:
				list.sortIf(compareUserbyMoney);
			default:
				break;
			}
		__PRINTLIST__:
			maxPage = list.getSize() / 24;
			maxPage += (list.getSize() % 24 ? 1 : 0);
				gotoxy(83, 28);
				setTextBGColor(WHITE);
				setTextColor(BLACK);
				cout << "Trang " << page << '/' << maxPage;
				printListPerPage(page, chooseSort, list);
				showCursor(false);
			}
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

	gotoxy(g_adminMenuX + 4, g_adminMenuY + g_adminMenuHeight - 3);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "BACK - Esc";

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
		cout << setFill(30);
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
			if (c == ESC) {
				gotoxy(g_adminMenuX + 3, g_adminMenuY + g_adminMenuHeight - 3);
				setTextBGColor(LIGHT_RED);
				setTextColor(LIGHT_BLUE);
				cout << " BACK - Esc ";
				Beep(800, 50);
				Sleep(50);
				return;
			}
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
					if (++curr >= 4) {
						if (!input[3].empty() && !input[1].empty() && !input[2].empty()) {
							if (input[3] != "USD" && input[3] != "VND")
								input[3] = "VND";
							User newUser(input[0], "123456", Name(input[1]), Money(stoi(input[2]), input[3]));
							listAccount.append(newUser);
							listAccount.saveCard("./data/TheTu.txt");
							listAccount.save("./data/");
							Beep(1000, 200);
							
							return;
						}
						else {
							Beep(1000, 200);
							gotoxy(hoverText[3].x + 2, hoverText[3].y + 1);
							setTextBGColor(LIGHT_GREEN);
							setTextColor(RED);
							cout << "                             ";
							gotoxy(hoverText[3].x + 2, hoverText[3].y + 1);
							cout << "Khong duoc bo trong ";
							if (input[1].empty())
								cout << "o Ho Ten";
							else if (input[3].empty())
								cout << "o So Du";
							else cout << "o Tien Te";
							curr = 1;
							showCursor(false);
							_getch();
							gotoxy(hoverText[3].x + 2, hoverText[3].y + 1);
							cout << "                             ";
							showCursor(true);
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


void deleteUser() {
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
__INIT__:
	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, LIGHT_GREEN);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', YELLOW, RED);
	setTextBGColor(YELLOW);

	printArt(17, 0, "MenuAdmin.txt", RED, YELLOW);


	drawBorder(g_initMenuX + 24, g_initMenuY + 1, 29, 3, 1, RED, LIGHT_GREEN);
	gotoxy(g_adminMenuX + 26, g_adminMenuY + 2);
	setTextColor(RED);
	setTextBGColor(LIGHT_GREEN);
	cout << "NHAP ID TAI KHOAN CAN XOA";


	gotoxy(g_adminMenuX + 4, g_adminMenuY + g_adminMenuHeight - 3);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "BACK - Esc";


	setTextBGColor(LIGHT_GREEN);
	setTextColor(BLACK);

	
	POINT hoverText = {g_adminMenuX + 20, g_adminMenuY + 6};
	setTextBGColor(LIGHT_GREEN);
	gotoxy(hoverText.x, hoverText.y);
	cout << "ID: ";
	setTextBGColor(GRAY);
	gotoxy(hoverText.x += 4, hoverText.y);
	cout << setFill(29);

	bool isInput = true;
	string inputId = "";
	gotoxy(hoverText.x, hoverText.y);
	showCursor(true);
	while (true) {
		if (isInput)
			gotoxy(hoverText.x + inputId.length(), hoverText.y);
		
		if (_kbhit()) {
			char c = _getch();
			if (c == ESC) {
				gotoxy(g_adminMenuX + 3, g_adminMenuY + g_adminMenuHeight - 3);
				setTextBGColor(LIGHT_RED);
				setTextColor(LIGHT_BLUE);
				cout << " BACK - Esc ";
				Beep(800, 50);
				Sleep(50);
				return;
			}
			if (c == '\r' && !inputId.empty()) {
				User Temp = listAccount.getUserById(inputId);
				if (Temp.getId() != "00000000000000"){
					createBox(hoverText.x, hoverText.y + 1, 29, 6, YELLOW);
					gotoxy(hoverText.x, hoverText.y + 1);
					setTextBGColor(YELLOW);

					setTextColor(BLACK);
					cout << "TEN TAI KHOAN: ";
					gotoxy(hoverText.x, hoverText.y + 2);
					setTextColor(RED);
					cout << Temp.getName() << '\n';

					gotoxy(hoverText.x, hoverText.y + 3);
					setTextColor(BLACK);
					cout << "SO DU: ";
					gotoxy(hoverText.x, hoverText.y + 4);
					setTextColor(RED);
					cout << Temp.getAmount();

					gotoxy(hoverText.x, hoverText.y + 6);
					setTextBGColor(LIGHT_BLUE);
					setTextColor(RED);
					cout << "HUY - ESC";

					gotoxy(hoverText.x + 18, hoverText.y + 6);
					setTextBGColor(LIGHT_BLUE);
					setTextColor(RED);
					cout << "XOA - ENTER";

					c = _getch();

					if (c == ESC) {
						Beep(800, 50);
						gotoxy(hoverText.x, hoverText.y + 6);
						setTextBGColor(LIGHT_RED);
						setTextColor(BLUE);
						cout << "HUY - ESC";
						showCursor(false);
						Sleep(50);
						goto __INIT__;
					}
					else if (c == '\r') {
						Beep(800, 50);
						if (confirmProcess("Ban co chac muon xoa tai khoan nay ?")) {
							listAccount.removeUserById(inputId);
							listAccount.saveCard("./data/TheTu.txt");
							listAccount.save("./data/");
							createBox(g_adminMenuX, g_adminMenuY + 3, g_adminMenuWidth, 7, AQUA);
							gotoxy((g_adminMenuWidth / 2 + g_adminMenuX) - 7, g_adminMenuY + 6);
							setTextBGColor(AQUA);
							setTextColor(BLACK);
							cout << "DA XOA TAI KHOAN";
							showCursor(false);
							_getch();
							return;
						}
						else
						{
							goto __INIT__;
						}
					}
				}
				else {
					gotoxy(hoverText.x, hoverText.y + 1);
					setTextBGColor(LIGHT_GREEN);
					setTextColor(RED);
					cout << "Tai khoan khong ton tai!";
					Beep(1000, 200);
					_getch();
					gotoxy(hoverText.x, hoverText.y + 1);
					cout << "                        ";
				}
			}
			else if (c == '\b') {
				setTextBGColor(GRAY);
				setTextColor(GRAY);
				if (inputId.length() > 0) {
					cout << "\b  \b";
					inputId.pop_back();
				}
			}
			else if(isNumber(c) && inputId.length() < 15) {
				setTextBGColor(GRAY);
				setTextColor(BLACK);
				cout << c;
				inputId.push_back(c);
			}
		}
	}

}

void unblockUser() {
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
__INIT__:
	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, LIGHT_GREEN);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', YELLOW, RED);
	setTextBGColor(YELLOW);

	printArt(17, 0, "MenuAdmin.txt", RED, YELLOW);


	drawBorder(g_initMenuX + 22, g_initMenuY + 1, 32, 3, 1, RED, LIGHT_GREEN);
	gotoxy(g_adminMenuX + 24, g_adminMenuY + 2);
	setTextColor(RED);
	setTextBGColor(LIGHT_GREEN);
	cout << "NHAP ID TAI KHOAN CAN MO KHOA";


	gotoxy(g_adminMenuX + 4, g_adminMenuY + g_adminMenuHeight - 3);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "BACK - Esc";


	setTextBGColor(LIGHT_GREEN);
	setTextColor(BLACK);


	POINT hoverText = { g_adminMenuX + 20, g_adminMenuY + 6 };
	setTextBGColor(LIGHT_GREEN);
	gotoxy(hoverText.x, hoverText.y);
	cout << "ID: ";
	setTextBGColor(GRAY);
	gotoxy(hoverText.x += 4, hoverText.y);
	cout << setFill(29);

	bool isInput = true;
	string inputId = "";
	gotoxy(hoverText.x, hoverText.y);
	showCursor(true);
	while (true) {
		if (isInput)
			gotoxy(hoverText.x + inputId.length(), hoverText.y);

		if (_kbhit()) {
			char c = _getch();
			if (c == ESC) {
				gotoxy(g_adminMenuX + 3, g_adminMenuY + g_adminMenuHeight - 3);
				setTextBGColor(LIGHT_RED);
				setTextColor(LIGHT_BLUE);
				cout << " BACK - Esc ";
				Beep(800, 50);
				Sleep(50);
				return;
			}
			if (c == '\r' && !inputId.empty()) {
				User Temp = listAccount.getUserById(inputId);
				bool isNotBlock = false;
				if (Temp.getId() != "00000000000000") {
					isNotBlock = listIdBlocked.search(inputId) == NULL;
					if (isNotBlock)
						goto __EXCEPT__;
					createBox(hoverText.x, hoverText.y + 1, 29, 6, YELLOW);
					gotoxy(hoverText.x, hoverText.y + 1);
					setTextBGColor(YELLOW);

					setTextColor(BLACK);
					cout << "TEN TAI KHOAN: ";
					gotoxy(hoverText.x, hoverText.y + 2);
					setTextColor(RED);
					cout << Temp.getName() << '\n';
					gotoxy(hoverText.x, hoverText.y + 3);
					setTextColor(BLACK);
					cout << "SO DU: ";
					gotoxy(hoverText.x, hoverText.y + 4);
					setTextColor(RED);
					cout << Temp.getAmount();

					gotoxy(hoverText.x, hoverText.y + 6);
					setTextBGColor(LIGHT_BLUE);
					setTextColor(RED);
					cout << "HUY - ESC";
					gotoxy(hoverText.x + 14, hoverText.y + 6);
					setTextBGColor(LIGHT_BLUE);
					setTextColor(RED);
					cout << "MO KHOA - ENTER";

					c = _getch();
					if (c == ESC) {
						Beep(800, 50);
						gotoxy(hoverText.x, hoverText.y + 6);
						setTextBGColor(LIGHT_RED);
						setTextColor(BLUE);
						cout << "HUY - ESC";
						showCursor(false);
						Sleep(50);
						goto __INIT__;
					}
					else if (c == '\r') {
						Beep(800, 50);
						if (confirmProcess("Ban co chac muon mo khoa tai khoan nay ?")) {
							listIdBlocked.remove(inputId);
							listIdBlocked.save("./data/AccountBlocked/ALL.txt");
							createBox(g_adminMenuX, g_adminMenuY + 3, g_adminMenuWidth, 7, AQUA);
							gotoxy((g_adminMenuWidth / 2 + g_adminMenuX) - 7, g_adminMenuY + 6);
							setTextBGColor(AQUA);
							setTextColor(BLACK);
							cout << "DA MO KHOA TAI KHOAN";
							showCursor(false);
							_getch();
							return;
						}
						else
						{
							goto __INIT__;
						}
					}
				}
				else {
					__EXCEPT__:
					gotoxy(hoverText.x, hoverText.y + 1);
					setTextBGColor(LIGHT_GREEN);
					setTextColor(RED);
					if (isNotBlock)
						cout << "Tai khoan nay khong bi khoa";
					else
						cout << "Tai khoan khong ton tai!";
					Beep(1000, 200);
					showCursor(false);
					_getch();
					gotoxy(hoverText.x, hoverText.y + 1);
					cout << "                                 ";
					showCursor(true);
				}
			}
			else if (c == '\b') {
				setTextBGColor(GRAY);
				setTextColor(GRAY);
				if (inputId.length() > 0) {
					cout << "\b  \b";
					inputId.pop_back();
				}
			}
			else if (isNumber(c) && inputId.length() < 15) {
				setTextBGColor(GRAY);
				setTextColor(BLACK);
				cout << c;
				inputId.push_back(c);
			}
		}
	}

}



void adminMenu() {
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
		{g_adminMenuX + 23, g_adminMenuY + 13}
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
	
	gotoxy(g_adminMenuX + 23 + 24, g_adminMenuY + 17);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(RED);
	cout << "RIGHT / LEFT ARROW TO MOVE";

/***********************************************************************

							CHOOSE PROCESS

************************************************************************/

	short choose = 0;
	while (true) {
		drawBorder(BUTTON[choose].x, BUTTON[choose].y, 28, 3, 1, BLACK, YELLOW);
		showCursor(false);
		if (_kbhit()) {
			char c = _getch();

			if (c == ESC)
				goto __LOGOUT__;

			if (c == 32 || c == -32) {
				drawBorder(BUTTON[choose].x, BUTTON[choose].y, 28, 3, 1, BLACK, LIGHT_GREEN);
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
					deleteUser();
					goto __INIT__;
					break;
				}
				case 3: {
					unblockUser();
					goto __INIT__;
					break;
				}
				case 4: {
					__LOGOUT__:
					if (confirmProcess("Ban co chac muon dang xuat ?"))
						return;
					else
						goto __INIT__;
					break;
				}
				default:
					break;
				}
			}
		}
	}
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


	gotoxy(passInputX - 5, passInputY + 3);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "BACK - Esc";



	gotoxy(passInputX + 12, passInputY + 3);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "LOGIN - Enter";

	gotoxy(g_loginRectX + 8, g_loginRectY + 18);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(WHITE);
	cout << "BANG HAI TAC MU ROM BANK";

	/***************************************************************

							KEYBOARD EVENT

	****************************************************************/
	char c = '\0';
	string inputId = "", inputPass = "";
	bool isInputId = true;
	while (true) {
		if (isInputId)
			gotoxy(userInputX + inputId.length(), userInputY);
		else
			gotoxy(passInputX + inputPass.length(), passInputY);
		showCursor(true);
		if (_kbhit()) {
			setTextBGColor(BLACK);
			setTextColor(WHITE);
			c = _getch();

			if (c == ESC) {
				gotoxy(passInputX - 6, passInputY + 3);
				setTextBGColor(RED);
				setTextColor(LIGHT_GREEN);
				cout << " BACK - Esc ";
				showCursor(false);
				Beep(800, 50);
				Sleep(50);
				return;
			}
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
							wrongTime = 0;

							gotoxy(passInputX + 11, passInputY + 3);
							setTextBGColor(RED);
							setTextColor(LIGHT_GREEN);
							cout << " LOGIN - Enter ";
							showCursor(false);
							Sleep(50);
							adminMenu();
							goto LOGIN;
						}
						else if(!inputId.empty() && !inputPass.empty()) {
							if (++wrongTime == 3) {
								clrscr();
								waiting(30);
								goto LOGIN;
							} if (wrongTime == 4) {
								listAdmin.~ListAdministrator();
								listAccount.~ListAccount();
								setConsoleBackgroundColor(BACKGROUND_RED);
								setTextBGColor(RED);
								setTextColor(YELLOW);	
								clrscr();
								cout << "Ban da nhap sai qua nhieu lan!!!\n!!!!!!!!CANH BAO!!!!!!!!";
								showCursor(false);
								while (++wrongTime <= 30) {
									Beep(1200, 500);
									Sleep(5);
								}
								exit(0);
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
				continue;
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

			}
			else if(c != 32 && c != '\n' && c != '\t' && c != '\0') {
				if (isInputId && inputId.length() < 15) {
					cout << c;
					inputId = inputId + c;
				}
				else if(isNumber(c) && inputPass.length() < 6)
				{
					Beep(600, 40);
					cout << '*';
					inputPass = inputPass + c;
				}
			}
			
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
		" NGUOI DUNG",
		"THOAT"
	};
	for (int i = 0; i < 3; ++i) {
		drawBorder(BUTTON[i].x, BUTTON[i].y, 28, 3, 1, BLACK, LIGHT_GREEN);
		gotoxy(BUTTON[i].x  + (13 - nameButton[i].length() / 2), BUTTON[i].y + 1);
		cout << nameButton[i];
	}
	short choose = 0;
	string runningString = "    NGAN HANG BANG HAI TAC MU ROM    ";
	int len = runningString.length(), lenLarge = g_initMenuWidth;
	runningString = setFill(len) + runningString;
	runningString = runningString + setFill(len);
	int runWord = 0, runWordL = 0;

	string runLargeName[6];
	ifstream fin("FullNameBank.txt");
	for (int i = 0; i < 6; ++i) {
		getline(fin, runLargeName[i]);
		runLargeName[i] = setFill(79) + runLargeName[i];
		runLargeName[i] = runLargeName[i] + setFill(79);
	}
	fin.close();
	while (true) {
		gotoxy(g_initMenuX + 18, g_initMenuY + 15);
		setTextBGColor(BLACK);
		setTextColor(rand() % 15);
		cout << runningString.substr(runWord++, len);
		runWord = runWord >= len * 2 ? 0 : runWord;

		setTextBGColor(YELLOW);
		setTextColor(RED);
		for (int i = 0; i < 6; ++i) {
			gotoxy(17, i);
			cout << runLargeName[i].substr(runWordL, lenLarge);
			
		}
		++runWordL;
		runWordL = (runWordL >= 245) ? 0 : runWordL;
		Sleep(50);

		drawBorder(BUTTON[choose].x, BUTTON[choose].y, 28, 3, 1, BLACK, YELLOW);
		showCursor(false);
		if (_kbhit()) {
			char c = _getch();
			if (c == 32 || c == -32) {
				drawBorder(BUTTON[choose].x, BUTTON[choose].y, 28, 3, 1, BLACK, LIGHT_GREEN);
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
					if (confirmProcess("Ban co chac muon thoat chuong trinh ?")) {
						resetTextBGColor();
						resetTextColor();
						clrscr();
						return;
					}
					else {
						goto __INIT__;
					}
				}
			}
		}
	}



}
