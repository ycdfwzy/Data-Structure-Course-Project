#include "wCharString.h"
#include <cstring>
#include <windows.h>
#include <wchar.h>

wCharString::wCharString(const char * c) {
	if (c == nullptr) {
		m_data = new wchar_t[2];
		size = 1;
		m_data[0] = L'\0';
		return;
	}
	size = MultiByteToWideChar(CP_ACP, 0, c, strlen(c) , NULL, 0);
	m_data = new wchar_t[size+1];
	int t = MultiByteToWideChar(CP_ACP, 0, c, strlen(c), m_data, size);
	m_data[t] = L'\0';
	int j = 0;
	for (int i = 0; i < t; ++i) {
		m_data[j++] = m_data[i];
		if (m_data[i] == L'>' || m_data[i] == L';' || m_data[i] == L'{' || m_data[i] == L'}' || m_data[i] == L',') {
			while (i < t && (m_data[i + 1] == L' ' || m_data[i + 1] == L'\t' || m_data[i + 1] == L'\r' || m_data[i + 1] == L'\n' || m_data[i + 1] == L'\r\n'))
				++i;
		}
		if (m_data[i] == L'<' || m_data[i] == L'{' || m_data[i] == L'}') {
			while (j > 1 && (m_data[j - 2] == L' ' || m_data[j - 2] == L'\t' || m_data[j - 2] == L'\r' || m_data[j - 2] == L'\n' || m_data[j - 2] == L'\r\n')) {
				m_data[j-2] = m_data[i];
				--j;
			}
		}
	}
	m_data[j] = L'\0';
}

wCharString::wCharString(const wchar_t * c) {
	if (c == nullptr) {
		m_data = new wchar_t[2];
		size = 1;
		m_data[0] = L'\0';
		return;
	}
	size = wcslen(c);
	m_data = new wchar_t[size + 1];
	for (int i = 0; i < size; ++i)
		m_data[i] = c[i];
	m_data[size] = L'\0';
}

wCharString::wCharString(const wCharString &c){
	size = c.size;
	m_data = new wchar_t[size+1];
	wcscpy_s(m_data, size + 1, c.m_data);
}

wCharString::~wCharString(){
	if (m_data != nullptr)
		delete[] m_data;
}

int wCharString::indexOf(const wCharString &c){
	return indexOf(c.m_data);
}

int wCharString::indexOf(const wchar_t* c) {
	int k1 = wcslen(m_data);
	int k2 = wcslen(c);
	/*for (int i = 0; i + k2 <= k1; ++i) {
		bool flag = true;
		for (int j = 0; j < k2 && flag; ++j) {
			if (m_data[i + j] != c[j]) flag = false;
		}
		if (flag) return i;
	}
	return -1;*/
	//KMP
	int *pre = new int[k2];
	pre[0] = -1;
	for (int i = 1, j = -1; i < k2; ++i) {
		while (j >= 0 && c[i] != c[j + 1]) j = pre[j];
		if (c[i] == c[j + 1]) ++j;
		pre[i] = j;
	}
	for (int i = 0, j = -1; i < k1; ++i) {
		while (j >= 0 && m_data[i] != c[j + 1]) j = pre[j];
		if (m_data[i] == c[j + 1]) ++j;
		if (j == k2 - 1) {
			delete[] pre;
			return i - j + 1;
		}
	}
	delete[] pre;
	return -1;
}

int wCharString::length() const {
	return wcslen(m_data);
}

wchar_t wCharString::operator[](unsigned int index) {
	if (index < 0 || index >= wcslen(m_data))
		return 0;
	return m_data[index];
}

wCharString wCharString::substring(int l, int r) {
	if (l < 0) l = 0;
	if (r > size) r = size;
	wchar_t *tmp = new wchar_t[r-l+1];
	//wcscpy_s(tmp, r-l, m_data+l);
	for (int i = l; i < r; ++i)
		tmp[i - l] = m_data[i];
	tmp[r - l] = L'\0';
	return wCharString(tmp);
}

void wCharString::concat(const wCharString &c) {
	concat(c.m_data);
}

void wCharString::concat(const wchar_t *c) {
	int k1 = wcslen(m_data);
	int k2 = wcslen(c);
	if (k2 == 0) return;
	if (k1 + k2 + 1 > size) expand(k1 + k2 + 1);
	wcscpy_s(m_data+k1, wcslen(c)+1, c);
}

void wCharString::concat(const wchar_t c) {
	int k = wcslen(m_data);
	if (k + 2 > size) expand(k+2);
	m_data[k] = c;
	m_data[k + 1] = L'\0';
}

void wCharString::expand(int tar) {
	while (size < tar) size <<= 1;
	wchar_t* tmp = new wchar_t[size+1];
	wcscpy_s(tmp, wcslen(m_data)+1, m_data);
	delete m_data;
	m_data = tmp;
}

void wCharString::translate() {
	int len = wcslen(m_data);
	int j = 0;
	for (int i = 0; i < len; ++i, ++j) {
		if (i + 1 < len && m_data[i] == L'&' && m_data[i + 1] == L'#') {
			i = i + 2;
			int t = 0;
			while (i < len && m_data[i] >= L'0' && m_data[i] <= L'9') {
				t = t * 10 + m_data[i] - L'0';
				++i;
			}
			m_data[j] = t;
		}
		else
		if (i + 5 < len && m_data[i] == L'&' && m_data[i + 1] == L'n' && m_data[i + 2] == L'b' && m_data[i + 3] == L's' && m_data[i + 4] == L'p' && m_data[i + 5] == L';') {
			i += 5;
			m_data[j] = L' ';
		}
		else
			m_data[j] = m_data[i];
	}
	m_data[j] = L'\0';
}

bool wCharString::startwith(const wchar_t *c) {
	int l1 = wcslen(m_data);
	int l2 = wcslen(c);
	if (l1 < l2) return false;
	for (int i = 0; i < l2; ++i)
		if (m_data[i] != c[i])
			return false;
	return true;
}

bool wCharString::endwith(const wchar_t *c) {
	int l1 = wcslen(m_data);
	int l2 = wcslen(c);
	if (l1 < l2) return false;
	for (int i = 0; i < l2; ++i)
		if (m_data[l1-1-i] != c[l2-1-i])
			return false;
	return true;
}

wCharString& wCharString::operator=(const wCharString &c) {
	if (m_data != nullptr) delete m_data;
	size = wcslen(c.m_data);
	m_data = new wchar_t[size+1];
	wcscpy_s(m_data, size+1, c.m_data);
	return *this;
}

bool wCharString::operator==(const wCharString &c) const {
	int l1 = wcslen(m_data);
	int l2 = wcslen(c.m_data);
	if (l1 != l2) return false;
	for (int i = 0; i < l1; ++i)
		if (m_data[i] != c.m_data[i])
			return false;
	return true;
}

bool wCharString::operator<(const wCharString &c) const {
	int l1 = wcslen(m_data);
	int l2 = wcslen(c.m_data);
	for (int i = 0; i < l1 && i < l2; ++i) {
		if (m_data[i] < c.m_data[i]) return true;
		if (m_data[i] > c.m_data[i]) return false;
	}
	return l1 < l2;
}

std::wostream& operator<<(std::wostream &os, wCharString &c) {
	/*
	os << c.m_data;
	*/
	int sz = wcslen(c.m_data);
	for (int i = 0; i < sz; ++i) {
		if (os.bad()) {
			os.clear();
		}
		os << c.m_data[i];
	}
	return os;
}

std::wistream& operator >> (std::wistream& is, wCharString& c) {
	wchar_t *temp = new wchar_t[100010];
	is >> std::setw(100010) >> temp;
	c = temp;
	return is;
}
