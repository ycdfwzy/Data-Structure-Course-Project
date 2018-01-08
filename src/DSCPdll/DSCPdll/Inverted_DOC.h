#pragma once
#include "wCharString.h"
#include "Inverted_DOC_Node.h"

class Inverted_DOC {
public:
	Inverted_DOC();
	~Inverted_DOC();

	void rotate(Inverted_DOC_Node*, int);
	Inverted_DOC_Node* Insert(wCharString&, int, int, int);
	void Insert_Fixup(Inverted_DOC_Node*);
	void Remove(Inverted_DOC_Node*);
	void Remove_Fixup(Inverted_DOC_Node*);
	void Adjust(int K, Inverted_DOC_Node*);
	void Edit(wCharString&, int, int);
	Inverted_DOC_Node* search(wCharString&);
	Inverted_DOC_Node* successor(Inverted_DOC_Node* z);
	Inverted_DOC_Node* precursor(Inverted_DOC_Node* z);
	Inverted_DOC_Node* operator [](wCharString&);
	Inverted_DOC_Node* getNIL()const;
	int getsize()const;
private:
	Inverted_DOC_Node *root, *NIL;
	int size;
};

inline Inverted_DOC_Node* Inverted_DOC::getNIL()const { return NIL; }

inline int Inverted_DOC::getsize()const {
	return size;
}
