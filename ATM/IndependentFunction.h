#pragma once

#include "Handles.h";
#include <cstdlib>
#include <ctime>

int getRandomNumber() {
	unsigned int n;
	for (int i = 0; i < 500; ++i) {
		n = std::rand() % 10;
	}
	return n;
}

string getRandomId() {
	string id = "";
	for (int i = 0; i < 14; ++i)
		id = id + char(getRandomNumber() + 48);
	return id;
}

string setFill(int n) {
	string s = "";
	while (n--)
		s = s + ' ';
	return s;
}


bool compareUserbyName(User a, User b) {
	return a.getName() < b.getName();
}

bool compareUserbyMoney(User a, User b) {
	return a.getAmount().getAmount() > b.getAmount().getAmount();
}

bool compareUserbyNameGreater(User a, User b) {
	return !(a.getName() < b.getName());
}

bool compareUserbyMoneyGreater(User a, User b) {
	return a.getAmount().getAmount() < b.getAmount().getAmount();
}


bool isNumber(char c) {
	return c >= '0' && c <= '9';
}

bool isWord(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

