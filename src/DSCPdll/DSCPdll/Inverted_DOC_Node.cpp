#include "Inverted_DOC_Node.h"



Inverted_DOC_Node::Inverted_DOC_Node(int color_, int TermID_, int size_, Inverted_DOC_Node* p_, Inverted_DOC_Node* son0, Inverted_DOC_Node* son1, wCharString& st):
                   color(color_), TermID(TermID_), size(size_), p(p_), Term(st){
	son[0] = son0;
	son[1] = son1;
	doclist = new DocList(TermID);
	DF = 0;
	Occur = 0;
}

Inverted_DOC_Node::~Inverted_DOC_Node() {
	if (son[0] != nullptr && son[0]->TermID >= 0)
		delete son[0];
	if (son[1] != nullptr && son[1]->TermID >= 0)
		delete son[1];
	if (doclist != nullptr)
		delete doclist;
}

void Inverted_DOC_Node::insert(int DocID, int Times) {
	/*
	DF++;
	Occur += Times;
	doclist->Add(DocID, Times);
	*/
	DocList_Node *t = doclist->Search(DocID);
	if (t == nullptr) {
		DF++;
		Occur += Times;
		doclist->Add(DocID, Times);
	}
	else
	{
		Occur += Times;
		doclist->Edit(DocID, t->Times+Times);
	}
}

void Inverted_DOC_Node::value_copy(Inverted_DOC_Node *z) {
	TermID = z->TermID;
	Term = z->Term;
	DF = z->DF;
	Occur = z->Occur;
	delete doclist;
	*(doclist) = *(z->doclist);
}

void Inverted_DOC_Node::Edit(int DocID, int Times) {
	Occur += doclist->Edit(DocID, Times);
}

void Inverted_DOC_Node::Remove(int DocID) {
	int t = doclist->Remove(DocID);
	Occur -= t;
	if (t > 0) DF--;
}
