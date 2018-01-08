// DSCPdll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "DSCPdll.h"

/*
// 这是导出变量的一个示例
DSCPDLL_API int nDSCPdll=0;

// 这是导出函数的一个示例。
DSCPDLL_API int fnDSCPdll(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 DSCPdll.h
CDSCPdll::CDSCPdll()
{
    return;
}
*/

using std::vector;
using std::wcout;
using std::endl;
using std::wcin;
using std::ifstream;
using std::wifstream;
using std::wofstream;

TCHAR* CharToTchar(const char * _char) {
	int iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	TCHAR* tchar = new TCHAR[iLength+1];
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
	tchar[iLength] = '\0';
	return tchar;
}

char* wchartochar(const wchar_t* t) {
	int len = WideCharToMultiByte(CP_UTF8, 0, t, wcslen(t), NULL, 0, NULL, NULL);
	char *ret = new char[len + 1];
	WideCharToMultiByte(CP_UTF8, 0, t, wcslen(t), ret, len, NULL, NULL);
	ret[len] = '\0';
	return ret;
}

wchar_t* chartowchar(const char *t) {
	int size = MultiByteToWideChar(CP_UTF8, 0, t, strlen(t), NULL, 0);
	wchar_t *ret = new wchar_t[size + 1];
	MultiByteToWideChar(CP_UTF8, 0, t, strlen(t), ret, size);
	ret[size] = L'\0';
	return ret;
}

char* StringtoChar(std::string &s) {
	int len = s.length();
	char* ret = new char[len+1];
	for (int i = 0; i < len; ++i)
		ret[i] = s[i];
	ret[len] = '\0';
	return ret;
}

std::string encode(std::string &s) {
	std::string ret;
	ret.reserve(s.size());
	for (char c : s) {
		if (c == '\t') {
			ret += "\\t";
		} else
		if (c == '\n') {
			ret += "\\n";
		} else
		if (c == '\"') {
			ret += "\\\"";
		} else
		if (c == '\\') {
			ret += "\\\\";
		}
		else
		{
			ret += c;
		}
	}
	return ret;
}

wCharString encode(wCharString &s) {
	wCharString ret;
	int len = s.length();
	for (int i = 0; i < len; ++i){
		if (s[i] == '\t') {
			ret.concat(L"\\t");
		}
		else
			if (s[i] == '\n') {
				ret.concat(L"\\n");
			}
			else
				if (s[i] == '\"') {
					ret.concat(L"\\\"");
				}
				else
					if (s[i] == '\\') {
						ret.concat(L"\\\\");
					}
					else
					{
						ret.concat(s[i]);
					}
	}
	return ret;
}

std::string mystringtostdstring(wCharString &s) {
	int len = s.length();
	wchar_t *t = new wchar_t[len+1];
	for (int i = 0; i < len; ++i)
		t[i] = s[i];
	t[len] = L'\0';
	std::string ret(wchartochar(t));
	delete[] t;
	return ret;
}

wchar_t* get_info(const wchar_t *t, int &s) {
	wchar_t *ret = new wchar_t[100000];
	int len = wcslen(t + s);
	int p = s;
	while (p < len + s && t[p] != L'"') ++p;
	int pp = (++p);
	while (p < len + s && t[p] != L'"') {
		ret[p - pp] = t[p];
		++p;
	}
	s = p + 1;
	ret[p - pp] = L'\0';
	return ret;
}

EXTERN_C{

DSCPDLL_API mainwork* init() {
	mainwork *ins = new mainwork();
	return ins;
}

DSCPDLL_API void destructor(mainwork *ins) {
	if (ins) delete ins;
}

DSCPDLL_API const char* beforework(mainwork *ins) {
	
	setlocale(LC_ALL, "zh_CN.gbk");
	std::locale::global(std::locale(""));
	wcout.imbue(std::locale(""));

	Dictionary::getSingle()->initDictionary();

	ins->data.clear();
	wifstream fin("output/result.csv");
	if (fin.is_open()) {
		fin.imbue(std::locale(""));
		wchar_t *in = new wchar_t[100000];
		fin.getline(in, 100000);
		while (!fin.eof()) {
			fin.getline(in, 100000);
			//wcout << in << endl;
			int k = 0;
			wchar_t *webadd = get_info(in, k);
			//wcout << webadd << endl;
			wchar_t *ctg1 = get_info(in, k);
			//wcout << ctg1 << endl;
			wchar_t *ctg2 = get_info(in, k);
			//wcout << ctg2 << endl;
			wchar_t *title = get_info(in, k);
			wchar_t *cont = get_info(in, k);
			wchar_t *author = get_info(in, k);
			wchar_t *date = get_info(in, k);
			wchar_t *type = get_info(in, k);
			Post* tmp = new Post(wCharString(webadd), wCharString(ctg1), wCharString(ctg2), wCharString(title), wCharString(cont), wCharString(author), wCharString(date), wCharString(type));
			delete[] webadd;
			delete[] ctg1;
			delete[] ctg2;
			delete[] title;
			delete[] cont;
			delete[] author;
			delete[] date;
			delete[] type;
			tmp->divideWords();
			//wcout << *tmp << endl;
			ins->data.push_back(tmp);
		}
		delete[] in;
		fin.close();
	}

	ins->inverted_doc = new Inverted_DOC;
	int len = ins->data.size();
	for (int i = 0; i < len; ++i) {
		Post* tmp = ins->data[i];
		//wcout << *tmp << endl;
		node<wCharString>* x = tmp->getpart()->gethead();
		while (x != nullptr) {
			//wcout << x->getvalue() << endl;
			ins->inverted_doc->Insert(x->getvalue(), 0, i + 1, 1);
			x = x->getnext();
		}
		//delete tmp;
	}

	return StringtoChar(std::string("{\"okay\":true,\"result\":null}"));
}

DSCPDLL_API const char* divide_words(mainwork *ins, const char *words) {
	wcout << "divide" << endl;
	wCharString w(chartowchar(words));
	wCharStringLink v;
	Dictionary::getSingle()->divide(w, v);
	wCharString s;
	node<wCharString>* x = v.gethead();
	while (x != nullptr) {
		if (s.length() > 0) s.concat(L',');
		s.concat(L'\"');
		s.concat(encode(x->getvalue()));
		s.concat(L'\"');
		x = x->getnext();
	}
	wcout << s << endl;
	/*int len = w.length();
	wCharString s;
	int i = 0;
	while (i < len) {
		while (i < len && w[i] == ' ') ++i;
		if (i >= len) break;
		int j = i;
		if (s.length() > 0) s.concat(L',');
		//s += "\"";
		s.concat(L'\"');
		while (i < len && w[i] != ' ')
			++i;
		s.concat( encode(w.substring(j, i)) );
		s.concat(L'\"');
		i++;
	}*/
	//wchar_t *t1 = new wchar_t[s.length()+1];
	//for (int i = 0; i < s.length(); ++i)
	//	t1[i] = s[i];
	//t1[s.length()] = L'\0';
	//wcout << s.length() << endl;
	//wchar_t *t2 = chartowchar(wchartochar(t1));
	//wcout << wcscmp(t1, t2) << endl;
	//wcout << t1 << endl;
	//wcout << t2 << endl;

	std::string ret = "{\"okay\":true,\"result\":[" + mystringtostdstring(s) + "]}";
	std::cout << ret << endl;
	return StringtoChar(ret);
}

DSCPDLL_API const char* query(mainwork *ins, const char *words) {
	int L = ins->data.size();
	int *cnt = new int[L];
	int *index = new int[L];
	int *num = new int[L];
	wCharString st(chartowchar(words));
	wCharStringLink v;
	Dictionary::getSingle()->divide(st, v);
	for (int i = 0; i < L; ++i)
		cnt[i] = 0, index[i] = i, num[i] = 0;
	node<wCharString>* x = v.gethead();
	while (x != nullptr) {
		auto foo = [ins, x]()->DocList_Node* {
			Inverted_DOC_Node* tt = ins->inverted_doc->search(x->getvalue());
			if (tt == ins->inverted_doc->getNIL()) return nullptr;
			return tt->get_doclist()->get_head();
		};
		DocList_Node* t = foo();
		while (t != nullptr) {
			cnt[t->get_DocID() - 1] += t->get_Times();
			num[t->get_DocID() - 1]++;
			t = t->get_next();
		}

		x = x->getnext();
	}
	/*
	int p = 0;
	while (p < st.length()) {
		while (p < st.length() && st[p] == L' ') ++p;
		int q = p;
		while (p < st.length() && st[p] != L' ') ++p;

		auto foo = [ins, &st, q, p]()->DocList_Node* {
			Inverted_DOC_Node* tt = ins->inverted_doc->search(st.substring(q, p));
			if (tt == ins->inverted_doc->getNIL()) return nullptr;
			return tt->get_doclist()->get_head();
		};
		DocList_Node* t = foo();
		while (t != nullptr) {
			cnt[t->get_DocID() - 1] += t->get_Times();
			t = t->get_next();
		}

		++p;
	}
	*/
	std::sort(index, index + L, [num, cnt](int a, int b)->bool { 
		if (num[a] != num[b]) return num[a] > num[b];
		return cnt[a] > cnt[b];
	});

	std::string ret = "";
	for (int i = 0; i < L && cnt[index[i]]; ++i) {
		if (ret.length() > 0) ret += ',';
		ret += "{\"rank\":" + std::to_string(cnt[index[i]]) + ",\"id\":" + std::to_string(index[i]) + "}";
	}
	delete[] index;
	delete[] cnt;
	delete[] num;

	wcout << "query" << endl;
	std::cout.clear();
	std::cout << ret << endl;
	std::cout << ins->inverted_doc->getsize() << endl;
	ret = "{\"okay\":true,\"result\":[" + ret + "]}";
	std::cout << ret << endl;
	return StringtoChar(ret);
}

DSCPDLL_API const char* get_Doc(mainwork *ins, unsigned id) {
	wcout << "get_Doc" << endl;
	std::string ret = "{\"okay\":true,\"result\":{"
		"\"url\":\"" + encode(mystringtostdstring(ins->data[id]->getwebadd())) + "\","
		"\"headline\":\"" + encode(mystringtostdstring(ins->data[id]->gettitle())) + "\","
		"\"question\":\"" + encode(mystringtostdstring(ins->data[id]->gettitle())) + "\","
		"\"author\":\"" + encode(mystringtostdstring(ins->data[id]->getauthor())) + "\","
		"\"content\":\"" + encode(mystringtostdstring(ins->data[id]->getcont())) + "\""
		"}}";
	return StringtoChar(ret);
}

DSCPDLL_API const char *get_str(const char *str) {
	return str;
}

DSCPDLL_API void free_str(const char *str) {
	delete[] str;
}

}