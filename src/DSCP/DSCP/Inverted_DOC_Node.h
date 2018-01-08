#pragma once
#include "wCharString.h"
#include "DocList.h"

class Inverted_DOC;

/*------------------------
  �����ĵ�ƽ��������ڵ�
  ��Ա����: Term ����
            TermID ����ID
			DF ���ʳ����ڶ���������
			Occur �����ܵĳ��ִ���
			size �Ըýڵ�Ϊ����������С
			son ���Һ��ӽڵ�
			p ���ڵ�
			doclist �ĵ�����
------------------------*/

class Inverted_DOC_Node {
public:
	//���캯��
	Inverted_DOC_Node(int color_,int TermID_, int size_, Inverted_DOC_Node*, Inverted_DOC_Node*, Inverted_DOC_Node*, wCharString&);
	//��������
	~Inverted_DOC_Node();

	void insert(int DocID, int Times);	//���� ���������ĵ���ţ����ִ�����
	void value_copy(Inverted_DOC_Node*); //ֵ����
	void Edit(int, int);//�༭ ���������ĵ���ţ� ���ִ�����
	void Remove(int);//ɾ�� ���������ĵ���ţ�
	DocList* get_doclist() const;	//��ȡ�ĵ�����
	friend class Inverted_DOC;
private:
	wCharString Term;
	int TermID, DF, Occur, color, size;
	Inverted_DOC_Node *son[2], *p;
	DocList *doclist;
};

inline DocList* Inverted_DOC_Node::get_doclist() const { return doclist; }