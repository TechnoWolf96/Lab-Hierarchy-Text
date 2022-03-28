#pragma once
#include <fstream>
#include "../TList/TStackList.h"
#include "TTextNode.h"
using namespace std;




class TText
{
private:
	TTextNode* pFirst, * navCurrent, *ptCurrent;
	TStackList<TTextNode*> navStack, ptStack;

	TTextNode* ReadRecursion(ifstream& is);
	void PrintFileRecursion(TTextNode* pNode, ofstream& os);
	void PrintRecursion(TTextNode* pNode, ostream& os, int level);
	
	
public:
	TText(int memorySize = 100)
	{
		pFirst = nullptr;
		navCurrent = nullptr;
		ptCurrent = nullptr;
		TTextNode::InitializeMemory(memorySize);
	}

	void CleanMemory();

	char* GetNavCurrent();
	void SetNavCurrent(char* str);
	char* GetPtCurrent();
	void SetPtCurrent(char* str);



	void Reset();
	void GoNext();
	bool IsEnd();

	// Navigation
	void GoNextLine();
	void GoBackLine();
	void GoDownLine();
	void GoFirstLine();

	void InsertNextLine(char* str); // Insert string after current 
	void InsertNextSection(char* str); // Insert string to the same level with subjection next lines
	void InsertDownLine(char* str); // Insert string to the first position on the lower level
	void InsertDownSection(char* str); // Insert subjected header of the lower level

	void DeleteNextLine();
	void DeleteDownLine();

	// Filestream
	bool Load(char* filename);
	void Print(char* filename);

	// Console
	void Print();
	void ShowAll();
};


inline TTextNode* TText::ReadRecursion(ifstream& is)
{
	TTextNode* pHead = nullptr, * pTemp = nullptr;
	char str[81];
	while (!is.eof())
	{
		is.getline(str, 81, '\n');
		if (str[0] == '{') pTemp->pDown = ReadRecursion(is);
		else if (str[0] == '}') break;
		else
		{
			TTextNode* newNode = new TTextNode(str);
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

inline void TText::PrintFileRecursion(TTextNode* pNode, ofstream& file)
{
	if (pNode != nullptr)
	{
		file << pNode->str << endl;
		if (pNode->pDown != nullptr)
		{
			file << '{' << endl;
			PrintFileRecursion(pNode->pDown, file);
			file << '}' << endl;
		}
			
		PrintFileRecursion(pNode->pNext, file);
	}
}

inline void TText::PrintRecursion(TTextNode* pNode, ostream& os, int level)
{
	if (pNode != nullptr)
	{
		for (int i = 0; i < level; i++) os << "\t";

		if (pNode == navCurrent) os << "=>" << pNode->str << endl;
		else os << "  " << pNode->str << endl;

		if (pNode->pDown != nullptr)
		{
			PrintRecursion(pNode->pDown, os, level+1);
		}
		PrintRecursion(pNode->pNext, os, level);
	}
}

inline void TText::CleanMemory()
{
	for (Reset(); !IsEnd(); GoNext()) ptCurrent->garbage = false;
	TTextNode* p = TTextNode::memory.pFree;
	while (p != nullptr)
	{
		p->garbage = false;
		p = p->pNext;
	}
	for (p = TTextNode::memory.pFirst; p <= TTextNode::memory.pLast; p++)
	{
		if (p->garbage) delete p;
		p->garbage = true;
	}
}


inline char* TText::GetNavCurrent()
{
	if (navCurrent == nullptr) throw "Pointer navCurrent is null";
	return navCurrent->str;
}

inline void TText::SetNavCurrent(char* str)
{
	if (navCurrent == nullptr) throw "Pointer navCurrent is null";
	strcpy(navCurrent->str, str);
}

inline char* TText::GetPtCurrent()
{
	if (ptCurrent == nullptr) throw "Pointer ptCurrent is null";
	return ptCurrent->str;
}

inline void TText::SetPtCurrent(char* str)
{
	if (ptCurrent == nullptr) throw "Pointer ptCurrent is null";
	strcpy(ptCurrent->str, str);
}

inline void TText::Reset()
{
	ptStack.Clear();
	if (pFirst == nullptr) return;
	ptCurrent = pFirst;
	ptStack.Push(ptCurrent);
	if (ptCurrent->pNext != nullptr) ptStack.Push(ptCurrent->pNext);
	if (ptCurrent->pDown != nullptr) ptStack.Push(ptCurrent->pDown);
}

inline void TText::GoNext()
{
	ptCurrent = ptStack.Pop();
	if (ptCurrent == pFirst) return;
	if (ptCurrent->pNext != nullptr) ptStack.Push(ptCurrent->pNext);
	if (ptCurrent->pDown != nullptr) ptStack.Push(ptCurrent->pDown);

}

inline bool TText::IsEnd()
{
	return ptStack.IsEmpty();
}

inline void TText::GoNextLine()
{
	if (navCurrent == nullptr || navCurrent->pNext == nullptr) throw "Current pointer don`t exist";
	navStack.Push(navCurrent);
	navCurrent = navCurrent->pNext;
}

inline void TText::GoBackLine()
{
	if (navCurrent == nullptr || navStack.IsEmpty()) throw "Current pointer don`t exist";
	TTextNode* backNode = navStack.Pop();
	navCurrent = backNode;
}

inline void TText::GoDownLine()
{
	if (navCurrent == nullptr || navCurrent->pDown == nullptr) throw "Current pointer don`t exist";
	navStack.Push(navCurrent);
	navCurrent = navCurrent->pDown;
}

inline void TText::GoFirstLine()
{
	navCurrent = pFirst;
	navStack.Clear();
}

inline void TText::InsertNextLine(char* str)
{
	if (navCurrent == nullptr) throw "Current pointer don`t exist";
	TTextNode* newNode = new TTextNode(str);
	newNode->pNext = navCurrent->pNext;
	navCurrent->pNext = newNode;
}

inline void TText::InsertNextSection(char* str)
{
	if (navCurrent == nullptr) throw "Current pointer don`t exist";
	TTextNode* newNode = new TTextNode(str);
	newNode->pDown = navCurrent->pNext;
	navCurrent->pNext = newNode;
}

inline void TText::InsertDownLine(char* str)
{
	if (navCurrent == nullptr) throw "Current pointer don`t exist";
	TTextNode* newNode = new TTextNode(str);
	newNode->pNext = navCurrent->pDown;
	navCurrent->pDown = newNode;
}

inline void TText::InsertDownSection(char* str)
{
	if (navCurrent == nullptr) throw "Current pointer don`t exist";
	TTextNode* newNode = new TTextNode(str);
	newNode->pDown = navCurrent->pDown;
	navCurrent->pDown = newNode;
}

inline void TText::DeleteNextLine()
{
	if (navCurrent != nullptr)
	{
		TTextNode* pDeletable = navCurrent->pNext;
		if (pDeletable != nullptr)
		{
			navCurrent->pNext = pDeletable->pNext;
			delete pDeletable;
		}
	}

}

inline void TText::DeleteDownLine()
{
	if (navCurrent != nullptr)
	{
		TTextNode* pDeletable = navCurrent->pDown;
		if (pDeletable != nullptr)
		{
			navCurrent->pDown = pDeletable->pNext;
			delete pDeletable;
		}
	}
}




bool TText::Load(char* filename)
{
	ifstream file(filename);
	if (file.bad()) return false;
	pFirst = ReadRecursion(file);
	return true;
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

inline void TText::ShowAll()
{
	for (Reset(); !IsEnd(); GoNext())
		cout << GetPtCurrent() << endl;
}
