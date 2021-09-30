#pragma once

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
