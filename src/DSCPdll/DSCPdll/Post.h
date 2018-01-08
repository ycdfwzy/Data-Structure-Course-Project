#pragma once
#include "Dictionary.h"
#include "wCharString.h"
#include "wCharStringLink.h"
#include "Dictionary_AC_Automation.h"
#include <iostream>

class Post {	//������Ϣ
public:
	Post(wCharString&);
	Post(wCharString&, wCharString&, wCharString&, wCharString&, wCharString&, wCharString&, wCharString&, wCharString&);
	Post(const Post&);		//�������캯��
	~Post();

	wCharString getwebadd() const;
	wCharString gettitle() const;
	wCharString getauthor() const;
	wCharString getcont() const;
	wCharString getctg1() const;
	wCharString getctg2() const;
	wCharString gettype() const;
	wCharString getdate() const;
	void setwebadd(const wCharString&);	//������ַ
	void setctg1(const wCharString&);	//���÷�������
	void setctg2(const wCharString&);	//���÷���С·
	void settitle(const wCharString&);	//���÷�������1
	void setcont(const wCharString&);	//���÷�������
	void setauthor(const wCharString&);	//���÷�����
	void setdate(const wCharString&);	//���÷�������
	void settype(const wCharString&);	//���÷�������
	void divideWords(int type = 0);		//�ִ�
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

inline wCharString Post::gettitle() const {
	return title;
}

inline wCharString Post::getauthor() const {
	return author;
}

inline wCharString Post::getcont() const {
	return cont;
}

inline wCharString Post::getctg1() const {
	return ctg1;
}

inline wCharString Post::getctg2() const {
	return ctg2;
}

inline wCharString Post::gettype() const {
	return type;
}

inline wCharString Post::getdate() const {
	return date;
}
