#pragma once
#include<iostream>
#define INF 1e6

using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;


template <class DataType>
class LinkedList;


template <class DataType>
class Node {
	friend class LinkedList<DataType>;
	friend class ListAccount;
	friend class ListTransaction;
	friend class ListAdministrator;
private:
	DataType _data;
	Node* _pNext;
public:
	Node(DataType data);
	void display();
	DataType& getData();
	Node<DataType>* getNext();
	Node<DataType>& operator++ ();
	friend std::ostream& operator<< (std::ostream&, Node<DataType>&);
};



template <class DataType>
class LinkedList {
	friend class ListAdministrator;
	friend class ListAccount;
	friend class ListTransaction;
private:
	Node<DataType>* _pHead;
	Node<DataType>* _pTail;
	int _iSize;
public:
	LinkedList();
	LinkedList(LinkedList<DataType>& other);
	~LinkedList();
	void load(string path);
	void save(string path);
	void addHead(DataType data);
	void addTail(DataType data);
	Node<DataType>* getHead();
	Node<DataType>* getTail();
	void addAfter(Node<DataType>* node, DataType data);
	Node<DataType>* search(DataType data);
	Node<DataType>* searchPre(Node<DataType>* node);
	void removeHead();
	void removeTail();
	void remove(DataType data);
	void removeNode(Node<DataType>* node);
	void removeAfter(DataType data);
	void removeIf(bool (*func)(DataType));
	void removeAt(int index);
	float getAvg();
	void selectionSort();
	void sortIf(bool (*func)(DataType, DataType));
	int getSize();
	void display();
	void displayIf(bool (*func)(DataType));
	void printList();
	void clear();
	void getElementAtPosition(int index);
	Node<DataType>* operator [] (int index);

	LinkedList<DataType> createFilterList(bool (*func)(DataType));

	void removeFirstIf(DataType a);

	int countElement(DataType data);

	void removeDuplicates();

	void interchangeSort();

	void input();
	DataType findMin();
	DataType findMax();

	void insertAfter(DataType p, DataType q);
	void appendList(LinkedList<DataType>& otherList);

	bool operator== (LinkedList<DataType> list);
	LinkedList<DataType>& operator= (const LinkedList<DataType>& list);
};








template <class DataType>
Node<DataType>::Node(DataType data) {
	_data = data;
	_pNext = NULL;
}
template <class DataType>
Node<DataType>& Node<DataType>::operator++ () {
	if (_pNext) {
		this = this->_pNext;
	}
	return *this;
}
template <class DataType>
Node<DataType>* Node<DataType>::getNext() {
	return _pNext;
}

template <class DataType>
DataType& Node<DataType>::getData() {
	return _data;
}

template <class DataType>
ostream& operator<< (ostream& _os, Node<DataType>& p) {
	_os << p._data;
	return _os;
}
template <class DataType>
void Node<DataType>::display() {
	cout << _data << ' ';
}



template <class DataType>
LinkedList<DataType>::LinkedList() {
	_pHead = _pTail = NULL;
	_iSize = 0;
}

template <class DataType>
LinkedList<DataType>::LinkedList(LinkedList<DataType>& other) {
	_pHead = _pTail = NULL;
	_iSize = 0;

	Node<DataType>* current = other._pHead;
	while (current) {
		addTail(current->_data);
		current = current->_pNext;
	}
}


template <class DataType>
LinkedList<DataType>::~LinkedList() {
	while (_pHead != NULL) {
		Node<DataType>* temp = _pHead;
		_pHead = _pHead->_pNext;
		delete temp;
	}
}
template <class DataType>
void LinkedList<DataType>::load(string path) {
	clear();
	ifstream fin(path);
	if (fin.is_open()) {
		DataType temp;
		while (getline(fin, temp))
			addHead(temp);
	}
	else
		throw runtime_error("Cannot open file");
}

template <class DataType>
void LinkedList<DataType>::save(string path) {
	ofstream fout(path);
	if (fout.is_open()) {
		Node<DataType>* curr = _pHead;
		while (curr) {
			fout << curr->_data << '\n';
			curr = curr->_pNext;
		}
	}
	else
		throw runtime_error("Cannot open file");
}


template <class DataType>
Node<DataType>* LinkedList<DataType>::getHead() {
	return _pHead;
}
template <class DataType>
Node<DataType>* LinkedList<DataType>::getTail() {
	return _pTail;
}

template <class DataType>
void LinkedList<DataType>::addHead(DataType data) {
	Node<DataType>* pAdd = new Node<DataType>(data);

	if (_pHead == NULL) {
		_pHead = _pTail = pAdd;

	}
	else {
		pAdd->_pNext = _pHead;
		_pHead = pAdd;
	}
	++_iSize;
}

template <class DataType>
void LinkedList<DataType>::addTail(DataType data) {
	Node<DataType>* pAdd = new Node<DataType>(data);
	if (_pHead == NULL)
		_pHead = _pTail = pAdd;
	else {
		_pTail->_pNext = pAdd;
		_pTail = pAdd;
	}
	++_iSize;

}

template <class DataType>
void LinkedList<DataType>::addAfter(Node<DataType>* node, DataType data) {
	Node<DataType>* pAdd = new Node<DataType>(data);
	if (node != NULL) {
		pAdd->_pNext = node->_pNext;
		node->_pNext = pAdd;
		if (node == _pTail)
			_pTail = pAdd;
	}
	else
		addHead(pAdd);
	++_iSize;
}

template<class DataType>
Node<DataType>* LinkedList<DataType>::search(DataType data) {
	Node<DataType>* current = _pHead;
	while (current) {
		if (current->_data == data) {
			return current;
		}
		current = current->_pNext;
	}
	return NULL;
}

template<class DataType>
Node<DataType>* LinkedList<DataType>::searchPre(Node<DataType>* node) {
	Node<DataType>* p = _pHead;
	if (p == node)
		return NULL;
	while ((p != NULL) && (p->_pNext != node))
		p = p->_pNext;
	return p;
}



template<class DataType>
void LinkedList<DataType>::removeHead() {
	if (_pHead != NULL) {
		Node<DataType>* pTemp = _pHead;
		_pHead = _pHead->_pNext;
		delete pTemp;
		if (_pHead == NULL)
			_pTail = NULL;
		--_iSize;
	}
}

template<class DataType>
void LinkedList<DataType>::removeTail() {
	if (_pHead == NULL)
		return;
	Node<DataType>* pTemp = _pTail;
	_pTail = searchPre(_pTail);
	delete pTemp;
	if (_pTail != NULL)
		_pTail->_pNext = NULL;
	else
		_pHead = NULL;
	--_iSize;
}

template<class DataType>
void LinkedList<DataType>::remove(DataType data) {
	Node<DataType>* pWalker = _pHead, * pTemp = NULL;
	while ((pWalker != NULL) && (pWalker->_data != data)) {
		pTemp = pWalker;
		pWalker = pWalker->_pNext;
	}
	if (pWalker == NULL)
		return;
	if (pTemp != NULL) {
		if (pWalker == _pTail) {
			_pTail = pTemp;
			_pTail->_pNext = NULL;
		}
		pTemp->_pNext = pWalker->_pNext;
		delete pWalker;
		--_iSize;
	}
}

template<class DataType>
void LinkedList<DataType>::removeAfter(DataType q) {
	Node<DataType>* current = _pHead;

	while (current) {
		if (current->_data == q && current->_pNext) {
			Node<DataType>* nodeToRemove = current->_pNext;
			current->_pNext = nodeToRemove->_pNext;
			delete nodeToRemove;
			_iSize--;
			return;
		}
		current = current->_pNext;
	}
}




template<class DataType>
void LinkedList<DataType>::removeIf(bool (*func)(DataType)) {
	Node<DataType>* current = _pHead;
	Node<DataType>* previous = NULL;

	while (current) {
		if (func(current->_data)) {
			if (current == _pHead) {
				removeHead();
				current = _pHead;
			}
			else if (current == _pTail) {
				removeTail();
				current = NULL;
			}
			else {
				previous->_pNext = current->_pNext;
				delete current;
				current = previous->_pNext;
				_iSize--;
			}
		}
		else {
			previous = current;
			current = current->_pNext;
		}
	}
}

template<class DataType>
void LinkedList<DataType>::removeFirstIf(DataType a) {
	Node<DataType>* current = _pHead;
	Node<DataType>* previous = NULL;

	while (current) {
		if (current->_data > a) {
			if (current == _pHead) {
				removeHead();
				current = _pHead;
			}
			else if (current == _pTail) {
				removeTail();
				current = NULL;
			}
			else {
				previous->_pNext = current->_pNext;
				delete current;
				current = previous->_pNext;
				_iSize--;
				break;
			}
		}
		else {
			previous = current;
			current = current->_pNext;
		}
	}
}


template<class DataType>
void LinkedList<DataType>::clear() {
	while (_pHead != NULL)
		removeHead();
	_iSize = 0;
}

template<class DataType>
void LinkedList<DataType>::selectionSort() {
	if (_pHead) {
		Node<DataType>* current = _pHead;
		while (current) {
			Node<DataType>* minNode = current;
			Node<DataType>* temp = current->_pNext;
			while (temp) {
				if (temp->_data < minNode->_data) {
					minNode = temp;
				}
				temp = temp->_pNext;
			}

			DataType tempData = current->_data;
			current->_data = minNode->_data;
			minNode->_data = tempData;
			current = current->_pNext;
		}
	}
}
template<class DataType>
void LinkedList<DataType>::sortIf(bool (*func)(DataType, DataType)) {
	if (_pHead) {
		Node<DataType>* current = _pHead;
		while (current) {
			Node<DataType>* minNode = current;
			Node<DataType>* temp = current->_pNext;
			while (temp) {
				if (func(temp->_data, minNode->_data)) {
					minNode = temp;
				}
				temp = temp->_pNext;
			}

			DataType tempData = current->_data;
			current->_data = minNode->_data;
			minNode->_data = tempData;
			current = current->_pNext;
		}
	}
}


template<class DataType>
int LinkedList<DataType>::getSize() {
	return _iSize;
}

template<class DataType>
void LinkedList<DataType>::getElementAtPosition(int index) {
	if (index < 0 || index >= _iSize) {
		// Invalid index
		return;
	}

	Node<DataType>* current = _pHead;
	for (int i = 0; i < index; i++) {
		current = current->_pNext;
	}

	cout << "\tElement at position " << index << ": " << current->_data << std::endl;
}

template<class DataType>
Node<DataType>* LinkedList<DataType>::operator [] (int index) {
	if (index < 0 || index >= _iSize) {
		// Invalid index
		return NULL;
	}

	Node<DataType>* current = _pHead;
	for (int i = 0; i < index; i++) {
		current = current->_pNext;
	}

	return current;
}
template<class DataType>
void LinkedList<DataType>::display() {

	if (_pHead != NULL) {
		Node<DataType>* current = _pHead;
		while (current) {
			cout << current->_data;
			current = current->_pNext;
			if (current)
				cout << "->";
		}
		cout << std::endl;
	}
}
template<class DataType>
void LinkedList<DataType>::displayIf(bool (*func)(DataType)) {
	Node<DataType>* current = _pHead;
	bool isFirst = true;
	while (current) {
		if (func(current->_data)) {
			if (isFirst)
				isFirst = false;
			else
				cout << "->";
			cout << current->_data;
		}
		current = current->_pNext;
	}
	cout << std::endl;
}


template<class DataType>
void LinkedList<DataType>::removeAt(int index) {
	if (index < 0 || index >= _iSize) {
		return;
	}

	if (index == 0) {
		removeHead();
	}
	else if (index == _iSize - 1) {
		removeTail();
	}
	else {
		Node<DataType>* current = _pHead;
		for (int i = 0; i < index - 1; i++) {
			current = current->_pNext;
		}

		Node<DataType>* nodeToRemove = current->_pNext;
		current->_pNext = nodeToRemove->_pNext;
		delete nodeToRemove;
		_iSize--;
	}
}

template<class DataType>
float LinkedList<DataType>::getAvg() {
	if (_pHead != NULL) {
		float sum = 0;
		Node<DataType>* current = _pHead;
		while (current) {
			sum += current->_data;
			current = current->_pNext;
		}
		return (float)sum / _iSize;
	}
	return -INF;
}


template<class DataType>
int LinkedList<DataType>::countElement(DataType data) {
	int count = 0;
	Node<DataType>* current = _pHead;

	while (current) {
		if (current->_data == data) {
			count++;
		}
		current = current->_pNext;
	}

	return count;
}

template<class DataType>
void LinkedList<DataType>::removeDuplicates() {
	if (!_pHead) {
		return;
	}

	Node<DataType>* current = _pHead;

	while (current) {
		Node<DataType>* runner = current;

		while (runner->_pNext) {
			if (current->_data == runner->_pNext->_data) {
				Node<DataType>* nodeToRemove = runner->_pNext;
				runner->_pNext = runner->_pNext->_pNext;
				delete nodeToRemove;
				_iSize--;
			}
			else {
				runner = runner->_pNext;
			}
		}

		current = current->_pNext;
	}
}

template<class DataType>
void LinkedList<DataType>::interchangeSort() {
	Node<DataType>* current = _pHead;

	while (current) {
		Node<DataType>* nextNode = current->_pNext;

		while (nextNode) {
			if (current->_data > nextNode->_data) {
				DataType temp = current->_data;
				current->_data = nextNode->_data;
				nextNode->_data = temp;
			}
			nextNode = nextNode->_pNext;
		}

		current = current->_pNext;
	}
}

template<class DataType>
void LinkedList<DataType>::input() {
	int n;
	cout << "\tEnter the number of elements: ";
	cin >> n;
	clear();
	for (int i = 0; i < n; i++) {
		DataType data;
		cout << "\tEnter element " << i + 1 << ": ";
		cin >> data;
		addTail(data);
	}
}
template<class DataType>
DataType LinkedList<DataType>::findMin() {
	if (_pHead) {


		DataType minData = _pHead->_data;
		Node<DataType>* current = _pHead->_pNext;

		while (current) {
			if (current->_data < minData) {
				minData = current->_data;
			}
			current = current->_pNext;
		}

		return minData;
	}
}


template<class DataType>
DataType LinkedList<DataType>::findMax() {
	if (_pHead) {


		DataType maxData = _pHead->_data;
		Node<DataType>* current = _pHead->_pNext;

		while (current) {
			if (current->_data > maxData) {
				maxData = current->_data;
			}
			current = current->_pNext;
		}

		return maxData;
	}
}



template<class DataType>
void LinkedList<DataType>::insertAfter(DataType p, DataType q) {
	Node<DataType>* current = _pHead;

	while (current) {
		if (current->_data == q) {
			Node<DataType>* newNode = new Node<DataType>(p);
			newNode->_pNext = current->_pNext;
			newNode->_pNext = current->_pNext;
			current->_pNext = newNode;
			_iSize++;
			return;
		}
		current = current->_pNext;
	}
	cout << "\tKhong tim thay phan tu co gia tri " << q << "!\n";
}

template<class DataType>
void LinkedList<DataType>::appendList(LinkedList<DataType>& otherList) {
	if (!_pHead) {
		_pHead = otherList._pHead;
	}
	else if (otherList._pHead) {
		_pTail->_pNext = otherList._pHead;
	}

	if (otherList._pTail) {
		_pTail = otherList._pTail;
	}

	_iSize += otherList._iSize;
	otherList._pHead = otherList._pTail = NULL;
	otherList._iSize = 0;
}

template<class DataType>
bool LinkedList<DataType>::operator== (LinkedList<DataType> list) {
	if (_iSize != list._iSize)
		return false;
	Node<DataType>* current1 = _pHead;
	Node<DataType>* current2 = list._pHead;

	while (current1 || current2) {
		if (current1->_data != current2->_data)
			return false;
		current1 = current1->_pNext;
		current2 = current2->_pNext;
	}
	return true;
}


template <class DataType>
void LinkedList<DataType>::printList() {
	Node<DataType>* current = _pHead;
	while (current) {
		current->_data.display();
		current = current->_pNext;
	}
}
template <class DataType>
LinkedList<DataType> LinkedList<DataType>::createFilterList(bool (*func)(DataType)) {
	LinkedList newList;
	Node<DataType>* curr = _pHead;
	while (curr) {
		if (func(curr->_data))
			newList.addTail(curr->_data);
		curr = curr->_pNext;
	}
	return newList;
}
template <class DataType>
void LinkedList<DataType>::removeNode(Node<DataType>* node) {
	Node<DataType>* nodeToRemove = node->_pNext;
	node->_pNext = nodeToRemove->_pNext;
	delete nodeToRemove;
	_iSize--;
}
template <class DataType>
LinkedList<DataType>& LinkedList<DataType>::operator= (const LinkedList<DataType>& list) {
	clear();
	_pHead = _pTail = NULL;
	_iSize = 0;

	Node<DataType>* current = list._pHead;
	while (current) {
		addTail(current->_data);
		current = current->_pNext;
	}
	return *this;
}

