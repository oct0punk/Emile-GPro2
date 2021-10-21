#include "IntArray.h"

Int64Array::Int64Array(int size) {
	if (size < 0) size = 0;
	curSize = size;
	if (size <= 0)
		maxSize = 16;
	else
		maxSize = size;

	data = (int64_t*)malloc(maxSize * sizeof(int64_t));

	zero(0, maxSize);
}

void Int64Array::zero(int idx, int nbElem) {
	memset(data + idx, 0, nbElem * sizeof(int64_t));
}

void Int64Array::ensure(int size) { //s’assure que le tableau fait au moins size
	if (size < maxSize)
		return;
	int oldSize = maxSize;
	maxSize = size * 1.75;
	data = (int64_t*)realloc(data, maxSize * sizeof(int64_t));
	zero(oldSize, maxSize - oldSize);
}

void Int64Array::ensureNew(int size) { //s’assure que le tableau fait au moins size
	if (size < maxSize)
		return;
	int oldSize = maxSize;
	maxSize = size;
	int64_t* oldData = data;
	data = new int64_t[size];
	memcpy(data, oldData, oldSize * sizeof(int64_t));
	delete[]oldData;
	zero(oldSize, maxSize);
}

void Int64Array::set_unsafe(int pos, int64_t elem) {
	data[pos] = elem;
}

void Int64Array::set(int pos, int64_t elem) //meme chose avec ensure voir throw si hors borne
{
	ensure(pos + 1);
	data[pos] = elem;
	if (pos >= curSize)
		curSize = pos + 1;
}

void Int64Array::append_sorted(const int* arr, int sz) { // Crée un tableau de int trié
	if (sz <= 0) return;
	insert_ordered(*arr);
	append_sorted(arr + 1, sz - 1);
}

void Int64Array::insertion_sort(const int* arr, int sz) {
	clear();
	load(arr, sz);
	int j;
	for (int i = 1; i < curSize; i++) {
		j = i;
		while (j > 0 && data[j] < data[j - 1]) {
			int64_t tmp = data[j];
			data[j] = data[j - 1];
			data[j - 1] = tmp;
			j--;
		}
	}
}

void Int64Array::push_back(int64_t elem) {
	set(curSize, elem);
}

int64_t& Int64Array::get(int pos) {
	ensure(pos + 1);
	if (pos >= curSize)
		curSize = pos + 1;
	return data[pos];
}

void Int64Array::push_front(int64_t elem) {
	insert(0, elem);
}

void Int64Array::shift_right(int pos) {
	ensure(maxSize + 1);
	shift_from_to(pos, maxSize);
}

void Int64Array::shift_from_to(int end, int node) {
	if (node <= end) return;
	data[node] = data[node - 1];
	shift_from_to(end, node - 1);
}

void Int64Array::insert(int pos, int64_t elem) {
	shift_right(pos);
	set(pos, elem);
}

void Int64Array::insert_ordered(int64_t elem) {
	int pos = search_position(elem, 0);
	insert(pos, elem);
}

int Int64Array::search_position(int64_t elem, int idx) {
	if (idx >= curSize) return curSize;
	if (data[idx + 1] >= elem) return idx;
	return search_position(elem, idx + 1);
}

void Int64Array::load(const int* arr, int sz) { // Crée un tableau de int
	if (sz == 0)
		return;
	set(curSize, *arr);
	load(arr + 1, sz - 1);
}


Int64Array::~Int64Array() {
	free(data);
	data = nullptr;
	maxSize = 0;
	curSize = 0;
}
