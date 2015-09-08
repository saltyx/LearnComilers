#pragma once

#include "helper.h"



template <typename T>
class Stack {

public :
	Stack();

	~Stack();

	T pop();

	T Top();

	STATUS push(T x);

	BOOL isFull();

	BOOL isEmpty();

protected : 
	int top;
	T *stack;
};
template<typename T>
Stack<T>::Stack() {

	stack = new T[MAX_SIZE];
	top = -1;
}

template<typename T>
Stack<T>::~Stack() {
	top = -1;
	delete[] stack;
}

template<typename T>
T Stack<T>::Top() {
		return stack[top];

}

template<typename T>
STATUS Stack<T>::push(T x) {
	if (!isFull()) {

		stack[++top] = x;

		return SUCCESS;
	}
	else {
		return FAIL;
	}
}

template<typename T>
T Stack<T>::pop() {
	return stack[top--];
}

template<typename T>
BOOL Stack<T>::isFull() {
	return top == MAX_SIZE - 1;
}

template<typename T>
BOOL Stack<T>::isEmpty() {
	return top == - 1;
}

