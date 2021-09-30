#pragma once

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
		Node* crématorium = First->Next;
		free(First);
		First = crématorium;
	}
	
	void RemoveLast() {
		Node* node = First;
		while (node->Next != nullptr)
			node = node->Next;
		free(node);
	}

	void Print() {
		Node* node = First;
		while (node != nullptr) {
			printf("%i, ", node->value);
			node = node->Next;
		}
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