#pragma once
#include "DocList_Node.h"
class Inverted_DOC_Node;
class DocList;

/*--------------------------------
  文档链表类
  成员变量： TermID 单词ID
             head 文档链表头指针
--------------------------------*/

class DocList {
public:
	DocList(int);      // 构造函数
	DocList(DocList&); // 拷贝构造函数 执行值拷贝
	~DocList();        // 析构函数
	DocList& operator =(const DocList&); //重载等号
	void Add(int ,int); //添加节点  （参数：文档编号， 出现次数）
	int Remove(int);	//删除节点  （参数：文档编号）
	DocList_Node* Search(int); //查找 （参数：文档编号）
	int Edit(int, int); //修改节点 （参数：文档编号， 出现次数）
	DocList_Node* get_head() const; //获取文档链表头指针

	friend class Inverted_DOC_Node;
	friend class DocList;
private:
	int TermID;
	DocList_Node *head;
};

inline DocList_Node* DocList::get_head() const { return head; }
