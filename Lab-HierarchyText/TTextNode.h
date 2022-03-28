#pragma once
#include <iostream>
#include <cstring>
using namespace std;

/*
struct TTextNode;

struct TMemory
{
	TTextNode* pFirst;
	TTextNode* pFree;
	TTextNode *pLast;
};
*/

struct TTextNode
{
	//static TMemory memory;
	char str[81];
	TTextNode* pNext, * pDown;
	bool garbage;

	TTextNode(char* str = nullptr)
	{
		this->pNext = nullptr;
		this->pDown = nullptr;
		if (str == nullptr) this->str[0] = '\0';
		else strcpy(this->str, str);
	}
	/*
	static void InitializeMemory(size_t size)
	{
		memory.pFirst = (TTextNode*)new char[sizeof(TTextNode) * size];
		memory.pFree = memory.pFirst;
		memory.pLast = memory.pFirst + (size - 1);
		for (TTextNode* p = memory.pFirst; p != memory.pLast; p++)
		{
			p->str[0] = '\0';
			p->pNext = p + 1;
			p->garbage = true;
		}
		memory.pLast->pNext = nullptr;
		memory.pLast->str[0] = '\0';
		memory.pLast->garbage = true;
	}
	static void PrintFree()
	{
		TTextNode* p = memory.pFree;
		while (p != nullptr)
		{
			cout << p->str << endl;
			p = p->pNext;
		}

	}


	void* operator new(size_t size)
	{
		TTextNode* res = memory.pFree;
		if (res != nullptr) memory.pFree = memory.pFree->pNext;
		return res;
	}
	void operator delete(void* p)
	{
		TTextNode* pNode = (TTextNode*)p;
		pNode->pNext = memory.pFree;
		memory.pFree = pNode;
	}
	*/
	~TTextNode() {}

};
