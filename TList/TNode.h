#pragma once
template <class T>
struct TNode
{
	T value;
	TNode<T>* pNext;
};

template <class T>
int CountNodes(TNode<T>* firstNode)
{
	TNode<T>* node = firstNode;
	int result = 0;
	while (node != nullptr)
	{
		node = node->pNext;
		result++;
	}
	return result;

}

template <class T>
void AddNewNode(TNode<T>* firstNode, int value)
{
	TNode<T>* node = firstNode;
	while (node->pNext != nullptr)
	{
		node = node->pNext;
	}
	TNode<T>* newNode = new TNode();
	newNode->value = value;
	node->pNext = newNode;
}

template <class T>
void DeleteNode(TNode<T>* firstNode, int elem)
{
	TNode<T>* node = firstNode;
	TNode<T>* prevNode = nullptr;

	while (node->value != elem)
	{
		node = node->pNext;
		prevNode = node;
	}
	prevNode->pNext = node->pNext;
	delete node;



}