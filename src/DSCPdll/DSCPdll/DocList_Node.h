#pragma once

class DocList;
class Inverted_DOC_Node;
class Inverted_DOC_HASH;

class DocList_Node {
public:
	DocList_Node(int, int);
	DocList_Node(DocList_Node&);
	~DocList_Node();
	int get_DocID() const;
	int get_Times() const;
	DocList_Node* get_next() const;
	DocList_Node& operator =(const DocList_Node&);
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
