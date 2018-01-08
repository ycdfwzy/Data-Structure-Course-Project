#pragma once
#include "node.h"

template <class T>
class Stack_{	// ջģ��
public:
	Stack_() : size(0), head(nullptr){}
	Stack_(const Stack_<T>&);	//�������캯��
	~Stack_() {
		if (head != nullptr)
			delete head;
	}

	int getsize() const;	//��ȡջ��С
	bool empty() const;		//�ж�ջ�Ƿ�Ϊ��
	T top() const;			//��ȡջ��Ԫ��
	void push(T&);			//ѹջ
	void pop();				//��ջ

private:
	int size;
	node<T> *head;
};

template <class T>
Stack_<T>::Stack_(const Stack_<T>& c) {
	size = c.getsize();
	head = new node<T>(*(c.top()));
}

template <class T>
int Stack_<T>::getsize() const{
	return size;
}

template <class T>
bool Stack_<T>::empty() const {
	return (size == 0);
}

template <class T>
T Stack_<T>::top() const {
	return head->getvalue();
}

template <class T>
void Stack_<T>::push(T& t) {
	node<T> *tmp = new node<T>(t, head);
	head = tmp;
	size++;
}

template <class T>
void Stack_<T>::pop() {
	if (size == 0) return;
	node<T> *tmp = head;
	head = head->getnext();
	tmp->setnext(nullptr);
	delete tmp;
	size--;
}