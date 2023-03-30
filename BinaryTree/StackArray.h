#pragma once
#include "Stack.h"
#include "StackUnderflow.h"
#include "StackOverflow.h"
#include "WrongStackSize.h"
#include <iostream>

const size_t SIZE = 100;

template <class T>
class StackArray : public Stack<T>
{
public:
	StackArray(size_t size = SIZE);
	StackArray(const StackArray<T>& src) = delete;
	StackArray& operator=(const StackArray<T>& src) = delete;

	//StackArray(StackArray<T>&& src);
	StackArray& operator=(StackArray<T>&& src);

	virtual ~StackArray(); 
	void push(const T& e);
	T pop();
	bool isEmpty();
	bool isFull();
	const T& top();
	void Print();

private:
	T* array_; // массив элементов стека: !!! array_[0] – не используется, top_ от 1 до size_
	size_t top_;
	size_t size_;
	void swap(StackArray<T>& src);
};

template <class T>
StackArray<T>::StackArray(size_t size) {
	size_ = size;
	top_ = 0;
	try {
		array_ = new T[size + 1];
	}
	catch (...) {
		throw WrongStackSize();
	}
}

//template <class T>
//StackArray<T>::StackArray(StackArray<T>&& src);

template <class T>
StackArray<T>& StackArray<T>::operator=(StackArray<T>&& src) {
	if (&src == this) {
		return *this;
	}
	delete[] array_;
	top_ = src.mp_top;
	size_ = src.m_size;
	top_ = nullptr;
	size_ = 0;
	return *this;
}

template <class T>
StackArray<T>::~StackArray() {
	delete[] array_;
}

template <class T>
void StackArray<T>::push(const T& e) {
	if (isFull()) {
		throw StackOverflow();
	}
	array_[++top_] = e;
}

template <class T>
T StackArray<T>::pop() {
	if (isEmpty()) {
		throw StackUnderflow();
	}
	return array_[top_--];
}

template <class T>
bool StackArray<T>::isEmpty() {
	return top_ == 0;
}

template <class T>
bool StackArray<T>::isFull() {
	return top_ == size_;
}

template <class T>
const T& StackArray<T>::top() {
	if (!isEmpty()) {
		return array_[top_];
	}
	return 0;
}

template <class T>
void StackArray<T>::Print() {
	if (isEmpty()) {
		std::cout << "Stack is empty.\n";
	}
	else {
		T* ind = array_ + 1;
		for (size_t i = 1; i < top_+1; i++) {
			std::cout << *ind << " ";
			ind++;
		}
		std::cout << '\n';
	}
}

template <class T>
void StackArray<T>::swap(StackArray<T>& src) {
	std::swap(array_, src.array_);
	std::swap(top_, src.top_);
	std::swap(size_, src.size_);
}



