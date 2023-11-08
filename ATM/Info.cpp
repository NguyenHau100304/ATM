#include "Info.h"

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
		this->_fullname.erase(0);

	while (this->_fullname[this->_fullname.length() - 1] == 32)
		this->_fullname.pop_back();

	for(int i = 0; i < this->_fullname.length() - 1; ++i)
		if (this->_fullname[i] == 32 && this->_fullname[i + 1] == 32) {
			this->_fullname.erase(i);
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
	int i = 0;
	while (i < a.length() && i < b.length()) {
		if (a[i] != b[i])
			return a[i] < b[i];
	}

	a = this->getLastName();
	b = _b.getLastName();
	i = 0;
	while (i < a.length() && i < b.length()) {
		if (a[i] != b[i])
			return a[i] < b[i];
	}
	return false;
}



Money::Money() : _amount(0), _type("VND") {}

Money::Money(float _amnt, string _strType) : _amount(_amnt), _type(_strType) {}

Money::Money(const Money& _m) {
	_amount = _m._amount;
	_type = _m._type;
}

float Money::getAmount() {
	return this->_amount;
}

float Money::getMoney() {
	if (_type == "USD")
		return roundf(float(_amount / 24.580) * 100) / 100;
	else
		return _amount;
}

string Money::getType() {
	return this->_type;
}

istream& operator>> (istream& _is, Money& _money) {
	_is >> _money._amount;
	return _is;
}

ostream& operator<< (ostream& _os, Money _money) {
	_os << _money.getMoney() << ' ' << _money._type;
	return _os;
}