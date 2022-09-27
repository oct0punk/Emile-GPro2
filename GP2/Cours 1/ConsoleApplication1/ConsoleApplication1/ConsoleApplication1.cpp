// ApplicationConsole1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>


void Memcpy(char* dst, const char* src, int len) {
	for (int i = 0; i < len; i++) {
		dst[i] = src[i];
	}
}

const char* StrChr(const char* grange, char chat) {
	while (*grange) {
		if (*grange == chat)
			return grange;
		grange++;
	}

	return nullptr;
}

const char* StrStr(const char* a, const char* b) {
	int bCount = strlen(b);
	bool found = false;
	while (*a != 0)
	{
		found = true;
		for (int i = 0; i < bCount; i++) {
			if (*(b + i) != *(a + i)) {
				found = false;
				break;
			}

		}
		if (found)
			return a;
	}
	return nullptr;

}

#pragma region RecOps
int add(int a, int b) {
	if (b == 0) return a;
	else
		if (b > 0)
			return 1 + add(a, b - 1);
		else
			return -1 + add(a, b + 1);
}

int sub(int a, int b) {
	return add(a, -b);
}

int mul(int a, int b) {
	if (a == 0) return 0;
	if (b == 0) return 0;

	if (b < 0)
		return -mul(a, -b);
	else
		return add(a, mul(a, b - 1));
}

int divInt(int a, int b) {
	if (a == 0) return 0;
	if (b == 1) return a;
	if (b == 0) throw "division by zero";
	if (a < 0)  return sub(0, divInt(sub(0, a), b));
	if (a < b)  return 0;
	return 1 + divInt(sub(a, b), b);
}

int modulo(int a, int b) {
	return mul(sub(a, divInt(a, b)), b);
}
#pragma endregion

#pragma region RecStr
int StrLen(const char* str) {
	if (*str == 0)
		return 0;
	if (!str)
		return 0;
	else
		return 1 + StrLen(str+1);
}

void StrCpy(char* dest, const char* str) {
	if (dest == nullptr) return;
	if (str == nullptr) return;
	if (*str == 0) return;
	
	*dest = *str;
	dest++;
	str++;
	StrCpy(dest, str);
}

void StrNCpy(char* dest, const char* str, int n) {	
	if (dest == nullptr) return;
	if (str == nullptr) return;
	if (*str == 0) return;
	if (n < 1) return;

	*dest = *str;
	dest++;
	str++;
	StrNCpy(dest, str, n - 1);
}

void ZeroMemory(void* ptr, int nbByte) {
	char* mem = (char*)ptr;
	if (!mem) return;
	if (!nbByte) return;
	*mem = 0;
	mem++;

	ZeroMemory(mem, nbByte - 1);
}

void MemCpy(void* dest, const void* src, int nbByte) {
	if (!src) return;
	if (nbByte < 1) return;
	
	char* bDst = (char*)dest;
	const char* bSrc = (const char*)src;

	*bDst = *bSrc;
	MemCpy(bDst + 1, bSrc + 1, nbByte - 1);
}

const char* StrChrRec(const char* str, char token) {
	if (!str) return nullptr;
	if (*str == token)
		return str;
	return StrChr(str + 1, token);
}

bool StrEqual(const char* str, const char* sub) {
	if (*str != *sub)
		return false;
	else
		if (sub[1] == 0)
			return true;
		else
			return StrEqual(str + 1, sub + 1);
}

const char* StrStrRec(const char* str, const char* sub) {
	if (nullptr == str) return nullptr;
	if (str[0])			return nullptr;
	if (nullptr == sub) return nullptr;

	if (StrEqual(str, sub))
		return str;
	return StrStrRec(str + 1, sub);
}

char* FindEnd(char* str) {
	if (str == nullptr) return nullptr;
	if (str[0]) {
		if (*str == 0)
			return str;
		else
			return FindEnd(str + 1);
	}
}

char* StrCat(char* dest, char* src) {
	if (nullptr == dest) return nullptr;

	char* dstEnd = FindEnd(dest);


}

int StrCmp(const char* a, const char* b) {
	if (*a == *b) {
		if (*a == 0) {
			return 0;
		}
		return StrCmp(a + 1, b + 1);
	}
	else
		return *a < *b ? -1 : 1;
}
#pragma endregion

#pragma region ExplicitOps

int mulExplicit(int a, int b, int tempResult) {
	if (b == 0) return tempResult;
	if (a == 0) return 0;

	if (b > 0)
		return mulExplicit(a, b - 1, tempResult + a);
	return mulExplicit(a, b + 1, tempResult - a);
}

int divIntExplicit(int a, int b, int tempResult) {
	if (a == 0) return 0;
	if (b == 1) return 1;
	if (b == 0) throw "non";
	if (a < b) return divIntExplicit(a, -b, -tempResult);
	return divIntExplicit(a - b, b, tempResult + 1);
}
#pragma endregion

int main()
{
	int jeperdsmeschveux = divIntExplicit(4, -8, 0);
	return 0;
}