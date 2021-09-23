#pragma once

#include <cstdlib>

class IntArray {
public :
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
		delete [] data;
	}

	void Set(int idx, int value) {
		// Récupérer la donnée à la case idx et l'affecter
		if ((idx < 0) || (idx > length))
			throw "exception:out of bounds";
		data[idx] = value;
	};

	int Get(int idx) {
		//Récupérer la donnée à l'index

		if ((idx < 0) || (idx > length))
			throw "exception:out of bounds";

		return data[idx];
	}
};