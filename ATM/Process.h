#pragma once
#include "Handles.h"
#include "Display.h"
#include "Defines.h"
#include "GlobalVariable.h"
#include "FakeDatabaseServer.h"
#include <conio.h>
#include <fstream>
#include <string>
#include <cstdlib>







void init() {

	listAdmin.load("Admin.txt");
	listAccount.load("", "TheTu.txt");
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



void loginAdminMenu() {
	setConsoleBackgroundColor(BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	clrscr();
	printArt(17, 0, "NameBank.txt", RED, YELLOW);
	createBox(g_loginRectX, g_loginRectY, g_loginRectX + g_loginRectWidth, g_loginRectY + g_loginRectHeight, BLUE);
	printArt(g_loginRectX + 8, g_loginRectY, "ATM.txt", WHITE, BLUE);

	setTextColor(RED);
	gotoxy(g_loginRectX + 14, g_loginRectY + 7);
	cout << "ADMIN LOGIN";


	gotoxy(userInputX, userInputY);
	setTextBGColor(BLACK);
	setTextColor(RED);
	cout << "User:                         ";
	

	gotoxy(passInputX, passInputY);
	setTextBGColor(BLACK);
	setTextColor(RED);
	cout << "PIN:                          ";

	gotoxy(g_loginRectX + 5, g_loginRectY + 18);
	setTextBGColor(BLUE);
	setTextColor(WHITE);
	cout << "Ngan Hang TNHH 5TV Dip Do Bank";

	gotoxy(userInputX + 6, userInputY);



}

void loginUserMenu();

void adminMenu();

void userMenu();

void loadListUsers();

