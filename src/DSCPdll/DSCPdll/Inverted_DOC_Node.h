#pragma once

#include "wCharString.h"
#include "DocList.h"

class Inverted_DOC;

class Inverted_DOC_Node {
public:
	Inverted_DOC_Node(int color_,int TermID_, int size_, Inverted_DOC_Node*, Inverted_DOC_Node*, Inverted_DOC_Node*, wCharString&);
	~Inverted_DOC_Node();

	void insert(int DocID, int Times);
	void value_copy(Inverted_DOC_Node*);
	void Edit(int, int);
	void Remove(int);
	DocList* get_doclist() const;
	friend class Inverted_DOC;
private:
	wCharString Term;
	int TermID, DF, Occur, color, size;
	Inverted_DOC_Node *son[2], *p;
	DocList *doclist;
};

inline DocList* Inverted_DOC_Node::get_doclist() const { return doclist; }