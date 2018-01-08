#pragma once

template <class T>
struct node {
private:
	T value;
	node<T> *next, *prev;
public:
	//node() : next(nullptr) {}
	node(T t, node<T>* nx = nullptr, node<T>* pr = nullptr) : value(t), next(nx), prev(pr) {}
	node(const node<T>&);	//�������캯��
	~node() { if (next != nullptr) delete next; }

	node<T>* getnext() const { return next; }	//��ȡ��һ��Ԫ��
	node<T>* getprev() const { return prev; }	//��ȡǰһ��Ԫ��
	void setnext(node<T>* t) { next = t;  }		//������һ��Ԫ��
	void setprev(node<T>* t) { prev = t; }		//����ǰһ��Ԫ��
	T getvalue() const { return value; }		//��ȡԪ��ֵ
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