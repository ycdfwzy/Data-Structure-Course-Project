#pragma once
#include "Dictionary.h"
#include "wCharString.h"
#include "wCharStringLink.h"
#include "Dictionary_AC_Automation.h"
#include <iostream>

class Post{	//������Ϣ
public:
	Post(wCharString&);
	Post(wCharString&, wCharString&, wCharString&, wCharString&, wCharString&, wCharString&, wCharString&, wCharString&);
	Post(const Post&);		//�������캯��
	~Post();

	wCharString getwebadd() const;
	void setwebadd(const wCharString&);	//������ַ
	void setctg1(const wCharString&);	//���÷�������
	void setctg2(const wCharString&);	//���÷���С·
	void settitle(const wCharString&);	//���÷�������1
	void setcont(const wCharString&);	//���÷�������
	void setauthor(const wCharString&);	//���÷�����
	void setdate(const wCharString&);	//���÷�������
	void settype(const wCharString&);	//���÷�������
	void divideWords(int type = 0);		//�ִ�
	void checkvalid();
	wCharStringLink* getpart();
	Post& operator =(const Post&);		//����=
	friend std::wostream& operator <<(std::wostream&, Post&); //�����
private:
	wCharString webadd, ctg1, ctg2, title, cont, author, date, type;	//��ַ �������� ����С�� ��������1 �������� ������ �������� �������� �ִʽ��
	wCharStringLink part;
};

inline wCharStringLink* Post::getpart() {
	return &part;
}

inline void Post::checkvalid() {
	int len = webadd.length();
	if (webadd[len - 1] == L'\"')
		webadd.eraselast();
}
