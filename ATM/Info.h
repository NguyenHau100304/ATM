#pragma once

#include <string.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>
using std::string;
using std::cout;

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
	void setAmount(float);
	void setType(string);
	friend std::istream& operator>> (std::istream&, Money&);
	friend std::ostream& operator<< (std::ostream&, Money);
};


int maxOfDay[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

class DateTime {
	int _h, _m, _s;
	int _day;
	int _month;
	int _year;
	static const int MAX_OF_YEAR = 3000;
public:
	DateTime();
	DateTime(const DateTime&);
	~DateTime();
	int getSecond();
	int getMinute();
	int getHour();
	int getDay();
	int getMonth();
	int getYear();
	void display();
	friend std::istream& operator>> (std::istream&, DateTime&);
	friend std::ostream& operator<< (std::ostream&, DateTime);
};

DateTime::DateTime() {
	std::time_t now;
	std::time(&now);
	std::tm localTime;
	if (localtime_s(&localTime, &now) == 0) {
		_s = localTime.tm_sec;
		_m = localTime.tm_min;
		_h = localTime.tm_hour;
		_day = localTime.tm_mday;
		_month = localTime.tm_mon + 1;
		_year = localTime.tm_year + 1900;
	}
}
DateTime::DateTime(const DateTime& d) {
	_s = d._s;
	_m = d._m;
	_h = d._h;
	_day = d._day;
	_month = d._month;
	_year = d._year;
}
DateTime::~DateTime(){}
int DateTime::getSecond() {
	return _s;
}
int DateTime::getMinute() {
	return _m;
}
int DateTime::getHour() {
	return _h;
}
int DateTime::getDay() {
	return _day;
}
int DateTime::getMonth() {
	return _month;
}
int DateTime::getYear() {
	return _year;
}
void DateTime::display() {
	cout << _h << ':' << _m << ':' << _s << ' ' << _day << '/' << _month << '/' << _year << '\n';
}
std::istream& operator>> (std::istream& in, DateTime& d) {
	std::string s;
	std::getline(in, s);
	for (char& c : s)
		if (c < '0' || c > '9')
			c = 32;
	std::stringstream ss(s);
	int i = 0;
	while (ss >> s) {
		switch (i++)
		{
		case 0:
			d._h = stoi(s);
			break;
		case 1:
			d._m = stoi(s);
			break;
		case 2:
			d._s = stoi(s);
			break;
		case 3:
			d._day = stoi(s);
			break;
		case 4:
			d._month = stoi(s);
			break;
		case 5:
			d._year = stoi(s);
			break;
		default:
			break;
		}
	}
	return in;
}
std::ostream& operator<< (std::ostream& out, DateTime d) {
	out << d._h << ':' << d._m << ':' << d._s << ' ' << d._day << '/' << d._month << '/' << d._year << '\n';
	return out;
}


using namespace std;

Name::Name() : _fullname("No Name") {}

Name::Name(const Name& _cpyName) {
	this->_fullname = _cpyName._fullname;
	this->formatName();
}

Name::Name(string _strName) {
	this->_fullname = _strName;
	this->formatName();
}

void Name::formatName() {
	for (char& c : this->_fullname)
		c = toupper(c);

	while (this->_fullname[0] == 32)
		this->_fullname.erase(0, 1);

	while (this->_fullname[this->_fullname.length() - 1] == 32)
		this->_fullname.pop_back();

	for (int i = 0; i < this->_fullname.length() - 1; ++i)
		if (this->_fullname[i] == 32 && this->_fullname[i + 1] == 32) {
			this->_fullname.erase(i, 1);
			--i;
		}

}

string Name::getFirstName() {
	for (int i = this->_fullname.length() - 1; i >= 0; --i)
		if (_fullname[i] == 32)
			return _fullname.substr(i + 1);
	return this->_fullname;
}

string Name::getLastName() {
	for (int i = 0; i < this->_fullname.length(); ++i)
		if (_fullname[i] == 32)
			return _fullname.substr(0, i);
	return this->_fullname;
}

string Name::getFullName() {
	return this->_fullname;
}


istream& operator>> (istream& _is, Name& _name) {
	getline(_is, _name._fullname);
	_name.formatName();
	return _is;
}

ostream& operator<< (ostream& _os, Name _name) {
	_os << _name.getFullName();
	return _os;
}


bool Name::operator< (Name _b) {
	string a = this->getFirstName(), b = _b.getFirstName();
	if (a != b)
		return a < b;
	else {
		a = this->getLastName();
		b = _b.getLastName();
		return a < b;
	}
	return false;
}



Money::Money() : _amount(0), _type("VND") {}

Money::Money(float _amnt, string _strType) {
	_type = _strType;
	if (_type == "USD")
		_amount = _amnt * 24580;
	else
		_amount = _amnt;
}



Money::Money(const Money& _m) {
	_amount = _m._amount;
	_type = _m._type;
}

float Money::getAmount() {
	return this->_amount;
}

float Money::getMoney() {
	if (_type == "USD")
		return float(_amount / 24580);
	else
		return _amount;
}

void Money::setType(string s) {
	_type = s;
}

string Money::getType() {
	return this->_type;
}

void Money::setAmount(float m) {
	_amount += m;
}

istream& operator>> (istream& _is, Money& _money) {
	_is >> _money._amount >> _money._type;
	if (_money._type == "USD")
		_money._amount = _money._amount * 24580;
	return _is;
}

ostream& operator<< (ostream& _os, Money _money) {
	string s = std::to_string(_money.getMoney());
	if (s[0] == '-')
		s.erase(0, 1);
	int start = s.length();
	while (s[--start] != '.');

	int length = s.length();
	for (int i = start - 3; i > 0; i -= 3) {
		s.insert(i, ".");
	}
	while (s[s.length() - 3] != '.')
		s.erase(s.length() - 1, 1);
	s[s.length() - 3] = ',';
	_os << (_money.getAmount() < 0 ? '-' : '\0') << s << " " << _money._type;
	return _os;
}

