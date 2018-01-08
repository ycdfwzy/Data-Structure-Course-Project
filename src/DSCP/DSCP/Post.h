#pragma once
#include "Dictionary.h"
#include "wCharString.h"
#include "wCharStringLink.h"
#include "Dictionary_AC_Automation.h"
#include <iostream>

class Post{	//帖子信息
public:
	Post(wCharString&);
	Post(wCharString&, wCharString&, wCharString&, wCharString&, wCharString&, wCharString&, wCharString&, wCharString&);
	Post(const Post&);		//拷贝构造函数
	~Post();

	wCharString getwebadd() const;
	void setwebadd(const wCharString&);	//设置网址
	void setctg1(const wCharString&);	//设置发帖大类
	void setctg2(const wCharString&);	//设置发帖小路
	void settitle(const wCharString&);	//设置发帖标题1
	void setcont(const wCharString&);	//设置发帖内容
	void setauthor(const wCharString&);	//设置发帖人
	void setdate(const wCharString&);	//设置发帖日期
	void settype(const wCharString&);	//设置发帖类型
	void divideWords(int type = 0);		//分词
	void checkvalid();
	wCharStringLink* getpart();
	Post& operator =(const Post&);		//重载=
	friend std::wostream& operator <<(std::wostream&, Post&); //输出流
private:
	wCharString webadd, ctg1, ctg2, title, cont, author, date, type;	//网址 发帖大类 发帖小类 发帖标题1 发帖内容 发帖人 发帖日期 发帖类型 分词结果
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
