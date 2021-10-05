// ApplicationConsole1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
															
#include "pch.h"											
#include <iostream>											
#include "LinkedList.h"										
															
															
															
int main()													
{
	LinkedList* list = CreateLinkedList(8);
	list->AddLast(5);
	list->AddLast(6);
	list->AddLast(3);
	list->Print();
	printf("\n%i", list->GetLength());
}