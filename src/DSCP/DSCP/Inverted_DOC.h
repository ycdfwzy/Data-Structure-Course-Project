#pragma once
#include "wCharString.h"
#include "Inverted_DOC_Node.h"

/*-------------------------------------
   倒排文档类：(平衡二叉树实现)
   成员变量：root 根节点
             NIL 空节点
			 size 文档大小（节点个数）
--------------------------------------*/

class Inverted_DOC {
public:
	Inverted_DOC();
	~Inverted_DOC();

	void rotate(Inverted_DOC_Node*, int);						//旋转
	Inverted_DOC_Node* Insert(wCharString&, int, int, int);		//插入   （参数：单词，单词ID，文档ID，单词出现次数）
	void Insert_Fixup(Inverted_DOC_Node*);						//插入调整
	void Remove(Inverted_DOC_Node*);							//删除   （参数：删除节点)
	void Remove_Fixup(Inverted_DOC_Node*);						//删除调整
	void Adjust(int K, Inverted_DOC_Node*);						//调整  使平衡树达到平衡
	void Edit(wCharString&, int, int);							//修改倒排文档  （参数：目标单词，目标文档，修改后的出现次数）
	Inverted_DOC_Node* search(wCharString&);					//查找结点  （参数：单词）
	Inverted_DOC_Node* successor(Inverted_DOC_Node* z);			//查找后继节点
	Inverted_DOC_Node* precursor(Inverted_DOC_Node* z);			//查找前驱节点
	Inverted_DOC_Node* operator [](wCharString&);				//重载下表运算符[]，提高代码可读性
	Inverted_DOC_Node* getNIL()const;
private:
	Inverted_DOC_Node *root, *NIL;
	int size;
};

inline Inverted_DOC_Node* Inverted_DOC::getNIL()const { return NIL; }
