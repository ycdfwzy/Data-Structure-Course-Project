#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "Stack_.h"
#include "wCharString.h"
#include "wCharStringLink.h"
#include "Post.h"

class htmlExplainer {	//����html
public:
	htmlExplainer();
	~htmlExplainer();

	void extractInfo(wCharString&, Post* p/*std::vector<Post*>&*/);					//����������
	bool match(wCharString&, wCharString&);									//�жϱ�ǩƥ��
	bool selfclosed(wCharString&);											//�жϱ�ǩ�Ƿ����Ապ�
	void findin_class_tszh1(int, wCharString&, wCharString&, wCharString&);	//��<div class="ts z h1">����ȡ ��ַ ��������1 ��������
	void findin_class_z(int, wCharString&, wCharString&);					//��<div class="z">����ȡ �������� ����С��
	void find_date(int, wCharString&);										//��ȡ ��������
	void find_author(int, wCharString&);									//��ȡ ������
	void findin_class_tfsz(int, wCharString&);								//��<div class='t-fsz'>����ȡ ��������

private:
	int cnt, root;
	wCharString label[10000];
	wCharString cont[10000];
	int a[10000];
	int nxt[10000];
	static wchar_t* sc[15];
};

