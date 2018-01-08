#include "wCharStringLink.h"

wCharStringLink::wCharStringLink() {
	head = nullptr;
	size = 0;
}

wCharStringLink::wCharStringLink(const wCharStringLink &c) {
	if (c.head == nullptr) head = nullptr;
		else head = new node<wCharString>(*c.head);
	size = c.size;
}

wCharStringLink::~wCharStringLink() {
	if (head != nullptr) delete head;
}

void wCharStringLink::add(wCharString &c, int pos) {
	if (pos == -1) pos = size;
	if (pos > size) pos = size;
	if (pos == 0) {
		head = new node<wCharString>(c, head, nullptr);
		size++;
		return;
	}
	node<wCharString> *tmp = head;
	while (pos > 1) {
		tmp = tmp->getnext();
		pos--;
	}
	node<wCharString> *t = new node<wCharString>(c, tmp->getnext(), tmp);
	if (t->getnext() != nullptr) t->getnext()->setprev(t);
	tmp->setnext(t);
	size++;
}

void wCharStringLink::remove(int pos) {
	if (pos < 0) return;
	if (pos >= size) return;
	node<wCharString> *tmp = head;
	while (pos--)
		tmp = tmp->getnext();
	
	if (tmp == head) head = head->getnext();

	if (tmp->getprev() != nullptr) tmp->getprev()->setnext(tmp->getnext());
	if (tmp->getnext() != nullptr) tmp->getnext()->setprev(tmp->getprev());
	tmp->setnext(nullptr);
	tmp->setprev(nullptr);
	delete tmp;
	--size;
}

void wCharStringLink::remove(wCharString &c) {
	node<wCharString> *tmp = head;
	while (tmp != nullptr) {
		if (tmp->getvalue() == c) {
			//delete
			if (tmp->getprev() != nullptr) tmp->getprev()->setnext(tmp->getnext());
			if (tmp->getnext() != nullptr) tmp->getnext()->setprev(tmp->getprev());
			node<wCharString> *t = tmp->getnext();
			tmp->setnext(nullptr);
			tmp->setprev(nullptr);
			delete tmp;
			--size;
			tmp = t;
		} else
			tmp = tmp->getnext();
	}
}

int wCharStringLink::search(wCharString &c) const{
	node<wCharString> *tmp = head;
	int index = 0;
	while (tmp != nullptr) {
		if (tmp->getvalue() == c)
			return index;
		index++;
		tmp = tmp->getnext();
	}
	return -1;
}

int wCharStringLink::search(const wchar_t *c) const {
	wCharString *t = new wCharString(c);
	node<wCharString> *tmp = head;
	int index = 0;
	while (tmp != nullptr) {
		if (tmp->getvalue() == *t)
			return index;
		index++;
		tmp = tmp->getnext();
	}
	return -1;
}

wCharString wCharStringLink::operator[](unsigned int index) {
	if (index < 0) index = 0;
	if (index >= size) index = size - 1;
	node<wCharString> *tmp = head;
	while (index--)
		tmp = tmp->getnext();
	//tmp->getvalue();
	return tmp->getvalue();
}

std::wostream& operator <<(std::wostream &os, wCharStringLink &c) {
	node<wCharString> *tmp = c.head;
	while (tmp != nullptr) {
		if (tmp->getnext() == nullptr)
			os << tmp->getvalue();
		else os << tmp->getvalue() << L" ";
		tmp = tmp->getnext();
	}
	return os;
}
