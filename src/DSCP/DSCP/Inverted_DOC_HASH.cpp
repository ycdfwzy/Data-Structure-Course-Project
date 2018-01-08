#include "Inverted_DOC_HASH.h"

int Inverted_DOC_HASH::HASHN = 1009;
int Inverted_DOC_HASH::HASHM = 10000019;
typedef long long LL;

Inverted_DOC_HASH::Inverted_DOC_HASH() {
	for (int i = 0; i < HASHM; ++i) {
		h[i] = nullptr;
		doclist[i] = nullptr;
	}
}


Inverted_DOC_HASH::~Inverted_DOC_HASH(){
	for (int i = 0; i < HASHM; ++i) {
		if (h[i] != nullptr) delete h[i];
		if (doclist[i] != nullptr) delete doclist[i];
	}
}

void Inverted_DOC_HASH::Insert(wCharString &c, int DocID, int Times) {
	int len = c.length();
	int hash = 0;
	//计算单词的哈希值
	for (int i = 0; i < len; ++i) {
		hash = ((LL)hash*HASHN + (LL)c[i]) % HASHM;
	}
	while (h[hash] != nullptr) {
		if (*h[hash] == c) break;
		hash++;
		if (hash == HASHM) hash = 0;
	}
	if (h[hash] == nullptr) {
		h[hash] = new wCharString(c);
		doclist[hash] = new DocList(hash);
	}

	DocList_Node *t = doclist[hash]->Search(DocID);
	if (t == nullptr) {//新插入节点
		DF[hash]++;
		Occur[hash] += Times;
		doclist[hash]->Add(DocID, Times);
	}
	else//已插入 修改
	{
		Occur[hash] += Times;
		doclist[hash]->Edit(DocID, t->Times + Times);
	}
}

DocList* Inverted_DOC_HASH::Search(wCharString &c) {
	int len = c.length();
	int hash = 0;
	for (int i = 0; i < len; ++i) {	//计算单词哈希值
		hash = ((LL)hash*HASHN + (LL)c[i]) % HASHM;
	}
	while (h[hash] != nullptr) {
		if (*h[hash] == c) break;
		hash++;
		if (hash == HASHM) hash = 0;
	}
	if (h[hash] == nullptr) return nullptr; //未找到
	return doclist[hash];
}

void Inverted_DOC_HASH::Edit(wCharString &c, int DocID, int Times) {
	Insert(c, DocID, Times);
}
