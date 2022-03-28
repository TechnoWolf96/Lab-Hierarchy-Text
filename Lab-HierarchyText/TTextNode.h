#pragma once
#include <iostream>
#include <cstring>
using namespace std;


struct TTextNode;

struct TMemory
{
	TTextNode* pFirst;
	TTextNode* pFree;
	TTextNode* pLast;
};

struct TTextNode
{
	static TMemory memory;
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

	static void InitializeMemory(size_t size)
	{
		memory.pFirst = (TTextNode*) new char[size * sizeof(TTextNode)];
		memory.pFree = memory.pFirst;
		memory.pLast = memory.pFirst + (size - 1);
		TTextNode* p = memory.pFirst;
		for (int i = 0; i < size - 1; i++)
		{
			p->pNext = p + 1;
			strcpy(p->str, "empty");
			p->garbage = true;

			p += 1;
		}
		memory.pLast->pNext = nullptr;
		strcpy(memory.pLast->str, "empty");
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
		TTextNode* tmp = memory.pFree;
		if (tmp == nullptr) throw "Have not memory";
		memory.pFree = memory.pFree->pNext;
		return tmp;
	}
	void operator delete(void* p)
	{
		TTextNode* pNode = (TTextNode*)p;
		pNode->pNext = memory.pFree;
		memory.pFree = pNode;
	}

	~TTextNode() {}

};
