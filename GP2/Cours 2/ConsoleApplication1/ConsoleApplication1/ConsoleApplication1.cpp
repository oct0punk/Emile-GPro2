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
	Int64Array toto;
	for (int i = 0; i < 5000; i++) {
		toto.PushBack(i*i);
	}
	printf("\n");

	{
		double t0 = getTimeStamp();
		for (int i = 0; i < toto.curSize - 1; i++) {
			int64_t random = (rand() % toto.curSize * toto.curSize);
			int idx = toto.bSearch(random, 0, toto.curSize - 1);
		}
		double t1 = getTimeStamp();
		printf("\nRecursive time elapsed : %llf", (t1 - t0));
	}
	{
		double t0 = getTimeStamp();
		for (int i = 0; i < toto.curSize - 1; i++) {
			int64_t random = (rand() % toto.curSize * toto.curSize);
			int idx = toto.bSearchIter(random);
		}
		double t1 = getTimeStamp();
		printf("\nIterative time elapsed : %llf\n", (t1 - t0));
	}

}
