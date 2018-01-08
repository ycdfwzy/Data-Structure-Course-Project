#pragma once
#include "wCharString.h"
#include "DocList.h"

class Inverted_DOC;

/*------------------------
  倒排文档平衡二叉树节点
  成员变量: Term 单词
            TermID 单词ID
			DF 单词出现在多少文章中
			Occur 单词总的出现次数
			size 以该节点为根的子树大小
			son 左右孩子节点
			p 父节点
			doclist 文档链表
------------------------*/

class Inverted_DOC_Node {
public:
	//构造函数
	Inverted_DOC_Node(int color_,int TermID_, int size_, Inverted_DOC_Node*, Inverted_DOC_Node*, Inverted_DOC_Node*, wCharString&);
	//析构函数
	~Inverted_DOC_Node();

	void insert(int DocID, int Times);	//插入 （参数：文档编号，出现次数）
	void value_copy(Inverted_DOC_Node*); //值拷贝
	void Edit(int, int);//编辑 （参数：文档编号， 出现次数）
	void Remove(int);//删除 （参数：文档编号）
	DocList* get_doclist() const;	//获取文档链表
	friend class Inverted_DOC;
private:
	wCharString Term;
	int TermID, DF, Occur, color, size;
	Inverted_DOC_Node *son[2], *p;
	DocList *doclist;
};

inline DocList* Inverted_DOC_Node::get_doclist() const { return doclist; }