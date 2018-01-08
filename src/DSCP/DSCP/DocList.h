#pragma once
#include "DocList_Node.h"
class Inverted_DOC_Node;
class DocList;

/*--------------------------------
  �ĵ�������
  ��Ա������ TermID ����ID
             head �ĵ�����ͷָ��
--------------------------------*/

class DocList {
public:
	DocList(int);      // ���캯��
	DocList(DocList&); // �������캯�� ִ��ֵ����
	~DocList();        // ��������
	DocList& operator =(const DocList&); //���صȺ�
	void Add(int ,int); //��ӽڵ�  ���������ĵ���ţ� ���ִ�����
	int Remove(int);	//ɾ���ڵ�  ���������ĵ���ţ�
	DocList_Node* Search(int); //���� ���������ĵ���ţ�
	int Edit(int, int); //�޸Ľڵ� ���������ĵ���ţ� ���ִ�����
	DocList_Node* get_head() const; //��ȡ�ĵ�����ͷָ��

	friend class Inverted_DOC_Node;
	friend class DocList;
private:
	int TermID;
	DocList_Node *head;
};

inline DocList_Node* DocList::get_head() const { return head; }
