// ApplicationConsole1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "IntArray.hpp"


void Memcpy(char* dst, const char* src, int len) {
	for (int i = 0; i < len; i++) {
		dst[i] = src[i];
	}
}

const char* StrChr(const char* grange, char chat) {
	while (*grange) {
		if (*grange == chat)
			return grange;
		grange++;
	}

	return nullptr;
}

const char* StrStr(const char* a, const char* b) {
	int bCount = strlen(b);
	bool found = false;
	while (*a != 0)
	{
		found = true;
		for (int i = 0; i < bCount; i++) {
			if (*(b + i) != *(a + i)) {
				found = false;
				break;
			}

		}
		if (found)
			return a;
	}
	return nullptr;

}

int add(int a, int b) {
	if (b == 0) return a;
	else
		if (b > 0)
			return 1 + add(a, b - 1);
		else
			return -1 + add(a, b + 1);
}

int sub(int a, int b) {
	return add(a, -b);
}

int mul(int a, int b) {
	if (a == 0) return 0;
	if (b == 0) return 0;

	if (b < 0)
		return -mul(a, -b);
	else
		return add(a, mul(a, b - 1));
}

int divInt(int a, int b) {
	if (a == 0) return 0;
	if (b == 1) return a;
	if (a < b) return 0;
	if (b == 0) throw "Division par zero";

	if ()
	return 1 + divInt(sub(a, b), b);
}

int main()
{
	printf("%i", divInt(6, 1));
}