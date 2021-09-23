// ApplicationConsole1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "Vec4.h"

struct Vec {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vec(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

int main()
{
	/*Vec4 vec;
	vec.Set(1.0f, 4.0f, 7.0, 0.0f);
	printf("%f %f %f %f\n", vec.x, vec.y, vec.z, vec.w);

	Vec4 vec2;
	vec2.Set(-0.1f, 0.2f, -3.2f, 1.0f);
	printf("%f %f %f %f\n", vec2.x, vec2.y, vec2.z, vec2.w);

	Vec4 add = vec.Add(vec2);
	printf("%f %s %f %s %f %s %f\n", add.x, ",", add.y, ",", add.z, ",", add.w);*/

	int tab[] = { 1, 2, 3, 4 };
	printf("%i\n %i\n %i\n %i\n", *&tab[0], *&tab[1], *&tab[2], *&tab[3]);
}
