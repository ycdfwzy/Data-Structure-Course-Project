#pragma once

class DocList;
class Inverted_DOC_Node;
class Inverted_DOC_HASH;

/*-------------------------------
  文档链表节点类
  成员变量：DocID 文档编号
            Times 单词出现次数
			nxt 下一个节点指针
-------------------------------*/

class DocList_Node {
public:
	//构造函数
	DocList_Node(int, int);
	//拷贝构造函数
	DocList_Node(DocList_Node&);
	//析构函数
	~DocList_Node();
	int get_DocID() const; // 获取文档ID
	int get_Times() const; // 获取单词出现次数
	DocList_Node* get_next() const; //获取下一个节点指针
	DocList_Node& operator =(const DocList_Node&); //重载=
	friend class DocList;
	friend class Inverted_DOC_Node;
	friend class Inverted_DOC_HASH;
private:
	int DocID, Times;
	DocList_Node* nxt;
};

inline int DocList_Node::get_DocID() const { return DocID; }
inline int DocList_Node::get_Times() const { return Times; }
inline DocList_Node* DocList_Node::get_next() const { return nxt; }
