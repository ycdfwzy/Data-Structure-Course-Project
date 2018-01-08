#pragma once
#include <iostream>
#include <fstream>
#include "node.h"
#include "wCharString.h"

class htmlExplainer;

class wCharStringLink	//�ַ���������
{
public:
	wCharStringLink();
	wCharStringLink(const wCharStringLink&);	//�������캯��
	~wCharStringLink();

	void add(wCharString&, int pos = -1);	//��Ӷ���
	void remove(int);						//ɾ��
	void remove(wCharString&);				//ɾ��
	int search(wCharString&) const;			//����
	int search(const wchar_t*) const;		//����
	node<wCharString>* gethead()const;

	wCharString operator[](unsigned int);	//����p[]
	friend std::wostream& operator <<(std::wostream&, wCharStringLink&);	//�����
	friend class htmlExplainer;
private:
	node<wCharString> *head;
	int size;
};

inline node<wCharString>* wCharStringLink::gethead()const {
	return head;
}

