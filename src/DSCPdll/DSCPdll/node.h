#pragma once

template <class T>
struct node {
private:
	T value;
	node<T> *next, *prev;
public:
	//node() : next(nullptr) {}
	node(T t, node<T>* nx = nullptr, node<T>* pr = nullptr) : value(t), next(nx), prev(pr) {}
	node(const node<T>&);	//拷贝构造函数
	~node() { if (next != nullptr) delete next; }

	node<T>* getnext() const { return next; }	//获取下一个元素
	node<T>* getprev() const { return prev; }	//获取前一个元素
	void setnext(node<T>* t) { next = t;  }		//设置下一个元素
	void setprev(node<T>* t) { prev = t; }		//设置前一个元素
	T getvalue() const { return value; }		//获取元素值
};

template <class T>
node<T>::node(const node<T> &c) {
	value = c.getvalue();
	prev = nullptr;
	if (c.getnext() == nullptr)
		next = nullptr;
	else {
		next = new node<T>(*(c.getnext()));
		next->setprev(this);
	}
}