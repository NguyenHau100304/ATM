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

string withdraw(int amount) {
	int denominations[] = { 500000, 200000, 100000, 50000 };

	int count[6]; 
	for (int i = 0; i < 6; ++i)
		count[i] = 0;
	string s;
	for (int i = 0; i < 4; ++i) {
		count[i] = amount / denominations[i];
		amount %= denominations[i];

		if (count[i] > 0) {
			for (int j = 0; j < count[i]; ++j)
				s = s + to_string(denominations[i]) + ' ';
		}
	}
	return s;
}