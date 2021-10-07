#include "pch.h"
#include "IntList.h"

IntList* IntList::appendFirst(IntList* l, int value) {
	IntList* v = (IntList*)malloc(sizeof(IntList));
	v->value = value;
	v->next = l;
	return v;
}

IntList* IntList::appendLast(IntList* l, int value) {
	if (!l)
		return appendFirst(l, value);
	
	if (l->next)
		return appendLast(l->next, value);
	else
		l->next = appendFirst(nullptr, value);
	return l;
}


IntList* IntList::remove(IntList* l, int value) {
	if (!l) return nullptr;
	if (l->value == value) {
		IntList* rest = l->next;
		free(l);
		return rest;
	}
	else {
		return l->next = remove(l->next, value);
		return l;
	}
}

int IntList::length(IntList* l) {
	if (!l)		return 0;
	else		return 1 + length(l->next);
}
