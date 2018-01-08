#include "Dictionary.h"

int Dictionary::HASHN = 1009;
int Dictionary::HASHM = 10000019;
typedef long long LL;
Dictionary* Dictionary::Single = nullptr;

Dictionary::Dictionary(){
	for (int i = 0; i < HASHM; ++i)
		h[i] = nullptr;
}

Dictionary::~Dictionary() {}

Dictionary* Dictionary::getSingle() {
	if (Single == nullptr)
		Single = new Dictionary();
	return Single;
}

void Dictionary::initDictionary() {
	wchar_t *t = new wchar_t[20];
	std::wifstream fin("input/×¨ÓÃÊõÓï.txt");
	if (!fin.is_open()) {
		std::wcout << "File Error!" << std::endl;
	}
	else
	{
		while (!fin.eof()) {
			fin.getline(t, 20);
			int len = wcslen(t);
			int hash = 0;
			for (int i = 0; i < len; ++i) {
				int tmp = t[i];
				int t = tmp % HASHM + HASHM;
				if (t > HASHM) t -= HASHM;

				hash = ((LL)hash*HASHN%HASHM + t) % HASHM;
			}
			while (h[hash] != nullptr) {
				++hash;
				if (hash == HASHM) hash = 0;
			}
			h[hash] = new wCharString(t);
		}
	}
	fin.close();
	
	fin.open("input/´Ê¿â.dic");
	if (!fin.is_open()) {
		std::wcout << "File Error!" << std::endl;
	}
	else
	{
		while (!fin.eof()) {
			fin.getline(t, 20);
			int len = wcslen(t);
			int hash = 0;
			for (int i = 0; i < len; ++i) {
				int tmp = t[i];
				int t = tmp % HASHM + HASHM;
				if (t >= HASHM) t -= HASHM;

				hash = ((LL)hash*HASHN%HASHM + t) % HASHM;
			}
			while (h[hash] != nullptr) {
				++hash;
				if (hash == HASHM) hash = 0;
			}
			h[hash] = new wCharString(t);
		}
	}
	fin.close();
	delete[] t;
}

void Dictionary::divide(wCharString & c, wCharStringLink & v) {
	int i = 0;
	int len = c.length();

	int *hash = new int[len + 1];
	int *e = new int[len + 1];
	hash[0] = 0; e[0] = 1;
	for (int i = 0; i < len; ++i) {
		int t = c[i];
		t = t % HASHM + HASHM;
		if (t >= HASHM) t -= HASHM;
		hash[i + 1] = ((LL)hash[i] * HASHN % HASHM + t) % HASHM;
		e[i + 1] = ((LL)e[i] * HASHN) % HASHM;
	}

	while (i < len) {
		if (c[i] == L' ' || c[i] == L'£¬' || c[i] == L'£¿' || c[i] == L'¡£' || c[i] == L'£¡') { i++; continue; }
		for (int j = 16; j > 0; --j) {
			if (i + j > len) continue;
			wCharString tmp = c.substring(i, i + j);
			int h = hash[i + j] - (LL)hash[i] * e[j] % HASHM + HASHM;
			if (h >= HASHM) h -= HASHM;

			if (check(tmp, h)) {
				v.add(tmp);
				i += j - 1;
				break;
			}
		}
		++i;
	}
	delete[] hash;
	delete[] e;
}

bool Dictionary::check(wCharString &c, int hash) {
	while (h[hash] != nullptr) {
		if (c == *h[hash])
			return true;
		++hash;
		if (hash == HASHM) hash = 0;
	}
	return false;
}

