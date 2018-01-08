#pragma once
#include "wCharString.h"
#include "Inverted_DOC_Node.h"

/*-------------------------------------
   �����ĵ��ࣺ(ƽ�������ʵ��)
   ��Ա������root ���ڵ�
             NIL �սڵ�
			 size �ĵ���С���ڵ������
--------------------------------------*/

class Inverted_DOC {
public:
	Inverted_DOC();
	~Inverted_DOC();

	void rotate(Inverted_DOC_Node*, int);						//��ת
	Inverted_DOC_Node* Insert(wCharString&, int, int, int);		//����   �����������ʣ�����ID���ĵ�ID�����ʳ��ִ�����
	void Insert_Fixup(Inverted_DOC_Node*);						//�������
	void Remove(Inverted_DOC_Node*);							//ɾ��   ��������ɾ���ڵ�)
	void Remove_Fixup(Inverted_DOC_Node*);						//ɾ������
	void Adjust(int K, Inverted_DOC_Node*);						//����  ʹƽ�����ﵽƽ��
	void Edit(wCharString&, int, int);							//�޸ĵ����ĵ�  ��������Ŀ�굥�ʣ�Ŀ���ĵ����޸ĺ�ĳ��ִ�����
	Inverted_DOC_Node* search(wCharString&);					//���ҽ��  �����������ʣ�
	Inverted_DOC_Node* successor(Inverted_DOC_Node* z);			//���Һ�̽ڵ�
	Inverted_DOC_Node* precursor(Inverted_DOC_Node* z);			//����ǰ���ڵ�
	Inverted_DOC_Node* operator [](wCharString&);				//�����±������[]����ߴ���ɶ���
	Inverted_DOC_Node* getNIL()const;
private:
	Inverted_DOC_Node *root, *NIL;
	int size;
};

inline Inverted_DOC_Node* Inverted_DOC::getNIL()const { return NIL; }
