#pragma once
#include <cstring>
#include <stdlib.h>

class List {
public:
	double val = 0.0;
	List* next = nullptr;

	List(double elem) {
		val = elem;
	}

	List(double elem, List* next) {
		val = elem;
		this->next = next;
	}


	List* PushFirst(List* list, double elem) {
		return new List(elem, list);
	}

	List* PushBack(List* node, double elem) {
		if (node->next) return PushBack(node->next, elem);
		node->next = (List*)malloc(sizeof(List));
		node->next->val = elem;
	}

	List* Remove(double elem) {
		if (val == elem) {
			List* rest = next;
			delete this;
			return rest;
		}
		if (next)
			return next->Remove(elem);
		return this;
	}
};

