// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 DSCPDLL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// DSCPDLL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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
// 此类是从 DSCPdll.dll 导出的
class DSCPDLL_API CDSCPdll {
public:
	CDSCPdll(void);
	// TODO:  在此添加您的方法。
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