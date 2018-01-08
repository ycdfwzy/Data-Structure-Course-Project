#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <locale.h> 
#include <sstream>
#include <vector>
#include <ctime>
#include "ThreadPool.h"
#include "Stack_.h"
#include "wCharString.h"
#include "wCharStringLink.h"
#include "WebCrawler.h"
#include "htmlExplainer.h"
#include "Post.h"
#include "Dictionary.h"
#include "Dictionary_AC_Automation.h"
#include "Inverted_DOC.h"
#include "Inverted_DOC_Node.h"
#include "Inverted_DOC_HASH.h"

using namespace std;

int main(int argc, TCHAR* argv[]) {
	setlocale(LC_ALL, "zh_CN.gbk");
	locale::global(locale(""));
	wcout.imbue(locale(""));
	
	ThreadPool th;
	/*--------------�ʵ��ʼ��--------------*/
	Dictionary::getSingle()->initDictionary();
	/*--------------------------------------*/
	/*---------------��ȡ��ҳ---------------*/
	vector <TCHAR*> webadd;
	ifstream fin("input/url.csv");
	if (fin.is_open()) {
		fin.imbue(locale(""));
		int w = 0;
		while (!fin.eof()) {
			TCHAR *in = new TCHAR[100];
			fin.getline(in, 100);
			if (w == 0) w = 1, delete[] in;
			else {
				int len = strlen(in);
				if (len == 0) continue;
				for (int i = 0; i < len; ++i)
				if (in[i] == 'h'){
					for (int j = i; j < len - 1; ++j)
						in[j - i] = in[j];
					in[len - 1 - i] = '\0';
					break;
				}
				wcout << "Get: " << in << endl;
				webadd.push_back(in);
				
			}
		}
	}
	fin.close();
	/*--------------------------------------*/
	/*---------------������ҳ---------------*/
	wofstream fout("output/result.csv");
	if (!fout.is_open()){
		wcout << "File Error" << endl;
		return 1;
	}
	vector < future<Post*> > infos;
	vector <Post*> data;
	infos.clear(); data.clear();
	fout.imbue(locale(""));
	fout << L"\"���\"" << L",\"��ַ\"" << L",\"��������\"" << L",\"����С��\"" << L",\"��������\"" << L",\"��������\"" << L",\"������\"" << L",\"��������\"" << L",\"��������\"" << L",\"�ִʽ��\"" << endl;
	for (TCHAR* url : webadd) {
		//���߳̽�����ҳ
		infos.push_back(th.enqueue([url]()->Post* {
			char* t = urlopen(url);
			wcout << "Extract: "  << url << endl;
			wCharString s(t);
			htmlExplainer hex;
			Post *ret = new Post(wCharString(url));
			hex.extractInfo(s, ret);
			ret->divideWords();
			delete[] t;
			return ret;
		}));
	}
	int len = infos.size();
	for (int i = 0; i < len; ++i) {
		Post* tmp = infos[i].get();
		tmp->checkvalid();
		data.push_back(tmp);
	}
	for (int i = 0; i < len; ++i) {
		Post* tmp = data[i];
		//wcout << tmp->getwebadd() << endl;
		fout << to_wstring(i + 1) << *tmp << endl;
	}
	fout.close();
	/*--------------------------------------*/
	/*-------------ѡ�������ʽ-------------*/
	wstring s;
	int type;
	do {
		wcout << "Please Choose method of searching: Hash(Hash Table) or BBT(Balanced Binary Tree)" << endl;
		wcin >> s;
	} while (s != wstring(L"Hash") && s != wstring(L"BBT"));
	if (s == wstring(L"Hash")) {
		type = 1;
	}
	else
	{
		type = 0;
	}
	/*--------------------------------------*/
	/*--------------���������--------------*/
	clock_t start = clock();
	Inverted_DOC* inverted_doc = nullptr;
	Inverted_DOC_HASH* inverted_doc_hash = nullptr;
	if (type == 0) {
		inverted_doc = new Inverted_DOC;
	}
	else
	{
		inverted_doc_hash = new Inverted_DOC_HASH;
	}

	len = data.size();
	for (int i = 0; i < len; ++i) {
		Post* tmp = data[i];
		node<wCharString>* x = tmp->getpart()->gethead();
		while (x != nullptr) {
			if (type == 0) {	//ƽ�����������
				inverted_doc->Insert(x->getvalue(), 0, i+1, 1);
			}
			else               //��ϣ�����
			{
				inverted_doc_hash->Insert(x->getvalue(), i+1, 1);
			}
			x = x->getnext();
		}
		delete tmp;
	}
	clock_t ends = clock();
	wcout << "It costs " << (double)(ends - start)/CLOCKS_PER_SEC << " seconds to build index table using ";
	if (type == 0) wcout << "Balanced Binary Tree." << endl;
	else wcout << "Hash Table." << endl;

	/*--------------------------------------*/
	/*-----------------����-----------------*/
	wcout << "searching..." << endl;
	wifstream filein("query.txt");
	fout.open("result.txt");
	wchar_t *in = new wchar_t[1000000];
	if (filein.is_open() && fout.is_open()) {
		int *index = new int[2010];	//�ĵ��±�
		int *cnt = new int[2010];   //�ؼ��ʸ���
		int *num = new int[2010];   //�ؼ���������
		while (!filein.eof()) {
			for (int i = 0; i < 2010; ++i)
				cnt[i] = 0, num[i] = 0, index[i] = i;
			filein.getline(in, 1000000);
			int len = wcslen(in);
			for (int j = 0; j < len; ++j) { //�ָ�ؼ���
				wCharString s;
				while (j < len && in[j] != L' ') s.concat(in[j++]);
				
				//�����ùؼ���
				auto foo = [type, inverted_doc, inverted_doc_hash, &s]()->DocList_Node*{
					if (type == 0) {
						Inverted_DOC_Node* tt = inverted_doc->search(s);
						if (tt == inverted_doc->getNIL()) return nullptr;
						return tt->get_doclist()->get_head();
					}
					else
					{
						DocList *tt = inverted_doc_hash->Search(s);
						if (tt == nullptr) return nullptr;
						return tt->get_head();
					}
				};
				DocList_Node* t = foo();

				//�����
				while (t != nullptr) {
					cnt[t->get_DocID()] += t->get_Times();
					num[t->get_DocID()]++;
					t = t->get_next();
				}
			}
			//�����������������ִ��������ȼ��Ӹ���������
			sort(index, index + 2010, [num, cnt](int a, int b)->bool {
				if (num[a] != num[b]) return num[a] > num[b];
				return cnt[a] > cnt[b];
			});

			for (int i = 0; i < 2010; ++i)
			if (cnt[index[i]] > 0){
				fout << L"(" << to_wstring(index[i]) << L"," << to_wstring(cnt[index[i]]) << ") ";
			}
			fout << endl;
		}
		delete[] cnt;
		delete[] index;
		delete[] num;
		filein.close();
		fout.close();
	}
	delete[] in;
	system("pause");
	return 0;
}
