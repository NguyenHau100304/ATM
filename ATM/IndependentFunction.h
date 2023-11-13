#pragma once

#include "Handles.h";

string setfill(int n) {
	string s = "";
	while (n--)
		s = s + ' ';
	return s;
}

bool compareUserbyName(User a, User b) {
	return a.getName() < b.getName();
}

bool compareUserbyMoney(User a, User b) {
	return a.getAmount().getAmount() < b.getAmount().getAmount();
}

bool isNumber(char c) {
	return c >= '0' && c <= '9';
}

