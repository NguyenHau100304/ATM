#include "Handles.h"
using namespace std;

Admin::Admin() : _id("Admin"), _password("123456") {}

Admin::Admin(string _strId, string _strPw) : _id(_strId), _password(_strPw){}

Admin::~Admin(){}

string Admin::getUser() {
	return this->_id;
}

User::User() : _id("00000000000000"), _password("123456"), _fullname(Name()), _money(Money()){}

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

string User::getName() {
	return _fullname.getFullName();
}

Money User::getAmount() {
	return this->_money;
}


bool User::operator< (User _a) {
	return this->_fullname < _a._fullname;
}



Transaction::Transaction(): _type("None") {}

Transaction::Transaction(string type) :_type(type) {}
Transaction::Transaction(const Transaction& tras) {
	_type = tras._type;
}

Transaction::~Transaction() {}



WithrawATM::WithrawATM() : Transaction("withrawatm"), _wrMoney() {
}

WithrawATM::WithrawATM(User user, Money mn) : Transaction("withrawatm"), _wrMoney(mn) {
}

WithrawATM::~WithrawATM(){}

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
	}else
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

Transfer::~Transfer(){}

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
		}else
			throw runtime_error("Cannot open file\n");
		curr = curr->getNext();
		fout.close();
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
		while(!fin.eof()){
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
	}else
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


