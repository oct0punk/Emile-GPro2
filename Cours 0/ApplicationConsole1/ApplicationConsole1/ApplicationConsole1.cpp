// ApplicationConsole1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>


int Countc(const char* maChaine, char c) {
	int occur = 0;
	const char* pointeur = maChaine;
	while (*pointeur != 0) {
		if (*pointeur == c)
			occur++;
		pointeur++;
	}
	return occur;
}

int strLen(const char* maChaine) {
	int count = 0;
	const char* index = maChaine;
	while (*index++ != 0)
		count++;
	return count;
}


void Strcpy(char* dest, const char* maChaine) {
	int count = 0;
	for (char* i = dest; i < dest + strLen(maChaine); i++) {
		*i = *(maChaine + count);
		count++;
	}
	*(dest + count) = 0;
}

void Strncpy(char* dest, const char* maChaine, int nchars) {
	int count = 0;
	bool zeroFound = false;
	for (char* i = dest; i < dest + nchars; i++) {

		if (zeroFound)
			*i = 0;
		else
			*i = *(maChaine + count);
		count++;
	}
	*(dest + count) = 0;
}


int main()
{
	const char* str = "epuisette";
	char* dest = (char*)malloc(sizeof(char)*strLen(str));
	int n = 3;
	Strncpy(dest, str, n);

	for (char* i = dest; i < (dest + n); i++) {
		printf("%c", *i);
	}

	return 0;
}
