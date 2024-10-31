#ifndef __STACK_H__
#define __STACK_H__
#pragma once
#include <iostream>
using namespace std;
template <class T>
class Stack
{
	T* begin;
	T* end;
	int size;
public:
	Stack();
	Stack(int _n);
	Stack(const Stack& _A);
	~Stack();
	void Push(T a);
	T top();
	T pop();
	bool empty();
	int Size();
	bool operator==(Stack<T>& a);
	friend ostream& operator<<(ostream& out, const Stack& a) {
		for (int i = 0; i < a.end - a.begin; i++)
			out << a.begin[i] << ' ';
		return out;
	}
};
#endif
