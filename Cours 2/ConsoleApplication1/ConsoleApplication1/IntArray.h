#pragma once
#include <cstdint>
#include <cstring>
#include <malloc.h>


class Int64Array {
public:
	int64_t* data = nullptr;

	int maxSize = 0;
	int curSize = 0;

	Int64Array(int size = 0);

	void zero(int idx, int nbElem);

	void ensure(int size);

	void ensureNew(int size);

	void set_unsafe(int pos, int64_t elem);

	void set(int pos, int64_t elem);;

	void insert(int pos, int64_t elem);

	void shift_right(int pos);

	void shift_from_to(int end, int node);

	void insert_ordered(int64_t elem);

	int search_position(int64_t elem, int node);

	void load(const int* arr, int sz);

	void append_sorted(const int* arr, int sz);

	void clear() {
		curSize = 0;
	}

	void insertion_sort(const int* arr, int sz);

	void push_back(int64_t elem);

	void push_front(int64_t elem);

	int64_t& get(int pos);

	int64_t& operator[](int idx) {
		return get(idx);
	};

	~Int64Array();
};


