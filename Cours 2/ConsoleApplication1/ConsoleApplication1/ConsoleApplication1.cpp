// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "IntArray.h"
#include <ctime>
#include <chrono>
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
	srand(0);
	Int64Array ti6;
	double t0 = getTimeStamp();
	for (int i = 0; i < 1000; i++) {
		ti6.PushBack(rand());
	}
	double t1 = getTimeStamp();
	printf("time elapsed : %lld\n", (t1 - t0));
}
