#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include<iomanip> 

class htmlExplainer;
class Dictionary;
class Post;

class wCharString {							//�Զ����ַ�����
public:
	wCharString(const char* c);
	wCharString(const wchar_t* c = nullptr);
	wCharString(const wCharString&);		//�������캯��
	~wCharString();
	int indexOf(const wCharString&);		//Ѱ���Ӵ�λ��
	int indexOf(const wchar_t*);			//Ѱ���Ӵ�λ��
	int length()const;						//�ַ�������
	wchar_t operator[](unsigned int);		//����[]
	wCharString substring(int ,int);		//��ȡ�Ӵ�
	void concat(const wCharString&);		//�����ַ���
	void concat(const wchar_t*);			//�����ַ���
	void concat(const wchar_t);				//�����ַ�
	void expand(int tar);					//�����ڴ�
	void translate();						//ת������
	bool startwith(const wchar_t*);			//�ж�ǰ׺
	bool endwith(const wchar_t*);			//�жϺ�׺

	wCharString& operator =(const wCharString&);	//����=
	bool operator ==(const wCharString&)const;		//����==
	bool operator <(const wCharString&)const;		//����<

	friend std::wostream& operator <<(std::wostream&, wCharString&);//���������
	friend std::wistream& operator >>(std::wistream&, wCharString&);//����������
	friend class htmlExplainer;
	friend class Dictionary;
	friend class Post;
private:
	wchar_t* m_data;
	int size;
};
