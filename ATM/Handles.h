#pragma once
#include <string>
#include "Display.h"
#include "Info.h"
#include "Structure.h"
#include <fstream>
#include <iomanip>
using std::ifstream;
using std::ofstream;
using std::setw;

class User;
class Admin;
bool isCurrent(const Admin, string);



class Admin {
	friend class ListAdministrator;
private:
	string _id;
	string _password;
public:
	Admin();
	Admin(string, string);
	Admin(const Admin&);
	~Admin();
	string getUser();
	friend bool isCurrent(const Admin, string);
};




class Transaction {
protected:
	friend class ListTransaction;
	string _type;
	
public:
	Transaction();
	Transaction(string);
	Transaction(const Transaction&);
	~Transaction();
	virtual void load(ifstream&) = NULL;
	virtual void save(ofstream&) = NULL;
};

class WithrawATM : public Transaction {
	friend class ListTransaction;
	Money _wrMoney;
	
public:
	WithrawATM();
	WithrawATM(User, Money);
	~WithrawATM();
	void save(ofstream&);
	void load(ifstream&);
	Money getMoney();
};

class Transfer : public Transaction {
	friend class ListTransaction;
	Money _trsmoney;
	string _targetId;
	
public:
	Transfer();
	Transfer(User, string, Money);
	~Transfer();
	void save(ofstream&);
	void load(ifstream&);
	Money getMoney();
	string getTargetId();
	User getTarget(ListAccount&);
};



/****************************************************************************************************

										    TEMP MEMORY

***************************************************************************************************/


class ListAdministrator {
	LinkedList<Admin> list;
	
public:
	ListAdministrator();
	~ListAdministrator();
	int getSize();
	void load(string);
	void save(string);
	Admin getAdministratorAt(int);
	Admin getAdministratorById(string);
};

class ListAccount {
	LinkedList<User> list;
public:
	ListAccount();
	~ListAccount();
	void append(User);
	int getSize();
	void load(string, string);
	void save(string);
	void saveCard(string);
	User getUserAt(int);
	User getUserById(string);
	bool isHasUser(string);
	void removeUserAt(int);
	void removeUserById(string);
	void display(int, int, short, short, LinkedList<string>&);
	void sortIf(bool (*func)(User, User)) {
		list.sortIf(func);
	}
};

class ListTransaction {
	LinkedList<Transaction*> list;

public:
	void load(string);
	void save(string);
	ListTransaction();
	ListTransaction(const ListTransaction&);
	~ListTransaction();
	int getSize();
};



class User {
	friend class ListAccount;
	friend class Transaction;
	friend class WithrawATM;
	friend class Transfer;
	friend class Card;
private:
	string _id;
	string _password;
	Name _fullname;
	Money _money;
	ListTransaction _trans;
public:
	User();
	User(string, string, Name, Money, bool);
	User(const User&);
	string getId();
	Name getName();
	Money getAmount();
	bool operator< (User);
};




using namespace std;

Admin::Admin() : _id("Admin"), _password("123456") {}

Admin::Admin(string _strId, string _strPw) : _id(_strId), _password(_strPw) {}
Admin::Admin(const Admin& a) {
	_id = a._id;
	_password = a._password;
}

Admin::~Admin() {}

string Admin::getUser() {
	return this->_id;
}

bool isCurrent(const Admin a, string pw) {
	if (a._password == pw)
		return true;
	return false;
}

User::User() : _id("00000000000000"), _password("123456"), _fullname(Name()), _money(Money()) {}

User::User(string _strId, string _pw, Name _newname, Money _mn, bool active) {
	_id = _strId;
	_password = _pw;
	_fullname = _newname;
	_money = _mn;
}

User::User(const User& cp) {
	_id = cp._id;
	_password = cp._password;
	_fullname = cp._fullname;
	_money = cp._money;
}

string User::getId() {
	return this->_id;
}

Name User::getName() {
	return _fullname;
}

Money User::getAmount() {
	return this->_money;
}



bool User::operator< (User _a) {
	return this->_fullname < _a._fullname;
}



Transaction::Transaction() : _type("None") {}

Transaction::Transaction(string type) :_type(type) {}
Transaction::Transaction(const Transaction& tras) {
	_type = tras._type;
}

Transaction::~Transaction() {}



WithrawATM::WithrawATM() : Transaction("withrawatm"), _wrMoney() {
}

WithrawATM::WithrawATM(User user, Money mn) : Transaction("withrawatm"), _wrMoney(mn) {
}

WithrawATM::~WithrawATM() {}

Money WithrawATM::getMoney() {
	return _wrMoney;
}

void WithrawATM::save(ofstream& fout) {
	if (fout.is_open()) {
		fout << _type << '\n';
		fout << _wrMoney << '\n';
	}
	else
		throw runtime_error("Cannot open file\n");
}

void WithrawATM::load(ifstream& fin) {
	if (fin.is_open()) {
		fin >> _wrMoney;
	}
	else
		throw runtime_error("Cannot open file\n");
}


void Transfer::save(ofstream& fout) {
	if (fout.is_open()) {
		fout << _type << '\n';
		fout << _targetId << '\n';
		fout << _trsmoney << '\n';
	}
	else
		throw runtime_error("Cannot open file\n");
}

void Transfer::load(ifstream& fin) {
	if (fin.is_open()) {
		fin.ignore();
		getline(fin, _targetId);
		fin >> _trsmoney;
	}
	else
		throw runtime_error("Cannot open file\n");
}


Transfer::Transfer() : Transaction("transfer"), _targetId(), _trsmoney() {
}

Transfer::Transfer(User user, string tar, Money mn) : Transaction("transfer"), _targetId(tar), _trsmoney(mn) {
}

Transfer::~Transfer() {}

Money Transfer::getMoney() {
	return this->_trsmoney;
}
string Transfer::getTargetId() {
	return _targetId;
}

User Transfer::getTarget(ListAccount& list) {
	return list.getUserById(_targetId);
}


ListAccount::ListAccount() : list() {}
ListAccount::~ListAccount() { list.~LinkedList(); }

int ListAccount::getSize() {
	return list._iSize;
}
User ListAccount::getUserAt(int index) {
	return list[index]->getData();
}
User ListAccount::getUserById(string id) {
	Node<User>* curr = list._pHead;

	while (curr) {
		if (curr->getData()._id == id)
			return curr->getData();
		curr = curr->_pNext;
	}
	return User();
}
bool ListAccount::isHasUser(string id) {
	Node<User>* curr = list._pHead;

	while (curr) {
		if (curr->getData()._id == id)
			return true;
		curr = curr->_pNext;
	}
	return false;
}

void ListAccount::removeUserAt(int index) {
	list.removeAt(index);
}
void ListAccount::removeUserById(string id) {
	Node<User>* curr = list._pHead;
	Node<User>* previous = NULL;
	while (curr) {
		if (curr->getData()._id == id) {
			if (curr == list._pHead) {
				list.removeHead();
				curr = list._pHead;
			}
			else if (curr == list._pTail) {
				list.removeTail();
				curr = NULL;
			}
			else {
				previous->_pNext = curr->_pNext;
				delete curr;
				curr = previous->_pNext;
				list._iSize--;
			}
			break;
		}
		else {
			previous = curr;
			curr = curr->_pNext;
		}
	}
}



void ListAccount::append(User a) {
	list.addTail(a);
}


void ListAccount::saveCard(string path) {
	ofstream fout(path);
	if (fout.is_open()) {
		Node<User>* curr = list.getHead();
		while (curr) {
			fout << curr->getData()._id << '\n'
				<< curr->getData()._password << '\n';
			curr = curr->getNext();
		}
	}
	else
		throw runtime_error("Cannot open file\n");
	fout.close();
}


void ListAccount::load(string path, string pathCard) {
	ifstream fin(pathCard);
	if (fin.is_open()) {
		string id, pw;
		while (getline(fin, id)) {
			getline(fin, pw);
			ifstream finAcc(path + id + ".txt");
			User temp;
			if (finAcc.is_open()) {
				getline(finAcc, temp._id);
				finAcc >> temp._fullname;
				temp._password = pw;
				finAcc >> temp._money;
				finAcc.ignore();
				list.addTail(temp);
			}
			finAcc.close();
		}
		//cout << "Daloadthanhcong";
	}
	else
		throw runtime_error("Cannot open file\n");

	fin.close();
}


void ListAccount::save(string path) {
	Node<User>* curr = list.getHead();
	while (curr) {
		ofstream fout(path + curr->getData()._id + ".txt");
		if (fout.is_open()) {
			fout << curr->getData()._id << '\n'
				<< curr->getData()._fullname << '\n'
				<< curr->getData()._money << '\n';
		}
		else
			throw runtime_error("Cannot open file\n");
		curr = curr->getNext();
		fout.close();
	}

}

void ListAccount::display(int start, int end, short x, short y, LinkedList<string> &listIdBlocked) {
	Node<User>* current = list._pHead;
	int index = 0;
		while (current) {
			if (index >= start && index <= end) {
				bool isBlock = false;
				if (listIdBlocked.search(current->_data._id))
				{
					isBlock = true;
					setTextColor(RED);
				}
				else {
					setTextColor(WHITE);
				}
				gotoxy(x + 1, y);
				cout << index + 1;
				gotoxy(x + 5, y);
				cout << current->_data._id;
				gotoxy(x + 20, y);
				cout << current->_data.getName();
				gotoxy(x + 45, y);
				cout << setw(19) << right << current->_data._money;
				gotoxy(x + 69, y);
				if (isBlock)
					cout << "KHOA";
				else
					cout << "HOAT DONG";
				++y;
			}
			current = current->_pNext;
			index++;
		}
}



ListTransaction::ListTransaction() : list() {}


ListTransaction::ListTransaction(const ListTransaction& newlist) {
	list = newlist.list;
}
ListTransaction::~ListTransaction() {
	list.~LinkedList();
}
int ListTransaction::getSize() {
	return list._iSize;
}





void ListTransaction::load(string path) {
	ifstream fin(path);

	if (fin.is_open()) {
		while (!fin.eof()) {
			string type;
			fin >> type;
			Transaction* temp;
			if (type == "withrawatm") {
				temp = new WithrawATM;
				temp->load(fin);
			}
			else {
				temp = new Transfer;
				temp->load(fin);
			}
			list.addTail(temp);
		}
	}
	else
		throw runtime_error("Cannot open file\n");
	fin.close();
}
void ListTransaction::save(string path) {
	ofstream fout(path);
	if (fout.is_open()) {
		Node<Transaction*>* curr = list._pHead;
		while (curr) {
			curr->_data->save(fout);
			curr = curr->_pNext;
		}
	}

	fout.close();
}




void ListAdministrator::load(string path) {
	ifstream fin(path);
	if (fin.is_open()) {
		while (!fin.eof()) {
			Admin temp;
			getline(fin, temp._id);
			getline(fin, temp._password);
			list.addTail(temp);
		}
	}
	else
		throw runtime_error("Cannot open file\n");
	fin.close();

}
void ListAdministrator::save(string path) {
	ofstream fout(path);
	if (fout.is_open()) {
		Node<Admin>* curr = list.getHead();
		while (curr) {
			fout << curr->getData()._id << '\n'
				<< curr->getData()._password << '\n';
			curr = curr->getNext();
		}
	}
	else
		throw runtime_error("Cannot open file\n");
	fout.close();
}
ListAdministrator::ListAdministrator() : list() {}
ListAdministrator::~ListAdministrator() {
	list.~LinkedList();
}
int ListAdministrator::getSize() {
	return list._iSize;
}
Admin ListAdministrator::getAdministratorAt(int index) {
	return list[index]->getData();
}
Admin ListAdministrator::getAdministratorById(string id) {
	Node<Admin>* curr = list._pHead;

	while (curr) {
		if (curr->getData()._id == id)
			return curr->getData();
		curr = curr->_pNext;
	}
	return Admin();
}


