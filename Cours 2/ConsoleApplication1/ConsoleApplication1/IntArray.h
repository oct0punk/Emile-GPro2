#pragma once


class Int64Array {
public:
	int64_t* data = nullptr;
	int maxSize = 0;
	int curSize = 0;


	Int64Array(int size = 0) {
		if (size < 0) size = 0;
		curSize = size;
		if (size <= 0)
			maxSize = 16;
		else
			maxSize = size;

		data = (int64_t*)malloc(sizeof(int64_t) * maxSize);

		zero(0, maxSize);
	}

	~Int64Array() {
		free(data);
		data = nullptr;
		maxSize = 0;
		curSize = 0;
	}

	void zero(int idx, int nbElem) {
		if (idx >= nbElem) return;
		data[idx] = 0;
		zero(++idx, nbElem);
	}

	void ensure(int size) {
		if (size < maxSize) return;
		int oldSize = maxSize;
		maxSize = size;
		data = (int64_t*)malloc(sizeof(int64_t) * maxSize);
		zero(oldSize - 1, maxSize);
	}

	void set_unsafe(int pos, int64_t elem) {
		data[pos] = elem;
	}

	void set(int pos, int64_t elem) {
		ensure(pos + 1);
		data[pos] = elem;
		if (pos > curSize)
			curSize = pos + 1;
	}

	void push_back(int64_t elem) {
		set(maxSize, elem);
	}

	void push_front(int64_t elem) {
		if (data[maxSize] != 0)
			ensure(curSize + 1);
		shift_right(0, elem);
	}

	void shift_right(int pos, int64_t elem) {
		if (pos >= curSize) return;
		int64_t old = data[pos];
		data[pos] = elem;
		return shift_right(pos+1, old);
	}

	int64_t& get(int pos) {
		ensure(pos + 1);
		curSize = pos + 1;
		return data[pos];
	}

	int64_t& operator[](int pos) {
		return get(pos);
	}
};


