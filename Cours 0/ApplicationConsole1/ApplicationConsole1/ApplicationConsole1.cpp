// ApplicationConsole1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"											
#include <iostream>
#include "IntList.h"



int main()
{
	IntList* tata = (IntList*)malloc(sizeof(IntList));
	tata->value = 90;

	if (IntList::length(tata) != 1) throw "alarm?";
	if (IntList::length(0) != 0) throw "alarm?";

	tata = IntList::appendFirst(tata, 33);
	if (IntList::length(tata) != 2) throw "alarm?";
	IntList::remove(tata, 33);
	if (IntList::length(tata) != 0) throw "alarm?";
	
	

}