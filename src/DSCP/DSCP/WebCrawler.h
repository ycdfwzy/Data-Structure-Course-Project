/*
这部分代码参考自 http://www.cnblogs.com/coderzh/archive/2008/11/24/1340134.html
*/

#pragma once
#include <windows.h>
#include <wininet.h>

#define MAXSIZE 1024
#pragma comment(lib, "Wininet.lib")

char* urlopen(TCHAR*);