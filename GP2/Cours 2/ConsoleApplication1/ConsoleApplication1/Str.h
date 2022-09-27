#pragma once

int StrLen(const char* str) {
	if (str == nullptr) return 0;
	if (*str == 0) return 0;
	return 1 + StrLen(str + 1);
}

int StrCmp(const char* a, const char* b) {
	if (*a == '\0' && *b == '\0') return 0;
	if (a > b) return 1;
	if (a < b) return -1;

	return StrCmp(a + 1, b + 1);
}

void StrNCpy(char* dest, int n, const char* src) {
	if (!src)	return;
	if (!dest)	return;

	if (*src == '\0') {
		*dest = 0;
		return;
	}

	if (!--n) *dest = '\0';

	*dest = *src;
	return StrNCpy(dest + 1, n, src + 1);
}

void StrCpy(char* dest, const char* str) {
	return StrNCpy(dest, StrLen(str), str);
}

void StrCat(char* a, char* b) {
	if (*a != '\0') return StrCat(a + 1, b);
	if (!b) return;
	if (*b == '\0') return;
	StrCpy(a, b);
}

const char* StrChr(const char* dst, char c) {
	if (dst == nullptr) return nullptr;
	if (*dst == '\0') return nullptr;
	if (*dst == c)
		return dst;
	return StrChr(dst + 1, c);
}

const char* StrStr(const char* str, const char* pattern) {
	if (str == nullptr) return nullptr;
	if (*str == 0) return nullptr;
	if (0 == StrCmp(str, pattern))
		return str;
	return StrStr(str + 1, pattern);
}
