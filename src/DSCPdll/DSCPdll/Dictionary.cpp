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
		fin.imbue(std::locale(""));
		while (!fin.eof()) {
			fin.getline(t, 20);
			//std::wcout << t << std::endl;
			int len = wcslen(t);
			//if (t[len] == 13) len--;
			if (len > 0) t[--len] = L'\0';
			int hash = 0;
			//std::wcout << "   " << hash << std::endl;
			for (int i = 0; i < len; ++i) {
				int tmp = (int)t[i];
				//std::wcout << t[i] << " " << tmp << std::endl;
				int tt = tmp % HASHM + HASHM;
				if (tt >= HASHM) tt -= HASHM;

				hash = ((LL)hash*(LL)HASHN%(LL)HASHM + (LL)tt) % (LL)HASHM;
				//std::wcout << "   " << hash << std::endl;
			}
			while (h[hash] != nullptr) {
				++hash;
				if (hash == HASHM) hash = 0;
			}
			//std::wcout << t << " " << hash << std::endl;
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
		fin.imbue(std::locale(""));
		while (!fin.eof()) {
			fin.getline(t, 20);
			
			int len = wcslen(t);
			//if (t[len] == 13) len--;
			if (len > 0) t[--len] = L'\0';
			int hash = 0;
			//std::wcout << "   " << hash << std::endl;
			for (int i = 0; i < len; ++i) {
				int tmp = (int)t[i];
				//std::wcout << t[i] << " " << tmp << std::endl;
				int tt = tmp % HASHM + HASHM;
				if (tt >= HASHM) tt -= HASHM;

				hash = ((LL)hash*(LL)HASHN%(LL)HASHM + (LL)tt) % (LL)HASHM;
				//std::wcout << "   " << hash << std::endl;
			}
			while (h[hash] != nullptr) {
				++hash;
				if (hash == HASHM) hash = 0;
			}
			//std::wcout << t << " " << hash << std::endl;
			h[hash] = new wCharString(t);
		}
		fin.close();
	}
	
	delete[] t;
}

void Dictionary::divide(wCharString & c, wCharStringLink & v) {
	//std::wcout << "divide " << c << std::endl;
	int i = 0;
	int len = c.length();

	int *hash = new int[len + 1];
	int *e = new int[len + 1];
	hash[0] = 0; e[0] = 1;
	for (int i = 0; i < len; ++i) {
		int t = (int)c[i];
		t = t % HASHM + HASHM;
		if (t >= HASHM) t -= HASHM;
		hash[i + 1] = ((LL)hash[i] * (LL)HASHN % (LL)HASHM + (LL)t) % (LL)HASHM;
		e[i + 1] = ((LL)e[i] * (LL)HASHN) % (LL)HASHM;
	}

	while (i < len) {
		if (c[i] == L' ' || c[i] == L'£¬' || c[i] == L'£¿' || c[i] == L'¡£' || c[i] == L'£¡') { i++; continue; }
		for (int j = 16; j > 0; --j) {
			if (i + j > len) continue;
			wCharString tmp = c.substring(i, i + j);
			int h = (LL)hash[i + j] - ((LL)hash[i] * (LL)e[j]) % (LL)HASHM + (LL)HASHM;
			if (h >= HASHM) h -= HASHM;

			if (check(tmp, h)) {
				//std::wcout << tmp << std::endl;
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
		//std::wcout << c <<" "<< *h[hash] << std::endl;
		if (c == *h[hash])
			return true;
		++hash;
		if (hash == HASHM) hash = 0;
	}
	return false;
}

