#pragma once
#include <utility>
#include <cstdlib>
#include <cstring>
#include <functional>

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


	int Get(int idx);

	void Set(int idx, int value);

	void Insert(int value);

	void InsertAt(int idx, int value);

	void InsertAtMove(int idx, int value);


	void Sort();

	void Resize(int newSize);

	void Reverse();


	void Iter(std::function<void(int)> f);

	double Sum();

	IntArray* fromArray(int* data, int len);
};