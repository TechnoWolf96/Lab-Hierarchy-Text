#pragma once
#include "TNode.h"

template <class T>
class TQueueList
{
private:
	TNode<T>* pFirst, * pLast;
public:
	TQueueList() { pFirst = pLast = nullptr; }			// Конструктор
	TQueueList(const TQueueList& other);				// Конструктор копирования
	TQueueList& operator= (const TQueueList& other);	// Оператор присваивания
	~TQueueList() { Clear(); }							// Деструктор

	int Count() { return CountNodes(pFirst); }		// Счетчик элементов в очереди
	bool IsEmpty() { return pFirst == nullptr; }	// Является ли очередь пустой
	void Push(T item);								// Добавить элемент в конец очереди
	T Pop();										// Извлечь из начала очереди
	void Clear();									// Очистить очередь
};

template<class T>
inline void TQueueList<T>::Push(T item)
{
	TNode<T>* newNode = new TNode<T>();
	newNode->value = item;
	newNode->pNext = nullptr;
	if (pLast != nullptr) 
		pLast->pNext = newNode;
	else 
		pFirst = newNode;
	pLast = newNode;
}

template<class T>
inline T TQueueList<T>::Pop()
{
	if (IsEmpty()) throw "Queue is empty";

	T value = pFirst->value;
	TNode<T>* oldFirst = pFirst;
	pFirst = oldFirst->pNext;
	delete oldFirst;
	if (pFirst == nullptr)
		pLast = nullptr;
	return value;
}

template<class T>
inline void TQueueList<T>::Clear()
{
	while (pFirst != nullptr)
		Pop();
}

template<class T>
inline TQueueList<T>::TQueueList(const TQueueList& other)
{
	pFirst = pLast = nullptr;
	if (other.pFirst == nullptr) return;

	TNode<int>* pOther = other.pFirst;
	TNode<T>* newNode = new TNode<int>();
	newNode->value = pOther->value;
	newNode->pNext = nullptr;
	pFirst = newNode;
	TNode<T>* temp = pFirst;
	pOther = pOther->pNext;
	while (pOther != nullptr)
	{
		newNode = new TNode<T>();
		newNode->value = pOther->value;
		newNode->pNext = nullptr;
		temp->pNext = newNode;
		pOther = pOther->pNext;
		temp = temp->pNext;
	}
	pLast = newNode;
}

template<class T>
inline TQueueList<T>& TQueueList<T>::operator=(const TQueueList<T>& other)
{
	Clear();
	if (other.pFirst == nullptr) return *this;

	TNode<int>* pOther = other.pFirst;
	TNode<T>* newNode = new TNode<int>();
	newNode->value = pOther->value;
	newNode->pNext = nullptr;
	pFirst = newNode;
	TNode<T>* temp = pFirst;
	pOther = pOther->pNext;
	while (pOther != nullptr)
	{
		newNode = new TNode<T>();
		newNode->value = pOther->value;
		newNode->pNext = nullptr;
		temp->pNext = newNode;
		pOther = pOther->pNext;
		temp = temp->pNext;
	}
	pLast = newNode;
	return *this;
}