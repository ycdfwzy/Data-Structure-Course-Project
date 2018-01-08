#include "Inverted_DOC.h"

#define red 0
#define black 1

Inverted_DOC::Inverted_DOC() {
	NIL = new Inverted_DOC_Node(black, -1, 0, NIL, NIL, NIL, wCharString(""));
	root = NIL;
	size = 0;
}

Inverted_DOC::~Inverted_DOC(){
	delete root;
}

void Inverted_DOC::rotate(Inverted_DOC_Node *x, int K) {
	Inverted_DOC_Node *y = x->p;
	if (y != root) {
		if (y->p->son[0] == y)
			y->p->son[0] = x;
		else y->p->son[1] = x;
	}
	x->p = y->p;
	y->son[K] = x->son[K ^ 1];
	if (x->son[K ^ 1] != NIL)
		x->son[K ^ 1]->p = y;
	y->p = x; x->son[K ^ 1] = y;
	if (root == y) root = x;
	NIL->size = 0;
	if (y != NIL)
		y->size = y->son[0]->size + y->son[1]->size + 1;
	if (x != NIL)
		x->size = x->son[0]->size + x->son[1]->size + 1;
}

Inverted_DOC_Node* Inverted_DOC::Insert(wCharString &Term, int TermID, int DocID, int Times) {
	Inverted_DOC_Node *x = root;
	Inverted_DOC_Node *y = NIL;
	while (x != NIL) {
		y = x;
		if (x->Term == Term) {
			x->insert(DocID, Times);
			return x;
		}
		x = x->son[(x->Term<Term)];
	}
	Inverted_DOC_Node *z = new Inverted_DOC_Node(red, TermID, 1, y, NIL, NIL, Term);
	z->insert(DocID, Times);
	if (y == NIL)
		root = z;
	else
		y->son[(y->Term<Term)] = z;

	Inverted_DOC_Node *zz = z;
	while (zz != root) {
		if (zz != NIL)
			zz->size = zz->son[0]->size + zz->son[1]->size + 1;
		zz = zz->p;
	}

	//Insert_Fixup(z);
	Adjust(1, z);
	size++;
	return z;
}

void Inverted_DOC::Insert_Fixup(Inverted_DOC_Node *z) {
	while (z != root && z->p->color == red) {
		int t = (z->p->p->son[0] == z->p);
		Inverted_DOC_Node *y = z->p->p->son[t];
		if (y->color == red) {    //case1
			y->color = black;
			z->p->color = black;
			y->p->color = red;
			z = y->p;
		}
		else {
			if (z->p->son[t] == z) {  //case2
				rotate(z, t);
				z = z->son[t ^ 1];
			}
			z->p->color = black;  //case3
			z->p->p->color = red;
			rotate(z->p, t ^ 1);
		}
	}
	root->color = black;

}

void Inverted_DOC::Remove(Inverted_DOC_Node *z) {
	Inverted_DOC_Node *x, *y;
	if (z->son[0] == NIL || z->son[1] == NIL)
		y = z;
	else y = successor(z);
	if (y->son[0] != NIL)
		x = y->son[0];
	else x = y->son[1];
	x->p = y->p;
	if (y->p == NIL)
		root = x;
	else if (y->p->son[0] == y)
		y->p->son[0] = x;
	else y->p->son[1] = x;

	Inverted_DOC_Node *xx = x;
	while (xx != root) {
		if (xx != NIL)
			xx->size = xx->son[0]->size + xx->son[1]->size + 1;
		xx = xx->p;
	}

	if (y != z) z->value_copy(y);
	if (y->color == black)
		//Remove_Fixup(x);
		Adjust(1, x);

	y->son[0] = y->son[1] = nullptr;
	delete y;
	size--;
}

void Inverted_DOC::Remove_Fixup(Inverted_DOC_Node *x) {
	while (x != root && x->color == black) {
		int t = (x == x->p->son[0]);
		Inverted_DOC_Node *w = x->p->son[t];
		if (w->color == red) {
			x->p->color = red;
			w->color = black;
			rotate(w, t);
			w = x->p->son[t];
		}
		if (w->son[0]->color == black && w->son[1]->color == black) {
			if (w != NIL)
				w->color = red;
			x = x->p;
		}
		else
		{
			if (w->son[t]->color == black) {
				w->color = red;
				w->son[t ^ 1]->color = black;
				rotate(w->son[t ^ 1], t ^ 1);
				w = x->p->son[t];
			}
			w->color = w->p->color;
			w->son[t]->color = black;
			w->p->color = black;
			rotate(w, t);
			x = root;
		}
	}
	x->color = black;
}

void Inverted_DOC::Adjust(int K, Inverted_DOC_Node *z) {
	if (K == 0) Insert_Fixup(z);
	else Remove_Fixup(z);
}

void Inverted_DOC::Edit(wCharString &c, int DocID, int Times) {
	
}

Inverted_DOC_Node * Inverted_DOC::search(wCharString &c) {
	Inverted_DOC_Node *ret = root;
	while (ret != NIL) {
		if (ret->Term == c)
			break;
		if (ret->Term < c)
			ret = ret->son[1];
		else ret = ret->son[0];
	}
	return ret;
}

Inverted_DOC_Node * Inverted_DOC::successor(Inverted_DOC_Node * z) {
	Inverted_DOC_Node *x = z->son[1];
	if (x == NIL) {
		x = z;
		while (x != root && x->p->son[1] == x)
			x = x->p;
		if (x == root) return NIL;
		return x->p;
	}
	while (x->son[0] != NIL)
		x = x->son[0];
	return x;
}

Inverted_DOC_Node * Inverted_DOC::precursor(Inverted_DOC_Node * z) {
	Inverted_DOC_Node *x = z->son[0];
	if (x == NIL) {
		x = z;
		while (x != root && x->p->son[0] == x)
			x = x->p;
		if (x == root) return NIL;
		return x->p;
	}
	while (x->son[1] != NIL)
		x = x->son[1];
	return x;
}

Inverted_DOC_Node * Inverted_DOC::operator[](wCharString &c){
	return search(c);
}
