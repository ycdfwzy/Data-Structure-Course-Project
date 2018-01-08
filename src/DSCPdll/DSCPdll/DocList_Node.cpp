#include "DocList_Node.h"



DocList_Node::DocList_Node(int DocID_, int Times_):
              DocID(DocID_), Times(Times_), nxt(nullptr){ }

DocList_Node::DocList_Node(DocList_Node &c) {
	DocID = c.DocID;
	Times = c.Times;
	if (c.nxt != nullptr)
		nxt = new DocList_Node(*(c.nxt));
	else nxt = nullptr;
}

DocList_Node::~DocList_Node() {
	if (nxt != nullptr)
		delete nxt;
}

DocList_Node & DocList_Node::operator=(const DocList_Node &c) {
	DocID = c.DocID;
	Times = c.Times;
	if (nxt != nullptr) delete nxt;
	if (c.nxt != nullptr)
		nxt = new DocList_Node(*(c.nxt));
	else nxt = nullptr;
	return *this;
}
