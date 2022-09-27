#pragma once
#include <cstring>
#include <stdlib.h>

template<typename Type>
class List {
public:
	Type val;
	List* next = nullptr;

	List(Type elem) {
		val = elem;
	}

	List(Type elem, List* next) {
		val = elem;
		this->next = next;
	}


	List* PushFirst(List* list, Type elem) {
		return new List(elem, list);
	}

	List* PushBack(Type elem) {
		if (!next)
			next = new List(elem);
		else
			next->PushBack(elem);
		return next;
	}

	List* Remove(Type elem) {
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

