// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <ctime>
#include <chrono>
#include "List.h"
#include <vector>

using namespace std;
using namespace std::chrono;

double getTimeStamp() //retourne le temps actuel en seconde
{
	std::chrono::nanoseconds ns =
		duration_cast<std::chrono::nanoseconds>(system_clock::now().time_since_epoch());
	return ns.count() / 1000000000.0;
}

typedef List<double>		ListD;
typedef List<float>			ListF;
typedef List<int>			ListI;
typedef List<std::string>	ListS;


int main()
{	
	std::vector<double> vd = { 0.0, 1.0, 2.0 };
	vd.push_back(13);
	vd[0] = 14;
	for (int i = 0; i < vd.size(); i++) {
		printf("%f", vd[i]);
	}
	printf("\n------------");

	for (auto f : vd) {
		printf("%f", f);
	}
	printf("\n------------");

	for (auto iter = vd.begin(); iter != vd.end();) {
		printf("%f", *iter);
		if (*iter == 1.0)
			iter = vd.erase(iter);
		else
			iter++;
	}
	printf("\n------------");

}
