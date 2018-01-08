#pragma once
#include "wCharString.h"
#include "DocList.h"
#include "DocList_Node.h"

/*----------------------------------------
    �����ĵ��ࣺ(��ϣ��ʵ��)
	��Ա������HASHN, HASHM ��ϣֵ
	          h ��ϣ���洢�ַ�
			  DF �����ڶ��������г���
			  Occur ���ʳ����ܴ���
			  doclist �ĵ�����
----------------------------------------*/

class Inverted_DOC_HASH
{
public:
	Inverted_DOC_HASH();
	~Inverted_DOC_HASH();

	void Insert(wCharString&, int, int);	//���� �����������ʣ��ĵ���ţ����ִ�����
	DocList* Search(wCharString&);          //���� �����������ʣ�
	void Edit(wCharString&, int, int);		//�޸� �����������ʣ��ĵ���ţ����ִ�����

private:
	static int HASHN;	//��ϣֵ
	static int HASHM;	//��ϣֵ
	wCharString *h[10000019];	//��ϣ��
	int DF[10000019], Occur[10000019];
	DocList *doclist[10000019];
};

