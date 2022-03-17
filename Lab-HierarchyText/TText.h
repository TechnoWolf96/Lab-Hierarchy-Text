#pragma once
#include <iostream>
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
		this->pNext = nullptr;
		this->pDown = nullptr;
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
	void PrintFileRecursion(Node* pNode, ofstream& os);
	void PrintRecursion(Node* pNode, ostream& os, int level);
	
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

	void InsertNextLine(char* str); // Insert string after current 
	void InsertNextSection(char* str); // Insert string to the same level with subjection next lines
	void InsertDownLine(char* str); // Insert string to the first position on the lower level
	void InsertDownSection(char* str); // Insert subjected header of the lower level

	void DeleteNext();
	void DeleteDown();

	// Filestream
	void Load(char* filename);
	void Print(char* filename);
	void Print();
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
			if (pHead == nullptr)
				pTemp = pHead = newNode;
			else
			{
				pTemp->pNext = newNode;
				pTemp = newNode;
			}
		}
	}

	return pHead;
}

inline void TText::PrintFileRecursion(Node* pNode, ofstream& file)
{
	if (pNode != nullptr)
	{
		file << pNode->str << endl;
		PrintFileRecursion(pNode->pDown, file);
		PrintFileRecursion(pNode->pDown, file);
	}
}

inline void TText::PrintRecursion(Node* pNode, ostream& os, int level)
{
	if (pNode != nullptr)
	{
		for (int i = 0; i < level; i++) os << "\t";
		os << pNode->str << endl;
		if (pNode->pDown != nullptr)
		{
			PrintRecursion(pNode->pDown, os, level+1);
		}
		PrintRecursion(pNode->pNext, os, level);
	}
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

inline void TText::InsertNextSection(char* str)
{
	if (pCurrent == nullptr) throw "Current pointer don`t exist";
	Node* newNode = new Node(str);
	newNode->pDown = pCurrent->pNext;
	pCurrent->pNext = newNode;
}

inline void TText::InsertDownLine(char* str)
{
	if (pCurrent == nullptr) throw "Current pointer don`t exist";
	Node* newNode = new Node(str);
	newNode->pNext = pCurrent->pDown;
	pCurrent->pDown = newNode;
}

inline void TText::InsertDownSection(char* str)
{
	if (pCurrent == nullptr) throw "Current pointer don`t exist";
	Node* newNode = new Node(str);
	newNode->pDown = pCurrent->pDown;
	pCurrent->pDown = newNode;
}




void TText::Load(char* filename)
{
	ifstream file(filename);
	pFirst = ReadRecursion(file);
}

inline void TText::Print(char* filename)
{
	ofstream file(filename);
	PrintFileRecursion(pFirst, file);
}

inline void TText::Print()
{
	PrintRecursion(pFirst, cout, 0);
}
