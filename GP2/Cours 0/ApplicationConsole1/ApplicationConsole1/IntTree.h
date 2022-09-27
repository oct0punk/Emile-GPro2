#pragma once

struct IntTree {
	int value = 0;
	IntTree* left = nullptr;
	IntTree* right = nullptr;

};


int			count(IntTree* head);
IntTree*	create(int value);
IntTree*	insert(IntTree* head, int value);
IntTree*	remove(IntTree* head, int value);
IntTree*	merge(IntTree* a, IntTree* b);