#pragma once
#include "wCharString.h"
#include "wCharStringLink.h"
#include <fstream>
#include <iostream>

class Dictionary	//字典 哈希
{
public:
	~Dictionary();

	static Dictionary* getSingle();	//获取单间
	void initDictionary();			//初始化字典
	void divide(wCharString &c, wCharStringLink &v);	//分词
	bool check(wCharString&, int);	//测试函数

	static int HASHN;	//哈希值
	static int HASHM;	//哈希值

private:
	Dictionary();
	static Dictionary *Single;	//单件模式
	wCharString *h[10000019];	//哈希表
};

