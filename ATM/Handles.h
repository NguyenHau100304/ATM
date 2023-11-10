#pragma once
#include <string>
#include "Display.h"
#include "Info.h"
#include "Structure.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

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
	void removeUserAt(int);
	void removeUserById(string);
	void display(int, int, short, short);
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
	User(string, string, Name, Money);
	User(const User&);
	string getId();
	string getName();
	Money getAmount();
	bool operator< (User);
};




