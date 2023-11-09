#pragma once

#include "Handles.h";

bool compareUserbyName(User a, User b) {
	return a.getName() < b.getName();
}

bool compareUserbyMoney(User a, User b) {
	return a.getAmount().getAmount() < b.getAmount().getAmount();
}


