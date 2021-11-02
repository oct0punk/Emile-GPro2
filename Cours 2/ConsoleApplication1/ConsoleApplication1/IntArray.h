#pragma once
#include<stdlib.h>
#include<cstring>
#include<stdint.h>

class Int64Array {
public:
	int64_t* data = nullptr;
	int maxSize = 0;
	int curSize = 0;


	Int64Array(int size = 0);

	~Int64Array();

private:
	void zero(int end, int start);

	void Ensure(int size);

	void ShiftRight(int end, int idx);

	int GetOrderedIndex(int idx, int64_t value);

public:
	void Set_Unsafe(int idx, int64_t value);

	void Set(int idx, int64_t value);

	void InsertAt(int idx, int64_t value);

	void InsertOrdered(int64_t value);

	void PushBack(int64_t value);

	void PushFront(int64_t value);

	int64_t& Get(int idx);

	int64_t& operator[] (int idx) {
		return Get(idx);
	}

};