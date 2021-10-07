#pragma once
#include <utility>
#include <cstdlib>
#include <cstring>

class IntArray {
public:
	int* data = nullptr;
	int length;

public:
	IntArray() {
		// Faire l'allocation dynamique de data qui sera de taille "suffisamment grande"
		data = new int[length = 65536];
		memset(data, 0, 65535 * sizeof(int));
	};

	IntArray(int size) {
		// Faire l'allocation dynamique de data qui sera de taille "suffisamment grande"
		data = new int[length = size];
		memset(data, 0, size * sizeof(int));
	};

	~IntArray() {
		delete[] data;
	}



	void Set(int idx, int value) {
		// Récupérer la donnée à la case idx et l'affecter
		if ((idx < 0) || (idx > length))
			throw "exception:out of bounds";
		data[idx] = value;
	};

	void InsertAt(int idx, int value) {
		int sz = length;
		Resize(std::max<int>(idx + 1, length + 1));
		for (; sz > idx; sz--)
			data[sz] = data[sz - 1];
		data[idx] = value;
	}

	void Insert(int value) {
		int idx = 0;
		while ((idx < length) && (data[idx] < value))
			idx++;
		InsertAt(idx, value);
	}

	void InsertAtMove(int idx, int value) {
		int sz = length;
		Resize(std::max<int>(idx + 1, length + 1));
		memmove(&data[idx + 1], &data[idx], (sz - idx) * sizeof(int));
		data[idx] = value;
	}

	int Get(int idx) {
		//Récupérer la donnée à l'index

		if ((idx < 0) || (idx > length))
			throw "exception:out of bounds";

		return data[idx];
	}


	static int cmp(const void* v0, const void* v1) {

		return (*(int*)v1 - *(int*)v0);
	}

	void Sort() {
		::qsort(data, length, sizeof(int), cmp);
	}

	void Resize(int newSize) {
		int* ndata = new int[newSize];
		memset(ndata, 0, newSize * sizeof(int));
		memcpy(ndata, data, length * sizeof(int));
		int* oldData = data;
		this->data = ndata;
		delete oldData;
		length = newSize;
	}

};