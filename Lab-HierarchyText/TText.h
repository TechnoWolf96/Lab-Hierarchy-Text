#pragma once
#include <cstring>
#include <fstream>
#include "../TList/TStackList.h"
using namespace std;

struct Node
{
	char str[81];
	Node* pNext, * pDown;

	Node(char* str = nullptr)
	{
		this->pNext = pNext;
		this->pDown = pDown;
		if (str == nullptr) this->str[0] = '\0';
		else strcpy(this->str, str);
	}
	~Node(){}

};


class TText
{
private:
	Node* pFirst, * pCurrent;
	TStackList<Node*> stack;

	Node* ReadRecursion(ifstream& is);
	void PrintRecursion();
	
public:
	TText()
	{
		pFirst = nullptr;
		pCurrent = nullptr;
	}

	// Navigation
	void GoNext();
	void GoBack();
	void GoDown();
	void GoFirst();

	void InsertNextLine(char* str); // Insert string after current to the same level
	void InsertNextSection(char* str); // Insert string to the lower lever of current
	void InsertDownLine(char* str);
	void InsertDownSection(char* str);

	void DeleteNext();
	void DeleteDown();

	// Filestream
	void Load(char* filename);
	void Print(char* filename);
};


inline Node* TText::ReadRecursion(ifstream& is)
{
	Node* pHead = nullptr, * pTemp = nullptr;
	char str[81];
	while (!is.eof())
	{
		is.getline(str, 81, '\n');
		if (str[0] == '{') pTemp->pDown = ReadRecursion(is);
		else if (str[0] == '}') break;
		else
		{
			Node* newNode = new Node(str);
			if (pHead == nullptr) pTemp = pHead = newNode;
			else
			{
				pTemp->pNext = newNode;
				pTemp = newNode;
			}
		}
	}

	return pHead;
}

inline void TText::PrintRecursion()
{

}

inline void TText::GoNext()
{
	if (pCurrent == nullptr) throw "Current pointer don`t exist";
	stack.Push(pCurrent);
	pCurrent = pCurrent->pNext;
}

inline void TText::GoBack()
{
	if (pCurrent == nullptr) throw "Current pointer don`t exist";
	Node* backNode = stack.Pop();
	pCurrent = backNode;
}

inline void TText::GoDown()
{
	if (pCurrent == nullptr) throw "Current pointer don`t exist";
	stack.Push(pCurrent);
	pCurrent = pCurrent->pDown;
}

inline void TText::GoFirst()
{
	pCurrent = pFirst;
}

inline void TText::InsertNextLine(char* str)
{
	if (pCurrent == nullptr) throw "Current pointer don`t exist";
	Node* newNode = new Node(str);
	newNode->pNext = pCurrent->pNext;
	pCurrent->pNext = newNode;
}

