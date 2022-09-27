
#include "pch.h"
#include "IntArray.hpp"


void IntArray::Set(int idx, int value) {
	// Récupérer la donnée à la case idx et l'affecter
	if ((idx < 0) || (idx > length))
		throw "exception:out of bounds";
	data[idx] = value;
};

void IntArray::InsertAt(int idx, int value) {
	int sz = length;
	Resize(std::max<int>(idx + 1, length + 1));
	for (; sz > idx; sz--)
		data[sz] = data[sz - 1];
	data[idx] = value;
}

void IntArray::Insert(int value) {
	int idx = 0;
	while ((idx < length) && (data[idx] < value))
		idx++;
	InsertAt(idx, value);
}

void IntArray::InsertAtMove(int idx, int value) {
	int sz = length;
	Resize(std::max<int>(idx + 1, length + 1));
	memmove(&data[idx + 1], &data[idx], (sz - idx) * sizeof(int));
	data[idx] = value;
}

int IntArray::Get(int idx) {
	//Récupérer la donnée à l'index

	if ((idx < 0) || (idx > length))
		throw "exception:out of bounds";

	return data[idx];
}


static int cmp(const void* v0, const void* v1) {

	return (*(int*)v1 - *(int*)v0);
}

void IntArray::Sort() {
	::qsort(data, length, sizeof(int), cmp);
}

void IntArray::Resize(int newSize) {
	int* ndata = new int[newSize];
	memset(ndata, 0, newSize * sizeof(int));
	memcpy(ndata, data, length * sizeof(int));
	int* oldData = data;
	this->data = ndata;
	delete oldData;
	length = newSize;
}

void IntArray::Reverse() {
	for (int i = data[0]; i < length / 2; i++) {
		int old = i;
		data[i] = data[length - i - 1];
		data[length - i - 1] = old;
	}
}

void IntArray::Iter(std::function<void(int)> f) {
	for (int i = 0; i < length; i++) {
		f(data[i]);
	}
}

static double tempRes;

double IntArray::Sum() {
	tempRes = 0.0;

	std::function<void(int)> add = [](int value) {
		tempRes += value;
	};
	Iter(add);

	return tempRes;
}

IntArray* IntArray::fromArray(int* data, int len) {
	IntArray* data2 = new IntArray(len);
	memcpy(data2->data, data, len * sizeof(int));
	return data2;
}