#pragma once
#include <string>
#include "Display.h"
#include "Info.h"
#include "Structure.h"
#include "EncodingPassword.h"
#include <fstream>
#include <iomanip>
using std::ifstream;
using std::ofstream;
using std::setw;


class User;
class Admin;




bool isCurrent(const Admin, string);
bool isCurrent(const User, string);
int indexOf(string f, string s);
bool isHas(User& user, string find);


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
	friend class ListTransaction;
	friend class ATM;
protected:
	DateTime _time;
	string _type;
public:
	Transaction();
	Transaction(string, DateTime);
	Transaction(const Transaction&);
	~Transaction();
	DateTime getDateTime();
	virtual void load(ifstream&) = NULL;
	virtual void save(ofstream&) = NULL;
};

class WithrawATM : public Transaction {
	friend class ListTransaction;
	Money _wrMoney;
public:
	WithrawATM();
	WithrawATM(Money);
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
	Transfer(string, Money);
	~Transfer();
	void save(ofstream&);
	void load(ifstream&);
	Money getMoney();
	string getTargetId();
	User getTarget(ListAccount&);
};

class BeTransfer : public Transaction {
	friend class ListTransaction;
	Money _trsmoney;
	string _targetId;
public:
	BeTransfer();
	BeTransfer(string, Money);
	~BeTransfer();
	void save(ofstream&);
	void load(ifstream&);
	Money getMoney();
	string getTargetId();
};


/****************************************************************************************************

										    LIST CLASS

***************************************************************************************************/


class ListAdministrator {
	friend class ATM;
private:
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
	friend class ATM;
	friend class Transaction;
private:
	LinkedList<User> list;
	User& getCurrentUser(string);
	void updatePriceUser(string, int);
	void transfer(string, string, int);
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
	ListAccount searching(string find);
	void sortIf(bool (*func)(User, User)) {
		list.sortIf(func);
	}
};

class ListTransaction {
	friend class ATM;
private:
	LinkedList<Transaction*> list;
public:
	void load(string);
	void save(string);
	ListTransaction();
	ListTransaction(const ListTransaction&);
	~ListTransaction();
	int getSize();
	void append(Transaction*);
};



class User {
	friend class ATM;
	friend class Transaction;
	friend class WithrawATM;
	friend class Transfer;
	friend class BeTransfer;
	friend class ListTransaction;
	friend class ListAccount;
private:
	string _id;
	string _password;
	Name _fullname;
	Money _money;
	ListTransaction _trans;
	void saveTransaction(string);
public:
	User();
	User(string, string, Name, Money);
	User(const User&);
	string getId();
	Name getName();
	Money getAmount();
	bool operator< (User);
	friend bool isCurrent(const User, string);
};


/***********************************************************************************************

								    DEFINE OBJECT

************************************************************************************************/




using namespace std;

Admin::Admin() : _id("none"), _password("123456") {}

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
	if (decoding(a._password) == pw)
		return true;
	return false;
}

bool isCurrent(const User a, string pw) {
	if (decoding(a._password) == pw)
		return true;
	return false;
}


User::User() : _id("00000000000000"), _password("123456"), _fullname(Name()), _money(Money()) {}

User::User(string _strId, string _pw, Name _newname, Money _mn) {
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



Transaction::Transaction() : _type("None"), _time() {}

Transaction::Transaction(string type, DateTime now) :_type(type), _time(now) {}
Transaction::Transaction(const Transaction& tras) {
	_type = tras._type;
	_time = tras._time;
}

Transaction::~Transaction() {}

DateTime Transaction::getDateTime() {
	return _time;
}


WithrawATM::WithrawATM() : Transaction("withrawatm", DateTime()), _wrMoney() {
}

WithrawATM::WithrawATM(Money mn) : Transaction("withrawatm", DateTime()), _wrMoney(mn) {
}

WithrawATM::~WithrawATM() {}

Money WithrawATM::getMoney() {
	return _wrMoney;
}

void WithrawATM::save(ofstream& fout) {
	if (fout.is_open()) {
		fout << _type << '\n';
		fout << _time;
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
		fout << _time;
		fout << _targetId << '\n';
		fout << _trsmoney << '\n';
	}
	else
		throw runtime_error("Cannot open file\n");
}

void Transfer::load(ifstream& fin) {
	if (fin.is_open()) {
		fin >> _targetId;
		fin >> _trsmoney;
	}
	else
		throw runtime_error("Cannot open file\n");
}


Transfer::Transfer() : Transaction("transfer", DateTime()), _targetId(), _trsmoney() {
}

Transfer::Transfer(string tar, Money mn) : Transaction("transfer", DateTime()), _targetId(tar), _trsmoney(mn) {
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

//----

void BeTransfer::save(ofstream& fout) {
	if (fout.is_open()) {
		fout << _type << '\n';
		fout << _time;
		fout << _targetId << '\n';
		fout << _trsmoney << '\n';
	}
	else
		throw runtime_error("Cannot open file\n");
}

void BeTransfer::load(ifstream& fin) {
	if (fin.is_open()) {
		fin >> _targetId;
		fin >> _trsmoney;
	}
	else
		throw runtime_error("Cannot open file\n");
}


BeTransfer::BeTransfer() : Transaction("betransfer", DateTime()), _targetId(), _trsmoney() {
}

BeTransfer::BeTransfer(string tar, Money mn) : Transaction("betransfer", DateTime()), _targetId(tar), _trsmoney(mn) {
}

BeTransfer::~BeTransfer() {}

Money BeTransfer::getMoney() {
	return this->_trsmoney;
}
string BeTransfer::getTargetId() {
	return _targetId;
}



ListAccount::ListAccount() : list() {}
ListAccount::~ListAccount() { list.~LinkedList(); }

int ListAccount::getSize() {
	return list._iSize;
}
User ListAccount::getUserAt(int index) {
	return list[index]->getData();
}

User& ListAccount::getCurrentUser(string id) {
	Node<User>* curr = list._pHead;

	while (curr) {
		if (curr->getData()._id == id)
			return curr->_data;
		curr = curr->_pNext;
	}
	return *(new User());
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
				<< decoding(curr->getData()._password) << '\n';
			curr = curr->getNext();
		}
	}
	else
		throw runtime_error("Cannot open file\n");
	fout.close();
}


void ListAccount::load(string path, string pathCard) {
	ifstream fin(pathCard);
	list.clear();
	if (fin.is_open()) {
		string id, pw;
		while (getline(fin, id)) {
			getline(fin, pw);
			ifstream finAcc(path + id + ".txt");
			User temp;
			if (finAcc.is_open()) {
				getline(finAcc, temp._id);
				finAcc >> temp._fullname;
				temp._password = encoding(pw);
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
				<< curr->getData()._money.getMoney() << ' '
				<< curr->getData()._money.getType() << '\n';
		}
		else
			throw runtime_error("Cannot open file\n");
		curr = curr->getNext();
		fout.close();
	}

}

ListAccount ListAccount::searching(string find) {
	ListAccount filter;
	Node<User>* curr = list._pHead;
	while (curr) {
		if (isHas(curr->_data, find)) {
			filter.append(curr->_data);
		}
		curr = curr->_pNext;
	}
	return filter;
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
					setTextColor(BLACK);
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


void ListAccount::updatePriceUser(string id, int money) {
	User& user = getCurrentUser(id);
	user._money.setAmount(money);
	Transaction* tras;
	if (user._money.getType() == "USD")
		tras = new WithrawATM(Money(float(money / 24580), "USD"));
	else
		tras = new WithrawATM(Money(money, "VND"));
	user._trans.append(tras);
	user._trans.save("./data/TransactionHistory/LichSu" + user._id + ".txt");
}
void ListAccount::transfer(string id1, string id2, int m) {
	User& user1 = getCurrentUser(id1);
	User& user2 = getCurrentUser(id2);
	user1._money.setAmount(-m);
	user2._money.setAmount(m);
	Transaction* trasU1;
	if (user1._money.getType() == "USD")
		trasU1 = new Transfer(id2, Money(float(m / 24580), "USD"));
	else
		trasU1 = new Transfer(id2, Money(m, "VND"));
	user1._trans.append(trasU1);
	Transaction* trasU2;
	if (user2._money.getType() == "USD")
		trasU2 = new BeTransfer(id1, Money(float(m / 24580), "USD"));
	else
		trasU2 = new BeTransfer(id1, Money(m, "VND"));
	user2._trans.append(trasU2);
	user1._trans.save("./data/TransactionHistory/LichSu" + user1._id + ".txt");
	user2._trans.save("./data/TransactionHistory/LichSu" + user2._id + ".txt");
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

void ListTransaction::append(Transaction* tran) {
	list.addHead(tran);
}

void ListTransaction::load(string path) {
	ifstream fin(path);
	list.clear();
	if (fin.is_open()) {
		while (!fin.eof()) {
			string type;
			DateTime time;
			getline(fin, type);
			fin >> time;
			Transaction* temp;
			if (type == "withrawatm") {
				temp = new WithrawATM;
				temp->load(fin);
			}
			else if(type == "transfer") {
				temp = new Transfer;
				temp->load(fin);
			}
			else {
				temp = new BeTransfer;
				temp->load(fin);
			}
			temp->_type = type;
			temp->_time = time;
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
	list.clear();
	if (fin.is_open()) {
		while (!fin.eof()) {
			Admin temp;
			getline(fin, temp._id);
			getline(fin, temp._password);
			temp._password = encoding(temp._password);
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
				<< decoding(curr->getData()._password) << '\n';
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


int indexOf(string f, string s) {
	if (f.length() > s.length())
		return -1;
	if (f == s)
		return 0;
	for (int i = 0; i < s.length() - f.length() + 1; ++i)
		if (f == s.substr(i, f.length()))
			return i;
	return -1;
}


bool isHas(User& user, string find) {
	if (indexOf(find, user.getId()) != -1)
		return true;
	if (indexOf(find, user.getName().getFullName()) != -1)
		return true;
	return false;
}