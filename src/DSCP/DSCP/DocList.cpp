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
		head = new DocList_Node(*(c.head)); //递归值拷贝
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
		if (x->nxt == nullptr || x->nxt->Times < Times) { //找到合适的插入位置：保持链表有序
			tmp->nxt = x->nxt;
			x->nxt = tmp;
			break;
		}
		x = x->nxt;
	}
}

int DocList::Remove(int DocID) {
	int ret = 0;
	/*x 当前文档， y上一个文档*/
	DocList_Node *x = head, *y = nullptr;
	if (head == nullptr) return 0;
	while (x != nullptr) {
		if (x->DocID == DocID) { //找到该文档
			/*删除并保持链表完整*/
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
	//查找文档
	DocList_Node *x = head;
	while (x != nullptr) {
		if (x->DocID == DocID) // 查到该文档
			return x;
		x = x->nxt;
	}
	//未查到
	return nullptr;
}

int DocList::Edit(int DocID, int Times) {
	//实现方法： 先删除， 后添加
	int ret = Times - Remove(DocID);
	Add(DocID, Times);
	return ret;
}
