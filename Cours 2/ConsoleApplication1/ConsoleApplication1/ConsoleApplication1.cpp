// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "IntArray.h"

int main()
{
	Int64Array totogro(12);
	for (int i = 0; i < totogro.maxSize; i++) {
		totogro.set_unsafe(i, i * i);
		printf("%lli\n", totogro[i]);
	}
	totogro.push_front(666);
	for (int i = 0; i < totogro.maxSize; i++) {
		printf("%lli\n", totogro[i]);
	}
	
}
