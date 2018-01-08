// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DSCPDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DSCPDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
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

#ifdef DSCPDLL_EXPORTS
#define DSCPDLL_API __declspec(dllexport)
#else
#define DSCPDLL_API __declspec(dllimport)
#endif
/*
// �����Ǵ� DSCPdll.dll ������
class DSCPDLL_API CDSCPdll {
public:
	CDSCPdll(void);
	// TODO:  �ڴ�������ķ�����
};

extern DSCPDLL_API int nDSCPdll;

DSCPDLL_API int fnDSCPdll(void);
*/

class mainwork {
public:
	mainwork() :inverted_doc(nullptr) { data.clear(); url.clear(); }
	~mainwork() {
		
	}

	ThreadPool thread;
	Inverted_DOC *inverted_doc;
	std::vector <Post*> data;
	std::vector <TCHAR*> url;
};
/*
TCHAR* CharToTchar(const char * _char);
char* StringtoChar(std::string &s);
std::string encode(std::string &s);
*/
EXTERN_C{
DSCPDLL_API mainwork* init();
DSCPDLL_API void destructor(mainwork *ins);
DSCPDLL_API const char* beforework(mainwork *ins);
DSCPDLL_API const char* divide_words(mainwork *ins, const char *words);
DSCPDLL_API const char* query(mainwork *ins, const char *words);
DSCPDLL_API const char* get_Doc(mainwork *ins, unsigned id);
DSCPDLL_API const char *get_str(const char *str);
DSCPDLL_API void free_str(const char *str);
}