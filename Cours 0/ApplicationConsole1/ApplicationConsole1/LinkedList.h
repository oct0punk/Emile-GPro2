#pragma once
#include <stdlib.h>
#include <malloc.h>
#include <iostream>

struct Node {
	int value;
	Node* Next;
};

struct LinkedList {
	Node* First;

	void AddLast(int val) {
		Node* insert = (Node*)malloc(sizeof(Node));
		Node* node = First;
		while (node->Next != nullptr)
			node = node->Next;
		node->Next = insert;
		node->Next->value = val;
		node->Next->Next = nullptr;
	}

	void RemoveFirst() {
		Node* newFirst = First->Next;
		free(First);
		First = newFirst;
	}
	
	void RemoveLast() {
		Node* node = First;
		while (node->Next->Next != nullptr)
			node = node->Next;
		node->Next = nullptr;
		free(node->Next);
	}

	void Print() {
		Node* node = First;
		while (node != nullptr) {
			printf("%i, ", node->value);
			node = node->Next;
		}
	}

	int GetLength() {
		Node* node = First;
		int count = 1;
		while (node->Next != nullptr) {
			node = node->Next;
			count++;
		}
		return count;
	}

};


LinkedList* CreateLinkedList(int firstVal) {
	LinkedList* listPtr = (LinkedList*)malloc(sizeof(LinkedList));
	Node* first = (Node*)malloc(sizeof(Node));
	listPtr->First = first;
	first->value = firstVal;
	first->Next = nullptr;
	return listPtr;
}