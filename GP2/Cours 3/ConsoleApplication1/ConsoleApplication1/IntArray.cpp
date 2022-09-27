#include "IntArray.h"
#include <cstring>

Int64Array::Int64Array(int size) {
	data = (int64_t*)malloc(sizeof(int64_t) * size);
	maxSize = size;
	curSize = 0;

	zero(0, maxSize);
}

Int64Array::~Int64Array() {
	data = nullptr;
	free(data);
	curSize = 0;
	maxSize = 0;
	delete data;
}

void Int64Array::zero(int end, int start) {
	if (start < end) return;
	if (start >= end) {
		Set_Unsafe(start, 0);
		return zero(end, start - 1);
	}
}

void Int64Array::Ensure(int size) {
	if (maxSize >= size)
		return;

	int oldSize = maxSize;
	maxSize = size;
	data = (int64_t*)realloc(data, sizeof(int64_t) * size);

	zero(oldSize, maxSize);
}

void Int64Array::ShiftRight(int end, int idx) {
	if (idx < end) return;
	if (idx == end) return	Set_Unsafe(end, 0);
	Set_Unsafe(idx, data[idx - 1]);
	ShiftRight(end, idx - 1);
}

int Int64Array::GetOrderedIndex(int idx, int64_t value) {
	if (idx > maxSize) return maxSize;
	if (data[idx] > value) return idx;
	return GetOrderedIndex(idx + 1, value);
}

void Int64Array::Set_Unsafe(int idx, int64_t value) {
	data[idx] = value;
	if (idx > curSize)
		curSize = idx;
}

void Int64Array::Set(int idx, int64_t value) {
	if (idx < 0) throw "NegativeIndex : Exception";
	Ensure(idx + 1);
	Set_Unsafe(idx, value);
}

void Int64Array::InsertAt(int idx, int64_t value) {
	if (idx > curSize)
		Ensure(idx + 1);
	else
		Ensure(curSize + 1);
	ShiftRight(idx, curSize);
	Set_Unsafe(idx, value);
}

void Int64Array::InsertOrdered(int64_t value) {
	int idx = GetOrderedIndex(0, value);
	Ensure(curSize + 1);
	ShiftRight(idx, maxSize);
	Set(idx, value);
}

void Int64Array::PushBack(int64_t value) {
	Set(maxSize, value);
}

void Int64Array::PushFront(int64_t value) {
	Ensure(curSize + 1);
	ShiftRight(0, curSize);
	Set_Unsafe(0, value);
}

int64_t& Int64Array::Get(int idx) {
	return data[idx];
}
