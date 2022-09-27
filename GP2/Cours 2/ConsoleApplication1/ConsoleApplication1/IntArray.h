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

	int bSearch(int64_t elem, int low, int high) {		
		int middle = (low + high) / 2; // pointer to Check
		
		if (data[low] == elem) return low;
		if (data[middle] == elem)		// find the index
			return middle;
		if (data[high] == elem) return high;

		if (low >= high) return -1;		// there is no middle

		if  (data[middle] > elem)	return bSearch(elem, low, middle - 1);	// Search in lower part
		else						return bSearch(elem, middle + 1, high);	//	or upper 
	}


	int bSearchIter(int64_t elem) {
		int low = 0; 
		int high = curSize - 1;
		bool found = false;

		while (true) {
			int middle = (low + high) / 2;

			if (data[low] == elem) return low;
			if (data[middle] == elem)		// find the index
				return middle;
			if (data[high] == elem) return high;

			if (low >= high) return -1;		// there is no middle

			if (data[middle] > elem) high = middle - 1;
			else low = middle + 1;
		}
	}

	int64_t& Get(int idx);

	int64_t& operator[] (int idx) {
		return Get(idx);
	}

};