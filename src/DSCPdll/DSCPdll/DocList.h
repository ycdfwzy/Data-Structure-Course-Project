#pragma once

#include "DocList_Node.h"
class Inverted_DOC_Node;
class DocList;

class DocList {
public:
	DocList(int);
	DocList(DocList&);
	~DocList();
	DocList& operator =(const DocList&);
	void Add(int ,int);
	int Remove(int);
	DocList_Node* Search(int);
	int Edit(int, int);
	DocList_Node* get_head() const;

	friend class Inverted_DOC_Node;
	friend class DocList;
private:
	int TermID;
	DocList_Node *head;
};

inline DocList_Node* DocList::get_head() const { return head; }
