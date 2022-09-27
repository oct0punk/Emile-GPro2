#include "IntTree.h"
#include <stdlib.h>
#include <cstring>
#include <iostream>

IntTree* create(int val) {
	IntTree* tree = (IntTree*)malloc(sizeof(IntTree));
	tree->value = val;
	tree->left = nullptr;
	tree->right = nullptr;
	return tree;
}

int count(IntTree* head) {
	if (!head) return 0;
	return 1 + count(head->left) + count(head->right);
}

IntTree* insert(IntTree* head, int val) {
	if (!head)
		return create(val);

	if (head->value > val)
		head->left = insert(head->left, val);
	else
		head->right = insert(head->right, val);
	return head;
}

IntTree* remove(IntTree* head, int val)
{
	if (!head) return head;
	if (head->value == val)
	{
		IntTree* merged = merge(head->left, head->right);		
		free(head);
		return merged;
	}
	head->left = remove(head->left, val);
	head->right = remove(head->right, val);
	return head;
}

IntTree* merge(IntTree* a, IntTree* b) {

	if (!a) return b;
	if (!b) return a;
	    
	IntTree* fg = a->left;
	IntTree* fd = a->right;
	int val = a->value;
	free(a);

	b = insert(b, val);

	b = merge(fg, b);
	b = merge(fd, b);

	return b;
}



int main0() {

	IntTree* tree = create(10);

	tree = insert(tree, 5);
	tree = insert(tree, 7);
	tree = insert(tree, 6);
	tree = insert(tree, 3);
	tree = insert(tree, 4);
	tree = insert(tree, 2);
	tree = insert(tree, 1);

	tree = remove(tree, 5);
	
	return 0;
}