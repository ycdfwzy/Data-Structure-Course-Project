#pragma once
#include <iostream>
#include <fstream>
#include "node.h"
#include "wCharString.h"

class htmlExplainer;

class wCharStringLink	//字符串链表类
{
public:
	wCharStringLink();
	wCharStringLink(const wCharStringLink&);	//拷贝构造函数
	~wCharStringLink();

	void add(wCharString&, int pos = -1);	//添加队列
	void remove(int);						//删除
	void remove(wCharString&);				//删除
	int search(wCharString&) const;			//查找
	int search(const wchar_t*) const;		//查找
	node<wCharString>* gethead()const;

	wCharString operator[](unsigned int);	//重载p[]
	friend std::wostream& operator <<(std::wostream&, wCharStringLink&);	//输出流
	friend class htmlExplainer;
private:
	node<wCharString> *head;
	int size;
};

inline node<wCharString>* wCharStringLink::gethead()const {
	return head;
}

