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

int main()
{
	const char* str = "epuisette";
	char* dest = (char*)malloc(sizeof(char)*strLen(str));
	Strcpy(dest, str);

	return 0;
}
