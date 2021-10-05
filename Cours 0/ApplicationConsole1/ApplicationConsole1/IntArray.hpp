#pragma once

#include <cstdlib>

class IntArray {
public:
	int* data = nullptr;
	int length;

public:
	IntArray() {
		// Faire l'allocation dynamique de data qui sera de taille "suffisamment grande"
		data = new int[65536];
		length = 65536;
	};

	IntArray(int size) {
		// Faire l'allocation dynamique de data qui sera de taille "suffisamment grande"
		data = new int[size];
		length = size;
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
		int resz = idx > length ?
			idx + 1 : length + 1;
		Resize(resz);
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


	static int cmp(const void* v0, const void* v1) {

		return (*(int*)v1 - *(int*)v0) < 0;
	}

	void Sort() {
		::qsort(data, length, sizeof(int), cmp);
	}


	int Get(int idx) {
		//Récupérer la donnée à l'index

		if ((idx < 0) || (idx > length))
			throw "exception:out of bounds";

		return data[idx];
	}


	void Resize(int newSize) {
		if (length >= newSize)
			return;

		int* ndata = new int[newSize];
		for (int i = 0; i < length; i++) {
			ndata[i] = data[i];
		}
		for (int i = length; i < newSize; i++) {
			ndata[i] = 0;
		}
		int* oldData = data;
		this->data = ndata;
		delete oldData;
		length = newSize;
	}
};