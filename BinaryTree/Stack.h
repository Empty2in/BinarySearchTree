#pragma once
#include <string>
template <class T>
class Stack
{
public:
	virtual ~Stack() {}
	virtual void push(const T& e) = 0; // Добавление элемента в стек
	virtual T pop() = 0; // Удаление верхнего элемента
	virtual bool isEmpty() = 0; // Проверка стека на пустоту
	virtual bool isFull() = 0;
	virtual void Print() = 0;
	virtual const T& top() = 0;

};