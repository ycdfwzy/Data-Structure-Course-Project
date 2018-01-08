#include "Dictionary_AC_Automation.h"

Dictionary_AC_Automation* Dictionary_AC_Automation::single = nullptr;

void Dictionary_AC_Automation::add_to_tire(wchar_t *c) {
	int len = wcslen(c);
	if (len == 0) return;
	int j = 1;
	for (int i = len-1; i >= 0; --i) {
		int tmp = c[i];
		if (j == 1) {
			if (root_next[tmp] == 0) {
				root_next[tmp] = ++cnt;
			}
			j = root_next[tmp];
		}
		else
		{
			int k = get_next(j, tmp);
			if (k > 0) j = k;
			else {
				ch[++cnt] = c[i];
				nxt[cnt] = a[j];
				a[j] = cnt;
				a[cnt] = 0;
				j = cnt;
			}
		}
	}
	mml[j] = len;
}

int Dictionary_AC_Automation::get_next(int i, int t){
	if (i < 1) return 0;
	if (i == 1) return root_next[t];
	for (int j = a[i]; j; j = nxt[j]) {
		if (ch[j] == t) return j;
	}
	return 0;
}

void Dictionary_AC_Automation::build_fail_tree() {
	int *q = new int[600010];
	int l , r;
	q[l = r = 1] = 1;
	while (l <= r) {
		int x = q[l++];
		if (x == 1) {
			fail[x] = 1;
			for (int i = 0; i < 100000; ++i)
			if (root_next[i] > 0){
				q[++r] = root_next[i];
				fa[root_next[i]] = x;
			}
			continue;
		}

		int t = fail[fa[x]];
		while (t > 1 && get_next(t, ch[x]) == 0)
			t = fail[t];
		fail[x] = get_next(t, ch[x]);
		if (fail[x] == 0) fail[x] = 1;

		if (mml[fail[x]] > mml[x])
			mml[x] = mml[fail[x]];

		for (int i = a[x]; i; i = nxt[i]) {
			q[++r] = i;
			fa[i] = x;
		}
	}


	delete[] q;
}

Dictionary_AC_Automation::Dictionary_AC_Automation() {
	cnt = 1;
	memset(root_next, 0, sizeof(root_next));
	memset(a, 0, sizeof(a));
	memset(mml , 0, sizeof(mml));
}


Dictionary_AC_Automation::~Dictionary_AC_Automation() {
}

Dictionary_AC_Automation * Dictionary_AC_Automation::getsingle() {
	if (single == nullptr)
		single = new Dictionary_AC_Automation();
	return single;
}

void Dictionary_AC_Automation::initDictionary(){
	wchar_t *t = new wchar_t[20];
	std::wifstream fin("input/◊®”√ ı”Ô.txt");
	if (!fin.is_open()) {
		std::wcout << "File Error!" << std::endl;
	}
	else
	{
		while (!fin.eof()) {
			fin.getline(t, 20);
			add_to_tire(t);
		}
	}
	fin.close();

	fin.open("input/¥ ø‚.dic");
	if (!fin.is_open()) {
		std::wcout << "File Error!" << std::endl;
	}
	else
	{
		while (!fin.eof()) {
			fin.getline(t, 20);
			add_to_tire(t);
		}
	}
	fin.close();

	build_fail_tree();
}

void Dictionary_AC_Automation::divide(wCharString &c, wCharStringLink &v) {
	int len = c.length();
	int *p = new int[len+1];

	//work on the AC Automation
	int j = 1;
	for (int i = len-1; i >= 0; --i) {
		while (j > 1 && get_next(j, c[i]) == 0)
			j = fail[j];
		j = get_next(j, c[i]);
		if (j == 0) j = 1;

		p[i] = mml[j];
	}

	for (int i = 0; i < len; ++i) {
		if (p[i] <= 0) continue;
		v.add(c.substring(i, i+p[i]));
		i = i + p[i] - 1;
	}
}
