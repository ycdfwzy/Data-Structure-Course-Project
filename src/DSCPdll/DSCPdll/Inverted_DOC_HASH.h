#pragma once

#include "wCharString.h"
#include "DocList.h"
#include "DocList_Node.h"

class Inverted_DOC_HASH
{
public:
	Inverted_DOC_HASH();
	~Inverted_DOC_HASH();

	void Insert(wCharString&, int, int);
	DocList* Search(wCharString&);
	void Edit(wCharString&, int, int);

private:
	static int HASHN;	//��ϣֵ
	static int HASHM;	//��ϣֵ
	wCharString *h[10000019];	//��ϣ��
	int DF[10000019], Occur[10000019];
	DocList *doclist[10000019];
};

