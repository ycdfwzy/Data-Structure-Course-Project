#pragma once

#include <map>
#include "wCharString.h"
#include "wCharStringLink.h"
#include <cstring>
#include <iostream>

class Dictionary_AC_Automation {	//�ֵ� AC�Զ���
public:
	~Dictionary_AC_Automation();

	static Dictionary_AC_Automation* getsingle();	//��ȡ����
	void initDictionary();	//��ʼ���ֵ�
	void divide(wCharString &c, wCharStringLink &v);	//�ִ�

private:
	static Dictionary_AC_Automation *single;	//����ģʽ
	void add_to_tire(wchar_t*);					//��ӵ�tire��
	int get_next(int, int);						//��AC�Զ������ҵ���һ��
	void build_fail_tree();						//���� ʧ��ָ�� ��

	Dictionary_AC_Automation();
	int root_next[100000];
	int a[600010], nxt[600010];
	int fa[600010], fail[600010];
	wchar_t ch[600010];
	int mml[600010]; // max matching length
	int cnt;
	//std::map<wchar_t, int> ac;
};

