#pragma once

#include <string>
#include <iostream>
#include <iomanip>
using std::string;

class Name {
	string _fullname;
public:
	Name();
	Name(const Name&);
	Name(string);
	void formatName();
	string getFirstName();
	string getLastName();
	string getFullName();
	friend std::istream& operator>> (std::istream&, Name&);
	friend std::ostream& operator<< (std::ostream&, Name);
	bool operator< (Name);
};


class Money {
	float _amount;
	string _type;
public:
	Money();
	Money(float, string);
	Money(const Money&);
	float getAmount();
	string getType();
	float getMoney();
	friend std::istream& operator>> (std::istream&, Money&);
	friend std::ostream& operator<< (std::ostream&, Money);
};