#pragma once
#include "TNode.h"
#include <iostream>

template<class T>
class TList
{
private:
	TNode<T>* pFirst;
public:
	TList() { pFirst = nullptr; }		// Конструктор
	~TList() { Clear(); }				// Деструктор
	void Clear();						// Очистить список
	void Add(T elem);					// Добавить элемент в начало списка
	void Print();						// Печать списка
	void AddAfterMax(T elem);			// Добавить элемент после максимального
	int GetIndexMaxElem();				// Получить порядковый номер максимального элемента


};

template<class T>
inline void TList<T>::Clear()
{
	TNode<T>* temp;
	while (pFirst != nullptr)
	{
		temp = pFirst;
		pFirst = pFirst->pNext;
		delete temp;
	}
}

template<class T>
inline void TList<T>::Add(T item)
{
	TNode<T>* newNode = new TNode<T>();
	newNode->value = item;
	newNode->pNext = pFirst;
	pFirst = newNode;
}

template<class T>
inline void TList<T>::Print()
{
	TNode<T>* pTemp = pFirst;
	std::cout << "[ ";
	while (pTemp != nullptr)
	{
		std::cout << pTemp->value << " ";
		pTemp = pTemp->pNext;
	}
	std::cout << ']';
}

template<class T>
inline void TList<T>::AddAfterMax(T elem)
{
	int index;
	try
	{
		index = GetIndexMaxElem();
	}
	catch (...)
	{
		Add(elem);
		return;
	}

	TNode<T>* pTemp = pFirst;
	for (int i = 0; i < index; i++)
	{
		pTemp = pTemp->pNext;
	}
	TNode<T>* newNode = new TNode<T>();
	newNode->value = elem;
	newNode->pNext = pTemp->pNext;
	pTemp->pNext = newNode;
}

template<class T>
inline int TList<T>::GetIndexMaxElem()
{

	int count = 0;
	int resIndex = 0;
	if (pFirst == nullptr) throw "Список пуст";
	TNode<T>* pTemp = pFirst;
	T maxElem = pTemp->value;
	pTemp = pTemp->pNext;
	while (pTemp != nullptr)
	{
		count++;
		if (maxElem < pTemp->value)
		{
			maxElem = pTemp->value;
			resIndex = count;
		}
		pTemp = pTemp->pNext;
	}
	return resIndex;
}
