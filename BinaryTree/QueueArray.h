#pragma once
#include "Queue.h"
#include "QueueOverflow.h"
#include "QueueUnderflow.h"
#include "WrongQueueSize.h"
#include <iostream>

const size_t SIZEQ = 100;

template <class T>
class QueueArray : public Queue<T>
{
private:
	T* array_;
	size_t head_;
	size_t tail_;
	size_t size_;
	size_t count_;
	void swap(QueueArray<T>& src);

public:
	QueueArray(size_t size = SIZEQ);
	QueueArray(const QueueArray<T>& src) = delete;
	QueueArray<T>& operator=(const QueueArray<T>& src) = delete;
	QueueArray<T>& operator=(QueueArray<T>&& src);
	QueueArray(QueueArray<T>&& src);

	~QueueArray()override;
	void enQueue(const T& e)override;
	T deQueue()override;
	bool isEmpty()override;
	bool isFull()override;
	
	void Print();
	const size_t count() { return count_; }
	const T& first();
	const T& last();
};

template <class T>
const T& QueueArray<T>::first() { 
	if (isEmpty()) {
		return array_[-1];
	}
	return array_[head_]; 
}

template <class T>
const T& QueueArray<T>::last() {
	if (isEmpty()) {
		return array_[-1];
	}
	if (tail_ == 0) {
		return array_[size_ - 1];
	}
	return array_[tail_ - 1];
}

template <class T>
QueueArray<T>::QueueArray(size_t size) {
	if (size < 1) {
		throw WrongQueueSize();
	}
	head_ = 0;
	tail_ = 0;
	count_ = 0;
	size_ = size;
	try {
		array_ = new T[size_];
	}
	catch (...) {
		throw WrongQueueSize();
	}
}

template <class T>
QueueArray<T>::QueueArray(QueueArray<T>&& src) {
	this->swap(src);
}

template <class T>
QueueArray<T>& QueueArray<T>::operator=(QueueArray<T>&& src) {
	this->swap(src);
	delete[] src.array_;
	src.size_ = 0;
	src.head_ = 0;
	src.tail_ = 0;
	src.count_ = 0;
	return *this;
}

template <class T>
QueueArray<T>::~QueueArray() {
	delete[] array_;
}

template <class T>
bool QueueArray<T>::isEmpty() {
	return count_ == 0;
}

template <class T>
bool QueueArray<T>::isFull() {
	return count_ == size_;
}

template<typename T>
void QueueArray<T>::enQueue(const T& e)
{
	if (isFull())
	{
		throw QueueOverflow();
	}
	array_[tail_] = e;
	if (tail_ == size_ - 1)
	{
		tail_ = 0;
	}
	else {
		tail_++;
	}
	count_++;
}

template<typename T>
T QueueArray<T>::deQueue()
{
	if (isEmpty())
	{
		throw QueueUnderflow();
	}
	T x = array_[head_];
	if (head_ == size_ - 1)
	{
		head_ = 0;
	}
	else
	{
		head_++;
	}
	count_--;
	return x;
}

template<typename T>
void QueueArray<T>::Print()
{
	if (isEmpty()) {
		std::cout << "Queue is empty.\n";
	}
	else {
		std::cout << "Queue: ";
		if (isFull()) {
			for (size_t i = 0; i < size_; i++) {
				std::cout << array_[i] << " ";
			}
		} else if (head_ > tail_ && !isFull()) {
			for (size_t i = head_; i < size_; i++) {
				std::cout << array_[i] << " ";
			}
			for (size_t i = 0; i < tail_; i++) {
				std::cout << array_[i] << " ";
			}
		} else {
			for (size_t i = head_; i < tail_; i++) {
				std::cout << array_[i] << " ";
			}
		}
	}
	std::cout << "\n";
}


template<typename T>
void QueueArray<T>::swap(QueueArray<T>& src)
{
	std::swap(array_, src.array_);
	std::swap(head_, src.head_);
	std::swap(tail_, src.tail_);
	std::swap(size_, src.size_);
	std::swap(count_, src.count_);
}



