#pragma once
#include "wCharString.h"
#include "wCharStringLink.h"
#include <fstream>
#include <iostream>

class Dictionary	//�ֵ� ��ϣ
{
public:
	~Dictionary();

	static Dictionary* getSingle();	//��ȡ����
	void initDictionary();			//��ʼ���ֵ�
	void divide(wCharString &c, wCharStringLink &v);	//�ִ�
	bool check(wCharString&, int);	//���Ժ���

	static int HASHN;	//��ϣֵ
	static int HASHM;	//��ϣֵ

private:
	Dictionary();
	static Dictionary *Single;	//����ģʽ
	wCharString *h[10000019];	//��ϣ��
};

