#pragma once
#include "Defines.h"
#include "GlobalVariable.h"
#include "IndependentFunction.h"
#include "Drawing.h"


using namespace drawing;

class ATM
{
private:
	ListAdministrator listAdmin;
	ListAccount listAccount;
	LinkedList<string> listIdBlocked;

	void init();
	void waiting(int second);
	void printListPerPage(int page, int sort, ListAccount& list, LinkedList<string>& listIdBlocked);
	void printListUsers();
	void addUserToList();
	void deleteUser();
	void unblockUser();
	void adminMenu();
	void printInfoUser(User& user);
	bool transfer(User& user);
	void printListTransPerPage(int, LinkedList<string>&);
	void printListTrans(User& user);
	bool withrawMoney(User& user);
	bool changePassword(User& user);
	void userMenu(User& user);
	void loginPasswordAdmin(Admin&);
	void loginPasswordUser(User&);
	bool inputPassword(User&);
public:
	ATM();
	~ATM();
	void loginUserMenu();
	void loginAdminMenu();
	void runProcess();
};



void ATM::init() {
	SetConsoleTitle(L"ATM");
	listAdmin.load("./data/Admin.txt");
	listAccount.load("./data/", "./data/TheTu.txt");
	listIdBlocked.load("./data/AccountBlocked/ALL.txt");
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	loadingScreen("Loading...", 5);
}

void ATM::waiting(int second) {
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

void ATM::printListPerPage(int page, int sort, ListAccount& list, LinkedList<string>& listIdBlocked) {
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
	if (sort > 0) {
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

void ATM::printListUsers() {
	loadingScreen("Loading data...", 10);
	drawTableList();

	int page = 1, chooseSort = 0;
	int maxPage = listAccount.getSize() / 24;
	maxPage += (listAccount.getSize() % 24 ? 1 : 0);
	ListAccount list(listAccount);
	ListAccount filerList;
	string input = "";
	printListPerPage(1, 0, list, listIdBlocked);

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
	cout << "ARROW UP - change sort greater";
	gotoxy(83, 16);
	cout << "ARROW DOWN - change sort less";
	gotoxy(83, 18);
	cout << "ESC - quit";

	setTextColor(BLACK);
	gotoxy(83, 28);
	cout << "Trang " << page << '/' << maxPage;

	showCursor(false);
	bool isSearch = false, isCurrectSearch = false;
	while (true) {
		if (_kbhit) {
			char c = _getch();
			if (c == 0)
				c = _getch();

			if (c == -32) {
				c = _getch();
				if (c == KEY_UP)
				{
					setTextColor(AQUA);
					setTextBGColor(YELLOW);
					gotoxy(83, 14);
					cout << "ARROW UP - change sort greater";
					Beep(600, 50);
					Sleep(50);
					setTextBGColor(WHITE);
					gotoxy(83, 14);
					cout << "ARROW UP - change sort greater";
					if (chooseSort < 0)
						chooseSort = 0;
					else if (++chooseSort == 3)
						chooseSort = 0;
				}
				else if (c == KEY_DOWN) {
					setTextColor(AQUA);
					setTextBGColor(YELLOW);
					gotoxy(83, 16);
					cout << "ARROW DOWN - change sort less";
					Beep(600, 50);
					Sleep(50);
					setTextBGColor(WHITE);
					gotoxy(83, 16);
					cout << "ARROW DOWN - change sort less";
					if (chooseSort > 0)
						chooseSort = 0;
					else if (--chooseSort == -3) {
						chooseSort = 0;
					}
				}
				else if (c == KEY_RIGHT) {
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
				else if (c == KEY_LEFT) {
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
				if (isCurrectSearch) {
					list = listAccount;
					isCurrectSearch = false;
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
					isCurrectSearch = true;
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
				else if (c >= 32 && input.length() < 29) {
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
					if (!isSearch)
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
				printListPerPage(page, chooseSort, list, listIdBlocked);
				showCursor(false);
			}
		}
	}
	_getch();

}

void ATM::addUserToList() {
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
__INIT__:
	bool isVND = true;
	string input[5] = {
	 "", "", "", ""
	};
__BACK__:
	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, LIGHT_GREEN);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', YELLOW, RED);
	setTextBGColor(YELLOW);

	printArt(17, 0, "./art/MenuAdmin.txt", RED, YELLOW);


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
		if (!input[i].empty()) {
			setTextColor(BLACK);
			if(i != 3)
				gotoxy(hoverText[i].x, hoverText[i].y);
			else
				gotoxy(hoverText[3].x + 13, hoverText[3].y);
			cout << input[i];
		}else if (i == 3) {
			isVND = true;
			gotoxy(hoverText[3].x + 13, hoverText[3].y);
			setTextColor(BLACK);
			input[3] = "VND";
			cout << "VND";
		}
	}

	gotoxy(hoverText[3].x + 11, hoverText[3].y);
	cout << char(174);
	gotoxy(hoverText[3].x + 17, hoverText[3].y);
	cout << char(175);


	gotoxy(hoverText[0].x, hoverText[0].y + 1);
	setTextColor(RED);
	setTextBGColor(LIGHT_GREEN);
	cout << "F5 generate new ID";

	gotoxy(hoverText[3].x + 8, hoverText[3].y + 2);
	setTextBGColor(YELLOW);
	setTextColor(RED);
	cout << "TAO TAI KHOAN - Enter";

	//----------------------------------------------------------------
	setTextBGColor(GRAY);
	setTextColor(BLACK);
	gotoxy(hoverText[0].x, hoverText[0].y);
	showCursor(true);
	char c = '\0';


	do {
		input[0] = getRandomId();
	} while (input[0].at(0) == '0' || listAccount.isHasUser(input[0]));
	gotoxy(hoverText[0].x, hoverText[0].y);
	cout << input[0];

	int curr = 1;
	while (true) {
		setCursorColor(FOREGROUND_RED);
		// MOVE CURSOR
		gotoxy(hoverText[curr].x + input[curr].length(), hoverText[curr].y);
		if (curr != 3)
			showCursor(true);
		else
			showCursor(false);
		
			
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
			if (c == KEY_F5) {
				do {
					input[0] = getRandomId();
				} while (input[0].at(0) == '0' || listAccount.isHasUser(input[0]));
				gotoxy(hoverText[0].x, hoverText[0].y);
				setTextBGColor(GRAY);
				setTextColor(BLACK);
				cout << input[0];
				continue;
			}

			// CHUYEN DONG
			if (c == '\r' || c == -32) {
				if (curr == 3) {
					setTextBGColor(GRAY);
					setTextColor(BLACK);
					gotoxy(hoverText[3].x + 13, hoverText[3].y);
					cout << input[3];
				}
				if (c == -32) {
					c = _getch();
					if (c == KEY_UP)
						if (--curr == 0)
							curr = 3;
					if (c == KEY_DOWN)
						if (++curr >= 4)
							curr = 1;
					if (c == KEY_LEFT || c == KEY_RIGHT) {
						if (curr == 3) {
							setTextBGColor(GRAY);
							setTextColor(BLACK);
							gotoxy(hoverText[curr].x + 13, hoverText[curr].y);
							if (isVND) {
								cout << "USD";
								input[curr] = "USD";
								isVND = false;
							}
							else {
								cout << "VND";
								input[curr] = "VND";
								isVND = true;
							}
						}
					}
				}
				if (c == '\r')
					if (++curr >= 4) {
						Money mon(stringToInt(input[2]), input[3]);
						if (!input[3].empty() && !input[1].empty() && !input[2].empty() && mon.getAmount() >= 50000) {
							if (confirmProcess("Ban co chac muon them tai khoan ?")) {
								User newUser(input[0], encoding("123456"), Name(input[1]), mon);
								listAccount.append(newUser);
								listAccount.saveCard("./data/TheTu.txt");
								listAccount.save("./data/");
								createBox(g_adminMenuX, g_adminMenuY + 3, g_adminMenuWidth, 7, AQUA);
								gotoxy((g_adminMenuWidth / 2 + g_adminMenuX) - 7, g_adminMenuY + 6);
								setTextBGColor(AQUA);
								setTextColor(BLACK);
								cout << "DA THEM TAI KHOAN";
								Beep(1000, 200);
								_getch();
								return;
							}
							else
								goto __BACK__;
						}
						else {
							Beep(1000, 200);
							gotoxy(hoverText[3].x + 2, hoverText[3].y + 1);
							setTextBGColor(LIGHT_GREEN);
							setTextColor(RED);
							cout << "                                   ";
							gotoxy(hoverText[3].x + 2, hoverText[3].y + 1);
							if (input[1].empty())
								cout << "Khong duoc bo trong o Ho Ten";
							else if (input[2].empty())
								cout << "Khong duoc bo trong o So Du";
							else if (input[3].empty())
								cout << "Khong duoc bo trong o Tien Te";
							else if (mon.getAmount() < 50000)
								cout << "Tien nap vao phai it nhat 50.000VND";
							curr = 1;
							showCursor(false);
							_getch();
							gotoxy(hoverText[3].x + 2, hoverText[3].y + 1);
							cout << "                                   ";
							showCursor(true);
						}
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
					setTextBGColor(GRAY);
					setTextColor(BLACK);
					if (curr == 1) {
						if ((isWord(c) || c == 32) && input[curr].length() < 25) {
							if (c == 32) {
								if (input[curr].empty())
									continue;
								else if (input[curr][input[curr].length() - 1] == 32)
									continue;
							}
							cout << char(toupper(c));
							input[curr].push_back(toupper(c));

						}
					}
					else if (curr == 2 && isNumber(c) && input[curr].length() < 11) {
						cout << c;
						input[curr].push_back(c);
					}
					else if (curr == 3) {
						gotoxy(hoverText[curr].x + 13, hoverText[curr].y);
						if (isVND) {
							cout << "USD";
							input[curr] = "USD";
							isVND = false;
						}
						else {
							cout << "VND";
							input[curr] = "VND";
							isVND = true;
						}
					}
				
			}
			if (curr == 3) {
				setTextBGColor(YELLOW);
				setTextColor(BLACK);
				gotoxy(hoverText[3].x + 13, hoverText[3].y);
				cout << input[3];
			}

		}
	}
	_getch();
}

void ATM::deleteUser() {
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
__INIT__:
	string inputId = "";
__BACK__:

	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, LIGHT_GREEN);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', YELLOW, RED);
	setTextBGColor(YELLOW);

	printArt(17, 0, "./art/MenuAdmin.txt", RED, YELLOW);


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


	POINT hoverText = { g_adminMenuX + 20, g_adminMenuY + 6 };
	setTextBGColor(LIGHT_GREEN);
	gotoxy(hoverText.x, hoverText.y);
	cout << "ID: ";
	setTextBGColor(GRAY);
	gotoxy(hoverText.x += 4, hoverText.y);
	cout << setFill(29);
	if (!inputId.empty()) {
		gotoxy(hoverText.x, hoverText.y);
		setTextColor(BLACK);
		cout << inputId;
	}

	bool isInput = true;
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
				if (inputId.length() < 14) {
					gotoxy(hoverText.x, hoverText.y + 1);
					setTextBGColor(LIGHT_GREEN);
					setTextColor(RED);
					cout << "ID phai co du 14 chu so";
					Beep(1000, 200);
					showCursor(false);
					_getch();
					gotoxy(hoverText.x, hoverText.y + 1);
					cout << "                        ";
					showCursor(true);
					continue;
				}
				User Temp = listAccount.getUserById(inputId);
				if (Temp.getId() != "00000000000000") {
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
						goto __BACK__;
					}
					else if (c == '\r') {
						Beep(800, 50);
						if (confirmProcess("Ban co chac muon xoa tai khoan nay ?")) {
							listAccount.removeUserById(inputId);
							listAccount.saveCard("./data/TheTu.txt");
							listAccount.save("./data/");
							string fileName = "./data/" + inputId + ".txt";
						
							if (std::remove(fileName.c_str()) != 0);
							fileName = "./data/TransactionHistory/LichSu" + inputId + ".txt";
							if (std::remove(fileName.c_str()) != 0);


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
							goto __BACK__;
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
			else if (isNumber(c) && inputId.length() < 14) {
				setTextBGColor(GRAY);
				setTextColor(BLACK);
				cout << c;
				inputId.push_back(c);
			}
		}
	}

}

void ATM::unblockUser() {
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
__INIT__:
	string inputId = "";
__BACK__:

	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, LIGHT_GREEN);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', YELLOW, RED);
	setTextBGColor(YELLOW);

	printArt(17, 0, "./art/MenuAdmin.txt", RED, YELLOW);


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
	if (!inputId.empty()) {
		gotoxy(hoverText.x, hoverText.y);
		setTextColor(BLACK);
		cout << inputId;
	}

	bool isInput = true;
	
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
				if (inputId.length() < 14) {
					gotoxy(hoverText.x, hoverText.y + 1);
					setTextBGColor(LIGHT_GREEN);
					setTextColor(RED);
					cout << "ID phai co du 14 chu so";
					Beep(1000, 200);
					showCursor(false);
					_getch();
					gotoxy(hoverText.x, hoverText.y + 1);
					cout << "                        ";
					showCursor(true);
					continue;
				}
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
						goto __BACK__;
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
							goto __BACK__;
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
			else if (isNumber(c) && inputId.length() < 14) {
				setTextBGColor(GRAY);
				setTextColor(BLACK);
				cout << c;
				inputId.push_back(c);
			}
		}
	}

}

void ATM::adminMenu() {
__INIT__:
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, LIGHT_GREEN);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', WHITE, RED);
	setTextBGColor(YELLOW);

	printArt(17, 0, "./art/MenuAdmin.txt", RED, YELLOW);
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

	gotoxy(g_adminMenuX + 23 + 18, g_adminMenuY + 17);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_RED);
	cout << "UP/DOWN/RIGHT/LEFT ARROW TO MOVE";

	/***********************************************************************

								CHOOSE PROCESS

	************************************************************************/

	short choose = 0;
	bool isLeft = true;
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
				if (c == KEY_RIGHT || c == 32)
					if (++choose == 5)
						choose = 0;
				if (c == KEY_LEFT)
					if (--choose == -1)
						choose = 4;
				if (c == KEY_UP)
				{
					if (choose - 2 < 0)
						choose = 4;
					else if (choose == 4)
						choose = (isLeft ? 2 : 3);
					else
						choose -= 2;
				}
				else if (c == KEY_DOWN)
				{
					choose += 2;
					if (choose == 5) {
						choose = 4;
						isLeft = false;
					}
					else if (choose == 4)
						isLeft = true;
					choose = (choose > 4 ? 0 : choose);
				}
			}
			else if (c == '\r') {
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

void ATM::loginPasswordAdmin(Admin& admin) {
LOGIN:
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	printArt(17, 0, "./art/NameBank.txt", RED, YELLOW);


	createBox(g_loginRectX, g_loginRectY, g_loginRectWidth, g_loginRectHeight, LIGHT_GREEN);
	printArt(g_loginRectX + 8, g_loginRectY, "./art/ATM.txt", RED, LIGHT_GREEN);
	drawBorder(g_loginRectX - 1, g_loginRectY - 1, g_loginRectWidth + 2, g_loginRectHeight + 2, '*', WHITE, RED);

	setTextColor(RED);
	setTextBGColor(LIGHT_GREEN);
	gotoxy(g_loginRectX + 15, g_loginRectY + 8);
	cout << "NHAP MA PIN";

	POINT box[6] = {
		{g_loginRectX + 6, userInputY},
		{g_loginRectX + 11, userInputY},
		{g_loginRectX + 16, userInputY},
		{g_loginRectX + 21, userInputY},
		{g_loginRectX + 26, userInputY},
		{g_loginRectX + 31, userInputY}
	};
	
	for (int i = 0; i < 6; ++i) {
		createBox(box[i].x, box[i].y, 3, 2, GRAY);
	}

	gotoxy(passInputX - 5, passInputY + 2);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "BACK - Esc";

	gotoxy(passInputX + 13, passInputY + 2);
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
	string pw;
	while (true) {
		showCursor(false);
		if (_kbhit()) {
			char c = _getch();
			if (c == ESC) {
				gotoxy(passInputX - 6, passInputY + 2);
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

			if (c == '\r') {
				__ENTERLOGIN__:
				if (pw.length() < 6) {
					Beep(1000, 200);
					setTextBGColor(LIGHT_GREEN);
					setTextColor(RED);
					gotoxy(passInputX - 2, passInputY);
					cout << "Khong duoc bo trong PIN!";
					showCursor(false);
					_getch();
					gotoxy(passInputX - 2, passInputY);
					cout << "                         ";
					showCursor(false);
				}
				else if(isCurrect(admin, pw)) {
					gotoxy(passInputX + 13, passInputY + 2);
					setTextBGColor(LIGHT_RED);
					setTextColor(LIGHT_BLUE);
					cout << "LOGIN - Enter";
					Beep(800, 50);
					Sleep(50);
					wrongTime = 0;
					adminMenu();
					return;
				}
				else {
					if (++wrongTime == 3) {
						waiting(30);
						pw.clear();
						goto LOGIN;
					}
					else if (wrongTime == 4) {
						setConsoleBackgroundColor(BACKGROUND_RED);
						clrscr();
						listAccount.~ListAccount();
						listAdmin.~ListAdministrator();
						listIdBlocked.~LinkedList();
						setTextBGColor(RED);
						setTextColor(YELLOW);
						gotoxy(userInputX, userInputY - 5);
						cout << "BAN DA NHAP SAI QUA NHIEU LAN\n";
						gotoxy(userInputX, userInputY - 4);
						cout << "  !!!!!!!!CANH BAO!!!!!!!!!\n";
						while (++wrongTime <= 25) {
							Beep(1200, 200);
							Sleep(100);
						}
						exit(0);
					}
					else {
						Beep(1000, 200);
						gotoxy(passInputX - 2, passInputY);
						setTextBGColor(LIGHT_GREEN);
						setTextColor(RED);
						cout << "Ban da nhap sai mat khau!";
						showCursor(false);
						_getch();
						showCursor(true);
						gotoxy(passInputX - 2, passInputY);
						cout << "                         ";
					}
				}
				continue;
			}
			else if (c == '\b') {
				if (!pw.empty()) {
					Beep(600, 50);
					createBox(box[pw.length() - 1].x, box[pw.length() - 1].y, 3, 2, GRAY);
					pw.pop_back();
				}
			}
			else if (isNumber(c) && pw.length() < 6) {
				Beep(600, 50);
				drawNut(box[pw.length()].x, box[pw.length()].y, BLACK, GRAY);
				pw.push_back(c);
				showCursor(false);
			}

		}
	}




}

void ATM::loginAdminMenu() {
__INIT__:
	
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	printArt(17, 0, "./art/NameBank.txt", RED, YELLOW);

	

	createBox(g_loginRectX, g_loginRectY, g_loginRectWidth, g_loginRectHeight, LIGHT_GREEN);
	printArt(g_loginRectX + 8, g_loginRectY, "./art/ATM.txt", RED, LIGHT_GREEN);
	drawBorder(g_loginRectX - 1, g_loginRectY - 1, g_loginRectWidth + 2, g_loginRectHeight + 2, '*', WHITE, RED);

	setTextColor(RED);
	setTextBGColor(LIGHT_GREEN);
	gotoxy(g_loginRectX + 14, g_loginRectY + 8);
	cout << "ADMIN LOGIN";


	gotoxy(userInputX - 6, userInputY);
	setTextBGColor(BLACK);
	setTextColor(RED);
	cout << "User:                         ";



	gotoxy(passInputX - 5, passInputY + 2);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "BACK - Esc";



	gotoxy(passInputX + 13, passInputY + 2);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "NEXT - Enter";

	gotoxy(g_loginRectX + 8, g_loginRectY + 18);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(WHITE);
	cout << "BANG HAI TAC MU ROM BANK";

	/***************************************************************

							KEYBOARD EVENT

	****************************************************************/
	char c = '\0';
	string inputId = "";
	while (true) {
		showCursor(true);
		gotoxy(userInputX + inputId.length(), userInputY);
		if (_kbhit()) {
			setTextBGColor(BLACK);
			setTextColor(WHITE);
			c = _getch();

			if (c == ESC) {
				gotoxy(passInputX - 6, passInputY + 2);
				setTextBGColor(RED);
				setTextColor(LIGHT_GREEN);
				cout << " BACK - Esc ";
				showCursor(false);
				Beep(800, 50);
				Sleep(50);
				return;
			}
			if (c == 0 || c == 224 || c == -32) {
				c = _getch();
				continue;
			}
			if (c == '\r') {
				if (inputId.empty()) {
					
					Beep(1000, 200);
					setTextBGColor(LIGHT_GREEN);
					setTextColor(RED);
					gotoxy(userInputX - 2, userInputY + 1);
					cout << "Khong duoc bo trong USER!";
					showCursor(false);
					_getch();
					showCursor(true);
					gotoxy(userInputX - 2, userInputY + 1);
					cout << "                         ";
					gotoxy(userInputX + inputId.length(), userInputY);
				}
				else {
					Admin admin = listAdmin.getAdministratorById(inputId);
					if (admin.getUser() != "none") {
						gotoxy(passInputX + 13, passInputY + 2);
						setTextBGColor(LIGHT_RED);
						setTextColor(LIGHT_BLUE);
						cout << "NEXT - Enter";
						Beep(800, 50);
						showCursor(false);
						Sleep(50);
						loginPasswordAdmin(admin);
						goto __INIT__;
					}
					else {
						Beep(1000, 200);
						setTextBGColor(LIGHT_GREEN);
						setTextColor(RED);
						gotoxy(userInputX - 2, userInputY + 1);
						cout << "Tai khoan khong ton tai!";
						showCursor(false);
						_getch();
						showCursor(true);
						gotoxy(userInputX - 2, userInputY + 1);
						cout << "                         ";
						gotoxy(userInputX + inputId.length(), userInputY);
					}
				}
				continue;
			}
			else if (c == '\b') {
				if (!inputId.empty()) {
					cout << "\b  \b";
					inputId.pop_back();
				}
			}
			else if (c != 32 && c != '\n' && c != '\t' && c != '\0') {
				if ((isNumber(c) || isWord(c)) && inputId.length() < 14) {
					cout << c;
					inputId = inputId + c;
				}
			}

		}
	}
}

void ATM::printInfoUser(User& user) {
__INIT__:
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, LIGHT_GREEN);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', WHITE, LIGHT_BLUE);
	setTextBGColor(YELLOW);
	printArt(17, 0, "./art/UserMenu.txt", RED, YELLOW);



	drawBorder(g_initMenuX + 25, g_initMenuY + 3, 25, 3, 1, RED, LIGHT_GREEN);
	gotoxy(g_adminMenuX + 27, g_adminMenuY + 4);
	setTextColor(RED);
	setTextBGColor(LIGHT_GREEN);
	cout << " THONG TIN TAI KHOAN";

	gotoxy(g_adminMenuX + 4, g_adminMenuY + g_adminMenuHeight - 3);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_RED);
	cout << "BACK - Esc";

	setTextBGColor(LIGHT_GREEN);
	setTextColor(BLACK);

	POINT hoverText[3] = {
		{g_adminMenuX + 12, g_adminMenuY + 7},
		{g_adminMenuX + 12, g_adminMenuY + 10},
		{g_adminMenuX + 12, g_adminMenuY + 13},
	};
	string titleHoverText[3] = {
		"ID: ",
		"HO VA TEN: ",
		"SO DU: ",
	};
	for (int i = 0; i < 3; ++i) {
		setTextBGColor(LIGHT_GREEN);
		gotoxy(hoverText[i].x, hoverText[i].y);
		cout << setw(14) << right << titleHoverText[i];
		setTextBGColor(YELLOW);
		gotoxy(hoverText[i].x + 14, hoverText[i].y);
		cout << setFill(24);
		hoverText[i].x += 14;
		gotoxy(hoverText[i].x, hoverText[i].y);
		setTextColor(BLACK);
		switch (i)
		{
		case 0:{
			cout << user._id;
			break;
		}
		case 1:
			cout << user.getName();
			break;
		case 2:
			cout << user.getAmount();
		default:
			break;
		}
	}
	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if (c == ESC) {
				gotoxy(g_adminMenuX + 4, g_adminMenuY + g_adminMenuHeight - 3);
				setTextBGColor(LIGHT_RED);
				setTextColor(LIGHT_GREEN);
				cout << "BACK - Esc";
				showCursor(false);
				Beep(800, 50);
				Sleep(50);
				return;
			}
		}
	}
	_getch();
}

bool ATM::withrawMoney(User& user) {
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
__INIT__:
	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, LIGHT_GREEN);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', YELLOW, LIGHT_BLUE);
	setTextBGColor(YELLOW);
	printArt(17, 0, "./art/UserMenu.txt", RED, YELLOW);

	drawBorder(g_initMenuX + 24, g_initMenuY + 1, 29, 3, 1, AQUA, LIGHT_GREEN);
	gotoxy(g_adminMenuX + 26, g_adminMenuY + 2);
	setTextColor(BLUE);
	setTextBGColor(LIGHT_GREEN);
	cout << "  NHAP SO TIEN CAN RUT";


	gotoxy(g_adminMenuX + 4, g_adminMenuY + g_adminMenuHeight - 3);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "BACK - Esc";

	setTextBGColor(LIGHT_GREEN);
	setTextColor(BLACK);


	POINT hoverText = { g_adminMenuX + 15, g_adminMenuY + 7 };
	setTextBGColor(LIGHT_GREEN);
	setTextColor(RED);
	gotoxy(hoverText.x, hoverText.y - 2);
	cout << "  SO DU:";
	setTextBGColor(GRAY);
	setTextColor(BLACK);
	gotoxy(hoverText.x + 9, hoverText.y - 2);
	cout << " " << user._money << " ";

	setTextBGColor(LIGHT_GREEN);
	gotoxy(hoverText.x - 5, hoverText.y);
	cout << "Nhap so tien: ";
	setTextBGColor(GRAY);
	gotoxy(hoverText.x += 9, hoverText.y);
	cout << setFill(29);
	gotoxy(hoverText.x + 26, hoverText.y);
	cout << "VND";

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
				return true;
			}
			if (c == '\r' && !inputId.empty()) {
				int money = stringToInt(inputId);
				if (money >= 50000 && money % 50000 == 0 && user.getAmount().getAmount() - money >= 50000) {
					createBox(hoverText.x , hoverText.y + 1, 29, 6, YELLOW);
					gotoxy(hoverText.x, hoverText.y + 1);
					setTextBGColor(YELLOW);

					setTextColor(RED);
					gotoxy(hoverText.x + 6, hoverText.y + 2);
					cout << "SO DU CON LAI";
					gotoxy(hoverText.x + 6, hoverText.y + 3);
					cout << "SAU KHI RUT LA";
					
					
					setTextColor(BLACK);
					gotoxy(hoverText.x + 6, hoverText.y + 4);
					Money temp(user.getAmount().getAmount() - money, "VND");
					temp.setType(user.getAmount().getType());
					cout << temp;

					gotoxy(hoverText.x, hoverText.y + 6);
					setTextBGColor(LIGHT_BLUE);
					setTextColor(RED);
					cout << "HUY - ESC";

					gotoxy(hoverText.x + 18, hoverText.y + 6);
					setTextBGColor(LIGHT_BLUE);
					setTextColor(RED);
					cout << "RUT - ENTER";
					showCursor(false);
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
						if (confirmProcess("Ban co chac muon rut ?")) {
							listAccount.updatePriceUser(user._id, -money);
							listAccount.save("./data/");
							createBox(g_adminMenuX, g_adminMenuY + 3, g_adminMenuWidth, 7, AQUA);
							gotoxy((g_adminMenuWidth / 2 + g_adminMenuX) - 7, g_adminMenuY + 4);
							setTextBGColor(AQUA);
							setTextColor(BLACK);
							cout << "SO TIEN CUA BAN LA";
							setTextColor(PURPLE);
							string tien = withdraw(money);
							gotoxy((g_adminMenuWidth / 2 + g_adminMenuX) - tien.length() / 2, g_adminMenuY + 6);
							cout << tien;
							showCursor(false);
							_getch();
							return confirmProcess("BAN CO MUON THUC HIEN GIAO DICH KHAC?");
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
					
					if (money < 50000)
						cout << "So tien rut it nhat la 50.000";
					else if (money > user.getAmount().getAmount())
						cout << "Ban khong du so du";
					else if (user.getAmount().getAmount() - money < 50000)
						cout << "So du con lai phai it nhat 50.000VND";
					else if (money % 50000 != 0)
						cout << "So tien phai la boi cua 50.000";

					Beep(1000, 200);
					_getch();
					gotoxy(hoverText.x, hoverText.y + 1);
					cout << "                                    ";
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
			else if (isNumber(c) && inputId.length() < 10) {
				setTextBGColor(GRAY);
				setTextColor(BLACK);
				cout << c;
				inputId.push_back(c);
			}
		}
	}

}

bool ATM::transfer(User& user) {
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
__INIT__:
	string inputId = "";
__BACK__:
	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, LIGHT_GREEN);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', YELLOW, LIGHT_BLUE);
	setTextBGColor(YELLOW);

	printArt(17, 0, "./art/UserMenu.txt", RED, YELLOW);


	drawBorder(g_initMenuX + 26, g_initMenuY + 1, 26, 3, 1, RED, LIGHT_GREEN);
	gotoxy(g_adminMenuX + 27 + 6, g_adminMenuY + 2);
	setTextColor(RED);
	setTextBGColor(LIGHT_GREEN);
	cout << "CHUYEN KHOAN";


	gotoxy(g_adminMenuX + 4, g_adminMenuY + g_adminMenuHeight - 3);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "BACK - Esc";


	setTextBGColor(LIGHT_GREEN);
	setTextColor(BLACK);




	POINT hoverText = { g_adminMenuX + 20, g_adminMenuY + 7 };

	setTextBGColor(LIGHT_GREEN);
	setTextColor(RED);
	gotoxy(hoverText.x - 3, hoverText.y - 2);
	cout << "SO DU: ";
	setTextBGColor(GRAY);
	setTextColor(BLACK);
	gotoxy(hoverText.x + 4, hoverText.y - 2);
	cout << " " << user._money << " ";

	setTextBGColor(LIGHT_GREEN);
	gotoxy(hoverText.x - 5, hoverText.y);
	cout << "Nhap ID: ";
	setTextBGColor(GRAY);
	gotoxy(hoverText.x += 4, hoverText.y);
	cout << setFill(29);

	if (!inputId.empty()) {
		setTextColor(BLACK);
		gotoxy(hoverText.x, hoverText.y);
		cout << inputId;
	}
	//-------------------------------------------------------------------------------------------


	bool isInput = true;
	
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
				return true;
			}
			if (c == '\r' && !inputId.empty()) {
				if (inputId.length() < 14) {
					gotoxy(hoverText.x, hoverText.y + 1);
					setTextBGColor(LIGHT_GREEN);
					setTextColor(RED);
					cout << "ID phai co du 14 chu so";
					Beep(1000, 200);
					showCursor(false);
					_getch();
					gotoxy(hoverText.x, hoverText.y + 1);
					cout << "                        ";
					showCursor(true);
					continue;
				}
				User Temp = listAccount.getUserById(inputId);
				bool isBlock = false;
				if (Temp.getId() != "00000000000000" && inputId != user._id) {
					isBlock = listIdBlocked.search(inputId) != NULL;
					if (isBlock)
						goto __EXCEPT__;
					createBox(hoverText.x - 2, hoverText.y + 1, 32, 8, AQUA);
					drawBorder(hoverText.x - 2, hoverText.y + 1, 32, 9, 32, LIGHT_BLUE, WHITE);
					setTextBGColor(AQUA);

					gotoxy(hoverText.x, hoverText.y + 2);
					setTextColor(BLACK);
					cout << "TEN TAI KHOAN: ";
					gotoxy(hoverText.x, hoverText.y + 3);
					setTextColor(RED);
					cout << Temp.getName() << '\n';
					
					gotoxy(hoverText.x, hoverText.y + 4);
					setTextColor(BLACK);
					cout << "NHAP SO TIEN: ";
					gotoxy(hoverText.x, hoverText.y + 5);
					setTextBGColor(GRAY);
					cout << setFill(28);

					gotoxy(hoverText.x + 25, hoverText.y + 5);
					cout << "VND";


					gotoxy(hoverText.x - 1, hoverText.y + 8);
					setTextBGColor(YELLOW);
					setTextColor(LIGHT_GREEN);
					cout << "HUY - ESC";
					gotoxy(hoverText.x + 15, hoverText.y + 8);
					setTextBGColor(YELLOW);
					setTextColor(LIGHT_GREEN);
					cout << "CHUYEN - ENTER";
					string inputMn;
					while (true) {
						showCursor(true);
						gotoxy(hoverText.x + inputMn.length(), hoverText.y + 5);
						if (_kbhit()) {
							c = _getch();
							if (c == ESC) {
								Beep(800, 50);
								gotoxy(hoverText.x - 1, hoverText.y + 8);
								setTextBGColor(LIGHT_RED);
								setTextColor(BLUE);
								cout << "HUY - ESC";
								inputMn.clear();
								showCursor(false);
								Sleep(50);
								createBox(hoverText.x - 2, hoverText.y + 1, 32, 9, LIGHT_GREEN);
								gotoxy(hoverText.x + inputId.length(), hoverText.y);
								showCursor(true);
								break;
							}
							else if (c == '\r' && !inputMn.empty()) {
								gotoxy(hoverText.x + 15, hoverText.y + 8);
								setTextBGColor(RED);
								setTextColor(LIGHT_BLUE);
								Beep(800, 50);
								cout << "CHUYEN - ENTER";
								Sleep(50);
								gotoxy(hoverText.x + 15, hoverText.y + 8);
								setTextBGColor(YELLOW);
								setTextColor(LIGHT_GREEN);
								cout << "CHUYEN - ENTER";
								int money = stringToInt(inputMn);
								if (money >= 50000 && user._money.getAmount() - money >= 50000 && money % 50000 == 0) {
									if (confirmProcess("Ban co chac muon chuyen tien ?")) {
										listAccount.transfer(user._id, inputId, money);
										listAccount.save("./data/");
										createBox(g_adminMenuX, g_adminMenuY + 3, g_adminMenuWidth, 7, AQUA);
										gotoxy((g_adminMenuWidth / 2 + g_adminMenuX) - 12, g_adminMenuY + 6);
										setTextBGColor(AQUA);
										setTextColor(BLACK);
										cout << "CHUYEN KHOAN THANH CONG";
										_getch();
										return confirmProcess("BAN CO MUON THUC HIEN GIAO DICH KHAC ?");
									}
									else 
										goto __BACK__;

								}
								else {
									setTextBGColor(AQUA);
									setTextColor(RED);
									gotoxy(hoverText.x, hoverText.y + 6);
									if (money < 50000)
										cout << "So tien it nhat la 50.000VND";
									else if (money > user._money.getAmount())
										cout << "Ban khong du so du";
									else if (user._money.getAmount() - money < 50000)
										cout << "So du it nhat la 50.000VND";
									else
										cout << "So tien phai la boi cua 50000";
									showCursor(false);
									_getch();
									showCursor(true);
									setTextBGColor(AQUA);
									gotoxy(hoverText.x, hoverText.y + 6);
									cout << "                             ";
								}
							}
							else if (c == '\b') {
								if (!inputMn.empty()) {
									setTextBGColor(GRAY);
									cout << "\b  \b";
									inputMn.pop_back();
								}
							}
							else if (isNumber(c) && inputMn.length() < 11) {
								setTextBGColor(GRAY);
								setTextColor(BLACK);
								gotoxy(hoverText.x + inputMn.length(), hoverText.y + 5);
								cout << c;
								inputMn.push_back(c);
							}
						}
					}
				}
				else {
				__EXCEPT__:
					gotoxy(hoverText.x, hoverText.y + 1);
					setTextBGColor(LIGHT_GREEN);
					setTextColor(RED);
					if (isBlock)
						cout << "Tai khoan nay bi khoa";
					else if (inputId == user._id)
						cout << "Khong duoc chuyen cho minh";
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
			else if (isNumber(c) && inputId.length() < 14) {
				setTextBGColor(GRAY);
				setTextColor(BLACK);
				cout << c;
				inputId.push_back(c);
			}
		}
	}

}

void ATM::printListTransPerPage(int page, LinkedList<string>& list) {
	int i = 3;
	for (LinkedList<string>::Iterator it = list.begin() + page; it != list.end(); ++it) {
		string s = *it;
		if (i >= 29 || i + s.size() / 79 >= 29)
			break;
		while (!s.empty()) {
			gotoxy(1, i++);
			int breakline = 79;
			if (s.size() > 79) {
				while (s[breakline] != 32)
					--breakline;
			}
			cout << s.substr(0, breakline + 1);
			s.erase(0, breakline + 1);
		}
		gotoxy(1, i);
		for (int k = 0; k < 79; ++k)
			cout << '-';
		++i;
	}
	showCursor(false);
}

void ATM::printListTrans(User& user) {
	clrscr();
	drawTransList();
	setTextColor(BLACK);
	gotoxy(83, 3);
	cout << "F3 - search";
	setTextColor(LIGHT_RED);
	gotoxy(83, 8);
	cout << "HOT KEY:";
	setTextColor(AQUA);
	gotoxy(83, 10);
	cout << "ARROW UP - scroll list up";
	gotoxy(83, 12);
	cout << "ARROW DOWN - scroll list down";
	gotoxy(83, 14);
	cout << "ESC - quit";

	LinkedList<string> content; 
	content = user._trans.createContent(user._money, listAccount);
	LinkedList<string> list(content);
	int page = 0;
	string input = "";
	setTextColor(BLACK);
	printListTransPerPage(0, list);
	//------------------------------------------------------------------------------------------------------
	showCursor(false);
	bool isSearch = false, isCurrectSearch = false;
	while (true) {
		if (_kbhit) {
			char c = _getch();
			if (c == 0)
				c = _getch();

			if (c == -32) {
				c = _getch();
				if (c == KEY_UP){
					setTextColor(AQUA);
					setTextBGColor(YELLOW);
					gotoxy(83, 10);
					cout << "ARROW UP - scroll list up";
					Beep(600, 50);
					Sleep(50);
					setTextBGColor(WHITE);
					gotoxy(83, 10);
					cout << "ARROW UP - scroll list up";
					if (page - 1 >= 0)
						--page;
						
				}
				else if (c == KEY_DOWN) {
					setTextColor(AQUA);
					setTextBGColor(YELLOW);
					gotoxy(83, 12);
					cout << "ARROW DOWN - scroll list down";
					Beep(600, 50);
					Sleep(50);
					setTextBGColor(WHITE);
					gotoxy(83, 12);
					cout << "ARROW DOWN - scroll list down";
					if (page + 1 < list.getSize() - 6)
						++page;
				}
				goto __PRINTLIST__;
			}
			if (!isSearch) {
				if (c == ESC) {
					setTextColor(AQUA);
					setTextBGColor(YELLOW);
					gotoxy(83, 14);
					cout << "ESC - quit";
					Beep(800, 50);
					Sleep(50);
					setTextBGColor(WHITE);
					gotoxy(83, 14);
					cout << "ESC - quit";
					list.clear();
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
				if (isCurrectSearch) {
					list = content;
					isCurrectSearch = false;
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
					list = content;
					goto __PRINTLIST__;
				}
				if (c == '\r') {
					page = 0;
					list.removeIf([input](string s)-> bool {return indexOf(input, s) == -1; });
					isCurrectSearch = true;
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
				else if (c != 0 && input.length() < 29) {
					gotoxy(83 + input.length(), 4);
					cout << c;
					input.push_back(c);
					if (input.length() == 1) {
						gotoxy(84, 4);
						cout << setFill(28);
						gotoxy(83 + input.length(), 4);
					}
				}
			}
			if (!isSearch) {
			__PRINTLIST__:
				createBox(1, 3, 80, 27, WHITE);
				setTextBGColor(WHITE);
				setTextColor(BLACK);
				printListTransPerPage(page, list);
			}
		}
	}
	






	//----------------------------------------------------------------------------------------------------
	
	_getch();
}

bool ATM::changePassword(User& user) {
LOGIN:
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	printArt(17, 0, "./art/NameBank.txt", RED, YELLOW);


	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, LIGHT_GREEN);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', WHITE, LIGHT_BLUE);
	setTextBGColor(YELLOW);
	printArt(17, 0, "./art/UserMenu.txt", RED, YELLOW);

	drawBorder(g_initMenuX + 24, g_initMenuY + 3, 29, 3, 1, RED, LIGHT_GREEN);
	gotoxy(g_adminMenuX + 24 + 7, g_adminMenuY + 4);
	setTextColor(RED);
	setTextBGColor(LIGHT_GREEN);
	cout << "NHAP MA PIN MOI";
	int userInputY = g_loginRectY + 6;

	short time = 1;
	string pw1 = "";
	string pw;

	POINT box[6] = {
		{g_loginRectX - 1, userInputY},
		{g_loginRectX + 7, userInputY},
		{g_loginRectX + 15, userInputY},
		{g_loginRectX + 23, userInputY},
		{g_loginRectX + 31, userInputY},
		{g_loginRectX + 39, userInputY}
	};
__INPUT_AGAIN__:
	if (time == 2) {
		pw1 = pw;
		gotoxy(g_adminMenuX + 24 + 7, g_adminMenuY + 4);
		setTextColor(RED);
		setTextBGColor(LIGHT_GREEN);
		cout << "NHAP LAI MA PIN";
	}

__WRONGINPUT__:

	pw = "";
	for (int i = 0; i < 6; ++i) {
		createBox(box[i].x, box[i].y, 3, 2, GRAY);
	}

	gotoxy(passInputX - 12, passInputY - 1);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "BACK - Esc";

	gotoxy(passInputX + 19, passInputY - 1);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "LOGIN - Enter";


	/***************************************************************

							KEYBOARD EVENT

	****************************************************************/

	while (true) {
		showCursor(false);
		if (_kbhit()) {
			char c = _getch();
			if (c == ESC) {
				gotoxy(passInputX - 12, passInputY - 1);
				setTextBGColor(RED);
				setTextColor(LIGHT_GREEN);
				cout << " BACK - Esc ";
				showCursor(false);
				Beep(800, 50);
				Sleep(50);
				return false;
			}
			if (c == 0 || c == 224)
				c = _getch();

			if (c == '\r') {
			__ENTERLOGIN__:
				if (pw.length() < 6) {
					Beep(1000, 200);
					setTextBGColor(LIGHT_GREEN);
					setTextColor(RED);
					gotoxy(passInputX - 2, passInputY - 4);
					cout << "Khong duoc bo trong PIN!";
					showCursor(false);
					_getch();
					gotoxy(passInputX - 2, passInputY - 4);
					cout << "                         ";
					showCursor(false);
				}
				else if (time == 2 || (pw != "123456" && !isCurrect(user, pw))) {
					gotoxy(passInputX + 19, passInputY - 1);
					setTextBGColor(LIGHT_RED);
					setTextColor(LIGHT_BLUE);
					cout << "LOGIN - Enter";
					Beep(800, 50);
					Sleep(50);
					gotoxy(passInputX + 19, passInputY - 1);
					setTextBGColor(LIGHT_GREEN);
					setTextColor(LIGHT_BLUE);
					cout << "LOGIN - Enter";
					if (time < 2) {
						++time;
						goto __INPUT_AGAIN__;
					}
					else if (pw == pw1) {
						if (confirmProcess("Ban co chac muon doi ma PIN ?")) {
							user._password = encoding(pw);
							listAccount.saveCard("./data/TheTu.txt");
							createBox(g_adminMenuX, g_adminMenuY + 3, g_adminMenuWidth, 7, AQUA);
							gotoxy((g_adminMenuWidth / 2 + g_adminMenuX) - 7, g_adminMenuY + 6);
							setTextBGColor(AQUA);
							setTextColor(BLACK);
							cout << "DA DOI MA PIN";
							showCursor(false);
							_getch();
							return true;
						}
					}
					else {
						Beep(1000, 200);
						gotoxy(passInputX - 1, passInputY - 4);
						setTextBGColor(LIGHT_GREEN);
						setTextColor(RED);
						cout << "     Ma PIN khong khop!";
						showCursor(false);
						_getch();
						showCursor(true);
						gotoxy(passInputX - 1, passInputY - 4);
						cout << "                       ";
						goto __WRONGINPUT__;
					}
					return false;
				}
				else {
					Beep(1000, 200);
					gotoxy(passInputX - 1, passInputY - 4);
					setTextBGColor(LIGHT_GREEN);
					setTextColor(RED);
					cout << "Khong duoc doi PIN mac dinh!";
					showCursor(false);
					_getch();
					showCursor(true);
					gotoxy(passInputX - 1, passInputY - 4);
					cout << "                            ";
				}
				continue;
			}
			else if (c == '\b') {
				if (!pw.empty()) {
					Beep(600, 50);
					createBox(box[pw.length() - 1].x, box[pw.length() - 1].y, 3, 2, GRAY);
					pw.pop_back();
				}
			}
			else if (isNumber(c) && pw.length() < 6) {
				Beep(600, 50);
				drawNut(box[pw.length()].x, box[pw.length()].y, BLACK, GRAY);
				pw.push_back(c);
				showCursor(false);
			}

		}
	}
}

bool ATM::inputPassword(User& user) {
LOGIN:
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	printArt(17, 0, "./art/NameBank.txt", RED, YELLOW);


	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, LIGHT_GREEN);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', WHITE, LIGHT_BLUE);
	setTextBGColor(YELLOW);
	printArt(17, 0, "./art/UserMenu.txt", RED, YELLOW);

	drawBorder(g_initMenuX + 24, g_initMenuY + 3, 29, 3, 1, RED, LIGHT_GREEN);
	gotoxy(g_adminMenuX + 24 + 9, g_adminMenuY + 4);
	setTextColor(RED);
	setTextBGColor(LIGHT_GREEN);
	cout << "NHAP MA PIN";
	int userInputY = g_loginRectY + 6;

	POINT box[6] = {
		{g_loginRectX - 1, userInputY},
		{g_loginRectX + 7, userInputY},
		{g_loginRectX + 15, userInputY},
		{g_loginRectX + 23, userInputY},
		{g_loginRectX + 31, userInputY},
		{g_loginRectX + 39, userInputY}
	};

	for (int i = 0; i < 6; ++i) {
		createBox(box[i].x, box[i].y, 3, 2, GRAY);
	}

	gotoxy(passInputX - 12, passInputY - 1);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "BACK - Esc";

	gotoxy(passInputX + 19, passInputY - 1);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "LOGIN - Enter";


	/***************************************************************

							KEYBOARD EVENT

	****************************************************************/
	string pw;
	while (true) {
		showCursor(false);
		if (_kbhit()) {
			char c = _getch();
			if (c == ESC) {
				gotoxy(passInputX - 12, passInputY - 1);
				setTextBGColor(RED);
				setTextColor(LIGHT_GREEN);
				cout << " BACK - Esc ";
				showCursor(false);
				Beep(800, 50);
				Sleep(50);
				return false;
			}
			if (c == 0 || c == 224)
				c = _getch();

			if (c == '\r') {
			__ENTERLOGIN__:
				if (pw.length() < 6) {
					Beep(1000, 200);
					setTextBGColor(LIGHT_GREEN);
					setTextColor(RED);
					gotoxy(passInputX - 2, passInputY - 4);
					cout << "Khong duoc bo trong PIN!";
					showCursor(false);
					_getch();
					gotoxy(passInputX - 2, passInputY - 4);
					cout << "                         ";
					showCursor(false);
				}
				else if (isCurrect(user, pw)) {
					gotoxy(passInputX + 19, passInputY - 1);
					setTextBGColor(LIGHT_RED);
					setTextColor(LIGHT_BLUE);
					cout << "LOGIN - Enter";
					Beep(800, 50);
					Sleep(50);
					wrongTime = 0;
					return true;
				}
				else {
					if (++wrongTime == 3) {
						setConsoleBackgroundColor(BACKGROUND_RED);
						clrscr();
						listIdBlocked.addTail(user._id);
						listIdBlocked.save("./data/AccountBlocked/ALL.txt");
						listAccount.~ListAccount();
						listAdmin.~ListAdministrator();
						listIdBlocked.~LinkedList();
						setTextBGColor(RED);
						setTextColor(YELLOW);
						gotoxy(userInputX, userInputY - 5);
						cout << "!!!BAN DA NHAP SAI QUA NHIEU LAN!!!";
						gotoxy(userInputX, userInputY - 4);
						cout << " DE DAM BAO AN TOAN CHO KHACH HANG";
						gotoxy(userInputX, userInputY - 3);
						cout << "********TAI KHOAN DA BI KHOA*******";
						while (++wrongTime <= 25) {
							Beep(1200, 200);
							Sleep(100);
						}
						exit(0);
					}
					else {
						Beep(1000, 200);
						gotoxy(passInputX - 2, passInputY - 4);
						setTextBGColor(LIGHT_GREEN);
						setTextColor(RED);
						cout << "Ban da nhap sai mat khau!";
						showCursor(false);
						_getch();
						showCursor(true);
						gotoxy(passInputX - 2, passInputY - 4);
						cout << "                         ";
					}
				}
				continue;
			}
			else if (c == '\b') {
				if (!pw.empty()) {
					Beep(600, 50);
					createBox(box[pw.length() - 1].x, box[pw.length() - 1].y, 3, 2, GRAY);
					pw.pop_back();
				}
			}
			else if (isNumber(c) && pw.length() < 6) {
				Beep(600, 50);
				drawNut(box[pw.length()].x, box[pw.length()].y, BLACK, GRAY);
				pw.push_back(c);
				showCursor(false);
			}

		}
	}




}

void ATM::userMenu(User& user) {
	if (isCurrect(user, "123456")) {
		if (!changePassword(user))
			return;
	}
__INIT__:
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	createBox(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, LIGHT_GREEN);
	drawBorder(g_adminMenuX, g_adminMenuY, g_adminMenuWidth, g_adminMenuHeight, '*', WHITE, LIGHT_BLUE);
	setTextBGColor(YELLOW);

	printArt(17, 0, "./art/UserMenu.txt", RED, YELLOW);
	/***********************************************

					CREATE BUTTON

	************************************************/

	POINT BUTTON[6] = {
		{g_adminMenuX + 6, g_adminMenuY + 2}, 	{g_adminMenuX + 40, g_adminMenuY + 2},
		{g_adminMenuX + 6, g_adminMenuY + 7},   {g_adminMenuX + 40, g_adminMenuY + 7},
		{g_adminMenuX + 6, g_adminMenuY + 13}, {g_adminMenuX + 40, g_adminMenuY + 13}
	};
	string nameButton[6]{
		"XEM THONG TIN TAI KHOAN",
		"RUT TIEN",
		"CHUYEN TIEN",
		"XEM NOI DUNG GIAO DICH",
		"DOI MA PIN",
		"DANG XUAT"
	};

	for (int i = 0; i < 6; ++i) {
		drawBorder(BUTTON[i].x, BUTTON[i].y, 28, 3, 1, BLACK, LIGHT_GREEN);
		gotoxy(BUTTON[i].x + 1 + (13 - nameButton[i].length() / 2), BUTTON[i].y + 1);
		cout << nameButton[i];
	}

	gotoxy(g_adminMenuX + 23 + 18, g_adminMenuY + 17);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_RED);
	cout << "UP/DOWN/RIGHT/LEFT ARROW TO MOVE";

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
				if (c == KEY_RIGHT || c == 32)
					if (++choose == 6)
						choose = 0;
				if (c == KEY_LEFT)
					if (--choose == -1)
						choose = 5;
				if (c == KEY_UP)
				{
					choose -= 2;
					choose = (choose < 0 ? (6 + choose) : choose);
				}
				if (c == KEY_DOWN)
				{
					choose += 2;
					choose = (choose > 5 ? (choose % 2) : choose);
				}
			}
			else if (c == '\r') {
				Beep(800, 50);
				switch (choose)
				{
				case 0: {
					printInfoUser(user);
					goto __INIT__;
					break;
				}
				case 1: {
					if (withrawMoney(user))
						goto __INIT__;
					else
						return;
					break;
				}
				case 2: {
					if (transfer(user))
						goto __INIT__;
					else
						return;
					break;
				}
				case 3: {
					printListTrans(user);
					goto __INIT__;
					break;
				}
				case 4: {
					if (inputPassword(user))
						changePassword(user);
					goto __INIT__;
					break;
				}
				case 5: {
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

void ATM::loginPasswordUser(User& user) {
LOGIN:
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	printArt(17, 0, "./art/NameBank.txt", RED, YELLOW);


	createBox(g_loginRectX, g_loginRectY, g_loginRectWidth, g_loginRectHeight, LIGHT_GREEN);
	printArt(g_loginRectX + 8, g_loginRectY, "./art/ATM.txt", RED, LIGHT_GREEN);
	drawBorder(g_loginRectX - 1, g_loginRectY - 1, g_loginRectWidth + 2, g_loginRectHeight + 2, '*', WHITE, LIGHT_BLUE);

	setTextColor(BLUE);
	setTextBGColor(LIGHT_GREEN);
	gotoxy(g_loginRectX + 15, g_loginRectY + 8);
	cout << "NHAP MA PIN";

	POINT box[6] = {
		{g_loginRectX + 6, userInputY},
		{g_loginRectX + 11, userInputY},
		{g_loginRectX + 16, userInputY},
		{g_loginRectX + 21, userInputY},
		{g_loginRectX + 26, userInputY},
		{g_loginRectX + 31, userInputY}
	};

	for (int i = 0; i < 6; ++i) {
		createBox(box[i].x, box[i].y, 3, 2, GRAY);
	}

	gotoxy(passInputX - 5, passInputY + 2);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "BACK - Esc";

	gotoxy(passInputX + 13, passInputY + 2);
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
	string pw;
	while (true) {
		showCursor(false);
		if (_kbhit()) {
			char c = _getch();
			if (c == ESC) {
				gotoxy(passInputX - 6, passInputY + 2);
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

			if (c == '\r') {
			__ENTERLOGIN__:
				if (pw.length() < 6) {
					Beep(1000, 200);
					setTextBGColor(LIGHT_GREEN);
					setTextColor(RED);
					gotoxy(passInputX - 2, passInputY);
					cout << "Khong duoc bo trong PIN!";
					showCursor(false);
					_getch();
					gotoxy(passInputX - 2, passInputY);
					cout << "                         ";
					showCursor(false);
				}
				else if (isCurrect(user, pw)) {
					gotoxy(passInputX + 13, passInputY + 2);
					setTextBGColor(LIGHT_RED);
					setTextColor(LIGHT_BLUE);
					cout << "LOGIN - Enter";
					Beep(800, 50);
					Sleep(50);
					wrongTime = 0;
					userMenu(user);
					return;
				}
				else {
					if (++wrongTime == 3) {
						setConsoleBackgroundColor(BACKGROUND_RED);
						clrscr();
						listIdBlocked.addTail(user._id);
						listIdBlocked.save("./data/AccountBlocked/ALL.txt");
						listAccount.~ListAccount();
						listAdmin.~ListAdministrator();
						listIdBlocked.~LinkedList();
						setTextBGColor(RED);
						setTextColor(YELLOW);
						gotoxy(userInputX - 2, userInputY - 5);
						cout << "!!!BAN DA NHAP SAI QUA NHIEU LAN!!!";
						gotoxy(userInputX - 2, userInputY - 4);
						cout << "!DE DAM BAO AN TOAN CHO KHACH HANG!";
						gotoxy(userInputX - 2, userInputY - 3);
						cout << "********TAI KHOAN DA BI KHOA*******";
						while (++wrongTime <= 25) {
							Beep(1200, 200);
							Sleep(100);
						}
						exit(0);
					}
					else {
						Beep(1000, 200);
						gotoxy(passInputX - 2, passInputY);
						setTextBGColor(LIGHT_GREEN);
						setTextColor(RED);
						cout << "Ban da nhap sai mat khau!";
						showCursor(false);
						_getch();
						showCursor(true);
						gotoxy(passInputX - 2, passInputY);
						cout << "                         ";
					}
				}
				continue;
			}
			else if (c == '\b') {
				if (!pw.empty()) {
					Beep(600, 50);
					createBox(box[pw.length() - 1].x, box[pw.length() - 1].y, 3, 2, GRAY);
					pw.pop_back();
				}
			}
			else if (isNumber(c) && pw.length() < 6) {
				Beep(600, 50);
				drawNut(box[pw.length()].x, box[pw.length()].y, BLACK, GRAY);
				pw.push_back(c);
				showCursor(false);
			}

		}
	}




}

void ATM::loginUserMenu() {
LOGIN:
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	printArt(17, 0, "./art/NameBank.txt", RED, YELLOW);


	createBox(g_loginRectX, g_loginRectY, g_loginRectWidth, g_loginRectHeight, LIGHT_GREEN);
	printArt(g_loginRectX + 8, g_loginRectY, "./art/ATM.txt", RED, LIGHT_GREEN);
	drawBorder(g_loginRectX - 1, g_loginRectY - 1, g_loginRectWidth + 2, g_loginRectHeight + 2, '*', WHITE, LIGHT_BLUE);

	setTextColor(BLUE);
	setTextBGColor(LIGHT_GREEN);
	gotoxy(g_loginRectX + 14, g_loginRectY + 8);
	cout << "USER LOGIN";


	gotoxy(userInputX - 4, userInputY);
	setTextBGColor(BLACK);
	setTextColor(BLUE);
	cout << "ID:                       ";



	gotoxy(passInputX - 5, passInputY + 2);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "BACK - Esc";



	gotoxy(passInputX + 13, passInputY + 2);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(LIGHT_BLUE);
	cout << "NEXT - Enter";

	gotoxy(g_loginRectX + 8, g_loginRectY + 18);
	setTextBGColor(LIGHT_GREEN);
	setTextColor(WHITE);
	cout << "BANG HAI TAC MU ROM BANK";

	/***************************************************************

							KEYBOARD EVENT

	****************************************************************/
	char c = '\0';
	string inputId = "";
	while (true) {
		showCursor(true);
		gotoxy(userInputX + inputId.length(), userInputY);
		if (_kbhit()) {
			setTextBGColor(BLACK);
			setTextColor(WHITE);
			c = _getch();

			if (c == ESC) {
				gotoxy(passInputX - 6, passInputY + 2);
				setTextBGColor(RED);
				setTextColor(LIGHT_GREEN);
				cout << " BACK - Esc ";
				showCursor(false);
				Beep(800, 50);
				Sleep(50);
				return;
			}
			if (c == 0 || c == 224 || c == -32) {
				c = _getch();
				c = '\0';
				continue;
			}

			if (c == '\r') {
				if (inputId.empty() || inputId.length() < 14) {
					Beep(1000, 200);
					setTextBGColor(LIGHT_GREEN);
					setTextColor(RED);
					gotoxy(userInputX - 2, userInputY + 1);
					if (inputId.empty())
						cout << "Khong duoc bo trong USER!";
					else
						cout << "ID phai du 14 chu so!";
					showCursor(false);
					_getch();
					showCursor(true);
					gotoxy(userInputX - 2, userInputY + 1);
					cout << "                         ";
					gotoxy(userInputX + inputId.length(), userInputY);
				}
				else {
					User& user = listAccount.getCurrentUser(inputId);
					if (user.getId() != "00000000000000") {
						if (listIdBlocked.search(user._id) != NULL) {
							Beep(1000, 200);
							setTextBGColor(LIGHT_GREEN);
							setTextColor(RED);
							gotoxy(userInputX - 2, userInputY + 1);
							cout << "Tai khoan da bi khoa!";
							showCursor(false);
							_getch();
							showCursor(true);
							gotoxy(userInputX - 2, userInputY + 1);
							cout << "                         ";
							gotoxy(userInputX + inputId.length(), userInputY);
						}
						else {
							gotoxy(passInputX + 13, passInputY + 2);
							setTextBGColor(LIGHT_RED);
							setTextColor(LIGHT_BLUE);
							cout << "NEXT - Enter";
							Beep(800, 50);
							showCursor(false);
							Sleep(50);
							loginPasswordUser(user);
							goto LOGIN;
						}
					}
					else {
						Beep(1000, 200);
						setTextBGColor(LIGHT_GREEN);
						setTextColor(RED);
						gotoxy(userInputX - 2, userInputY + 1);
						cout << "Tai khoan khong ton tai!";
						showCursor(false);
						_getch();
						showCursor(true);
						gotoxy(userInputX - 2, userInputY + 1);
						cout << "                         ";
						gotoxy(userInputX + inputId.length(), userInputY);
					}
				}
				continue;
			}
			else if (c == '\b') {
				if (!inputId.empty()) {
					cout << "\b  \b";
					inputId.pop_back();
				}
			}
			else if (c != 32 && c != '\n' && c != '\t' && c != '\0') {
				if (isNumber(c) && inputId.length() < 14) {
					cout << c;
					inputId = inputId + c;
				}
			}

		}
	}
}

ATM::ATM() {
	init();
}

ATM::~ATM() {
	listAccount.~ListAccount();
	listIdBlocked.~LinkedList();
	listAdmin.~ListAdministrator();
}

void ATM::runProcess() {
__INIT__:
	setConsoleBackgroundColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	clrscr();
	createBox(g_initMenuX, g_initMenuY, g_initMenuWidth, g_initMenuHeight, LIGHT_GREEN);
	drawBorder(g_initMenuX, g_initMenuY, g_initMenuWidth, g_initMenuHeight, '*', YELLOW, BLUE);
	setTextBGColor(YELLOW);
	printArt(17, 0, "./art/NameBank.txt", RED, YELLOW);

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
		gotoxy(BUTTON[i].x + (13 - nameButton[i].length() / 2), BUTTON[i].y + 1);
		cout << nameButton[i];
	}
	short choose = 0;
	int lenLarge = g_initMenuWidth;
	int runWord = 0, runWordL = 0;


	int jump = 0, move = 0;
	string stringMoving = "A1@BC2#DE$F4G6%H7I&7JK5*L8 M!9NO#-P0Q3~R4S6T7U2VW8SYZ";
	string magicString[2] = {
		"     NGAN HANG BANG HAI TAC MU ROM   ",
		"TIEN PHONG - SANG TAO - CHUYEN DOI SO"
	};
	string jumpString = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	string runLargeName[6];
	ifstream fin("./art/FullNameBank.txt");
	for (int i = 0; i < 6; ++i) {
		getline(fin, runLargeName[i]);
		runLargeName[i] = setFill(79) + runLargeName[i];
		runLargeName[i] = runLargeName[i] + setFill(79);
	}
	fin.close();
	while (true) {
		setTextBGColor(BLACK);
		gotoxy(g_initMenuX + 19, g_initMenuY + 15);
		if (move++ < stringMoving.size()) {
			char c = stringMoving[move - 1];
			for (int k = 0; k < 38; ++k) {
				if (c == magicString[jump][k] || jumpString[k] == magicString[jump][k])
					jumpString[k] = magicString[jump][k];
				else
					jumpString[k] = stringMoving[rand() % 53];
			}
			for (char& f : jumpString) {
				short r;
				do {
					r = rand() % 15;
				} while (r == BLACK);
				setTextColor(GRAY);
				cout << f;
			}
			//Sleep(100);
		}
		else if (move >= 70) {
			move = 0;
			jump = (jump == 0 ? 1 : 0);
		}


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
			if (c == ESC) {
				Beep(800, 50);
				goto __LOGOUT__;
			}
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
					__LOGOUT__:
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