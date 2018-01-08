#define _CRT_SECURE_NO_WARNINGS
#include "htmlExplainer.h"
#include <cstdio>

wchar_t* htmlExplainer::sc[15] = {L"<br", L"<hr", L"<area",	L"<base", L"<img", L"<input", L"<link", L"<meta", L"<basefont", L"<param", L"<col", L"<frame", L"<embed", L"<keygen", L"<source"};

htmlExplainer::htmlExplainer(): cnt(0){}

htmlExplainer::~htmlExplainer(){}

bool htmlExplainer::selfclosed(wCharString& c) {
	for (int i = 0; i < 15; ++i)
		if (c.startwith(sc[i])) return true;
	return false;
}

void htmlExplainer::findin_class_tszh1(int x, wCharString &webadd, wCharString &title, wCharString &type) {
	if (label[x] == L"<h1>") title = cont[x];
	if (label[x].startwith(L"<a")) {
		int t = label[x].indexOf(L"rel");
		if (t == -1) type = cont[x];
		else {
			webadd = label[x].substring(9, t-2);
		}
	}
	if (label[x].startwith(L"<span")) return;

	for (int i = a[x]; i; i = nxt[i]) {
		findin_class_tszh1(i, webadd, title, type);
	}
}

void htmlExplainer::findin_class_z(int x, wCharString &ctg1, wCharString &ctg2) {
	int t = 0;
	for (int i = a[x]; i; i = nxt[i]) {
		if (label[i].startwith(L"<a")) {
			++t;
			if (t < 3 || t > 4) continue;
			if (t == 4) ctg2 = cont[i];
			if (t == 3) ctg1 = cont[i];
		}
	}
}

void htmlExplainer::find_date(int x, wCharString &date) {
	for (int i = a[x]; i; i = nxt[i]) {
		if (label[i].startwith(L"<em")) {
			date = cont[i];
		}
	}
}

void htmlExplainer::find_author(int x, wCharString &author) {
	for (int i = a[x]; i; i = nxt[i]) {
		if (label[i].startwith(L"<a")) {
			author = cont[i];
		}
	}
}

void htmlExplainer::findin_class_tfsz(int x, wCharString &cont_) {
	if (label[x] == L"<div class=\"tip_c xs0\">")
		return;
	cont_.concat(cont[x]);
	for (int i = a[x]; i; i = nxt[i])
		findin_class_tfsz(i, cont_);
}

bool htmlExplainer::match(wCharString& c1, wCharString& c2) {
	int l1 = wcslen(c1.m_data);
	int l2 = wcslen(c2.m_data);
	if (l2 > l1+1) return false;
	for (int i = 0; i < l2 - 3; ++i)
		if (c1.m_data[i + 1] != c2.m_data[i + 2])
			return false;
	return true;
}

void htmlExplainer::extractInfo(wCharString &c, Post* p/*std::vector<Post*>& v*/) {
	Stack_<int> *stk = new Stack_<int>;
	int i = 0, len = wcslen(c.m_data);
	int usrs = 0;
	wCharString webadd_, title_, type_, ctg1_, ctg2_, author_, date_, cont_;
	//freopen("b.txt", "w", stdout);
	while (i < len) {
		if (c.m_data[i] == L'<') {
			int j = i;
			while (j < len && c.m_data[j] != L'>')
				++j;
			wCharString tmp = c.substring(i, j+1);
			i = j + 1;
			if (tmp.startwith(L"<!--")) continue;
			if (tmp.startwith(L"<!DOCTYPE")) continue;
			if (tmp.endwith(L"/>") || selfclosed(tmp)) {
				++cnt;
				label[cnt] = tmp;
				a[cnt] = 0;
				if (stk->empty()) {
					root = cnt;
					nxt[cnt] = 0;
				}
				else
				{
					int fa = stk->top();
					//nxt[cnt] = a[fa];
					//a[fa] = cnt;
					nxt[cnt] = 0;
					int k = a[fa];
					if (k == 0) {
						a[fa] = cnt;
					}
					else
					{
						while (nxt[k] != 0) k = nxt[k];
						nxt[k] = cnt;
					}
				}
			}
			else
			if (tmp.startwith(L"</")) {
				while (!stk->empty() && !match(label[stk->top()], tmp))
					stk->pop();
				if (!stk->empty()) {
					//std::wcout << label[stk->top()] << std::endl;
					//std::wcout << tmp << std::endl << std::endl;
					int t = stk->top();
					if (label[t] == L"<div class=\"ts z h1\">") {
						findin_class_tszh1(t, webadd_, title_, type_);
						p->setwebadd(webadd_);
						p->settitle(title_);
						p->settype(type_);
						//std::wcout << webadd_ << std::endl << title_ << std::endl << type_ << std::endl;
					} else
					if (label[t] == L"<div class=\"z\">") {
						findin_class_z(t, ctg1_,ctg2_);
						p->setctg1(ctg1_);
						p->setctg2(ctg2_);
						//std::wcout << ctg1_ << std::endl << ctg2_ << std::endl;
					} else
					if (label[t] == L"<div class=\"authi\">") {
						if (usrs & 1) {
							find_date(t, date_);
							date_ = date_.substring(4, date_.length());
							p->setdate(date_);
							//std::wcout << date_ << std::endl;
							usrs++;
						}
						else
						{
							find_author(t, author_);
							p->setauthor(author_);
							//std::wcout << author_ << std::endl;
							usrs++;
						}
					} else
					if (label[t] == L"<div class=\"t_fsz\">") {
						//cont_ = wCharString();
						findin_class_tfsz(t, cont_);
						cont_.translate();
						p->setcont(cont_);
						//Post* p = new Post(webadd_, ctg1_, ctg2_, title_, cont_, author_, date_, type_);
						//v.push_back(p);
						break;
					}
					stk->pop();
				}
			}
			else
			{
				++cnt;
				label[cnt] = tmp;
				a[cnt] = 0;
				if (stk->empty()) {
					root = cnt;
					nxt[cnt] = 0;
				}
				else
				{
					int fa = stk->top();
					nxt[cnt] = 0;
					int k = a[fa];
					if (k == 0) {
						a[fa] = cnt;
					}
					else
					{
						while (nxt[k] != 0) k = nxt[k];
						nxt[k] = cnt;
					}
					//a[fa] = cnt;
				}
				stk->push(cnt);
			}
		}
		else
		{
			int j = i;
			while (j < len && c.m_data[j] != L'<')
				++j;
			wCharString tmp = c.substring(i, j);
			i = j;
			int cur = stk->top();
			cont[cur].concat(tmp);
		}
	}
	delete stk;
	//fclose(stdout);
	//std::wcout << webadd_ << std::endl << title_ << std::endl << type_ << std::endl;
}
