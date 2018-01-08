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
		head = new DocList_Node(*(c.head)); //�ݹ�ֵ����
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
/*	if (Times > 1) {
		Times++;
		Times--;
	}*/
	while (x != nullptr) {
		if (x->nxt == nullptr || x->nxt->Times < Times) { //�ҵ����ʵĲ���λ�ã�������������
			tmp->nxt = x->nxt;
			x->nxt = tmp;
			break;
		}
		x = x->nxt;
	}
}

int DocList::Remove(int DocID) {
	int ret = 0;
	/*x ��ǰ�ĵ��� y��һ���ĵ�*/
	DocList_Node *x = head, *y = nullptr;
	if (head == nullptr) return 0;
	while (x != nullptr) {
		if (x->DocID == DocID) { //�ҵ����ĵ�
			/*ɾ����������������*/
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
	//�����ĵ�
	DocList_Node *x = head;
	while (x != nullptr) {
		if (x->DocID == DocID) // �鵽���ĵ�
			return x;
		x = x->nxt;
	}
	//δ�鵽
	return nullptr;
}

int DocList::Edit(int DocID, int Times) {
	//ʵ�ַ����� ��ɾ���� �����
	int ret = Times - Remove(DocID);
	Add(DocID, Times);
	return ret;
}
