#pragma once

#include <map>
#include "wCharString.h"
#include "wCharStringLink.h"
#include <cstring>
#include <iostream>

class Dictionary_AC_Automation {	//字典 AC自动机
public:
	~Dictionary_AC_Automation();

	static Dictionary_AC_Automation* getsingle();	//获取单件
	void initDictionary();	//初始化字典
	void divide(wCharString &c, wCharStringLink &v);	//分词

private:
	static Dictionary_AC_Automation *single;	//单件模式
	void add_to_tire(wchar_t*);					//添加到tire树
	int get_next(int, int);						//在AC自动机上找到下一个
	void build_fail_tree();						//建立 失败指针 树

	Dictionary_AC_Automation();
	int root_next[100000];
	int a[600010], nxt[600010];
	int fa[600010], fail[600010];
	wchar_t ch[600010];
	int mml[600010]; // max matching length
	int cnt;
	//std::map<wchar_t, int> ac;
};

