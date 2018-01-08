#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "Stack_.h"
#include "wCharString.h"
#include "wCharStringLink.h"
#include "Post.h"

class htmlExplainer {	//解析html
public:
	htmlExplainer();
	~htmlExplainer();

	void extractInfo(wCharString&, Post* p/*std::vector<Post*>&*/);					//解析主函数
	bool match(wCharString&, wCharString&);									//判断标签匹配
	bool selfclosed(wCharString&);											//判断标签是否是自闭和
	void findin_class_tszh1(int, wCharString&, wCharString&, wCharString&);	//在<div class="ts z h1">中提取 网址 发帖标题1 发帖类型
	void findin_class_z(int, wCharString&, wCharString&);					//在<div class="z">中提取 发帖大类 发帖小类
	void find_date(int, wCharString&);										//提取 发帖日期
	void find_author(int, wCharString&);									//提取 发帖人
	void findin_class_tfsz(int, wCharString&);								//在<div class='t-fsz'>中提取 发帖内容

private:
	int cnt, root;
	wCharString label[10000];
	wCharString cont[10000];
	int a[10000];
	int nxt[10000];
	static wchar_t* sc[15];
};

