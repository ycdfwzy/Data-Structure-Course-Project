#include "DocList.h"



DocList::DocList(int TermID_):
           TermID(TermID_), head(nullptr){ }

DocList::DocList(DocList &c) {
	TermID = c.TermID;
	head = new DocList_Node(*(c.head));
}

DocList::~DocList(){
	if (head != nullptr)
		delete head;
}

DocList & DocList::operator=(const DocList &c) {
	TermID = c.TermID;
	if (head != nullptr)
		head = new DocList_Node(*(c.head));
	else delete head;
	return *this;
}

void DocList::Add(int DocID, int Times) {
	DocList_Node* tmp = new DocList_Node(DocID, Times);
	if (head == nullptr || head->Times < Times) {
		tmp->nxt = head;
		head = tmp;
		return;
	}
	DocList_Node *x = head;
	if (Times > 1) {
		Times++;
		Times--;
	}
	while (x != nullptr) {
		if (x->nxt == nullptr || x->nxt->Times < Times) {
			tmp->nxt = x->nxt;
			x->nxt = tmp;
			break;
		}
		x = x->nxt;
	}
}

int DocList::Remove(int DocID) {
	int ret = 0;
	DocList_Node *x = head, *y = nullptr;
	if (head == nullptr) return 0;
	while (x != nullptr) {
		if (x->DocID == DocID) {
			if (x == head)
				head = x->nxt;
			else
				y->nxt = x->nxt;
			ret = x->Times;
			x->nxt = nullptr;
			delete x;
			break;
		}
		y = x;
		x = x->nxt;
	}
	return ret;
}

DocList_Node* DocList::Search(int DocID) {
	DocList_Node *x = head;
	while (x != nullptr) {
		if (x->DocID == DocID)
			return x;
		x = x->nxt;
	}
	return nullptr;
}

int DocList::Edit(int DocID, int Times) {
	int ret = Times - Remove(DocID);
	Add(DocID, Times);
	return ret;
}
