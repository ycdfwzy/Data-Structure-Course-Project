#pragma once
#include "wCharString.h"
#include "DocList.h"
#include "DocList_Node.h"

/*----------------------------------------
    倒排文档类：(哈希表实现)
	成员变量：HASHN, HASHM 哈希值
	          h 哈希表，存储字符
			  DF 单词在多少文章中出现
			  Occur 单词出现总次数
			  doclist 文档链表
----------------------------------------*/

class Inverted_DOC_HASH
{
public:
	Inverted_DOC_HASH();
	~Inverted_DOC_HASH();

	void Insert(wCharString&, int, int);	//插入 （参数：单词，文档编号，出现次数）
	DocList* Search(wCharString&);          //查找 （参数：单词）
	void Edit(wCharString&, int, int);		//修改 （参数：单词，文档编号，出现次数）

private:
	static int HASHN;	//哈希值
	static int HASHM;	//哈希值
	wCharString *h[10000019];	//哈希表
	int DF[10000019], Occur[10000019];
	DocList *doclist[10000019];
};

