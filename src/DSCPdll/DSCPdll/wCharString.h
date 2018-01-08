#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include<iomanip> 

class htmlExplainer;
class Dictionary;
class Post;

class wCharString {							//自定义字符串类
public:
	wCharString(const char* c);
	wCharString(const wchar_t* c = nullptr);
	wCharString(const wCharString&);		//拷贝构造函数
	~wCharString();
	int indexOf(const wCharString&);		//寻找子串位置
	int indexOf(const wchar_t*);			//寻找子串位置
	int length()const;						//字符串长度
	wchar_t operator[](unsigned int);		//重载[]
	wCharString substring(int ,int);		//截取子串
	void concat(const wCharString&);		//连接字符串
	void concat(const wchar_t*);			//连接字符串
	void concat(const wchar_t);				//连接字符
	void expand(int tar);					//扩充内存
	void translate();						//转译中文
	bool startwith(const wchar_t*);			//判断前缀
	bool endwith(const wchar_t*);			//判断后缀

	wCharString& operator =(const wCharString&);	//重载=
	bool operator ==(const wCharString&)const;		//定义==
	bool operator <(const wCharString&)const;		//定义<

	friend std::wostream& operator <<(std::wostream&, wCharString&);//定义输出流
	friend std::wistream& operator >>(std::wistream&, wCharString&);//定义输入流
	friend class htmlExplainer;
	friend class Dictionary;
	friend class Post;
private:
	wchar_t* m_data;
	int size;
};
