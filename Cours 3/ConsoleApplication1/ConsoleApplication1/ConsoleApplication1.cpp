// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "IntArray.h"
#include <ctime>
#include <chrono>
#include "List.h"
using namespace std;
using namespace std::chrono;

double getTimeStamp() //retourne le temps actuel en seconde
{
	std::chrono::nanoseconds ns =
		duration_cast<std::chrono::nanoseconds>(system_clock::now().time_since_epoch());
	return ns.count() / 1000000000.0;
}

int main()
{	
	List* list = new List(1.0);
	list = list->PushFirst(list, 67.98);
	list = list->PushFirst(list, 6798.546);
	list = list->PushFirst(list, 0.6666);
	list->Remove(1.0);
}
