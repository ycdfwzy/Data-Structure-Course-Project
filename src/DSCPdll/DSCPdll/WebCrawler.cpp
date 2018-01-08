#include "WebCrawler.h"

char* urlopen(TCHAR* url) {
	char* ret = nullptr;
	int l = 0;

	HINTERNET hSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hSession != NULL) {
		HINTERNET hHttp = InternetOpenUrl(hSession, url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);

		if (hHttp != NULL) {
			ret = new char[2000010];
			char Temp[MAXSIZE];
			ULONG Number = 1;
			while (Number > 0)
			{
				InternetReadFile(hHttp, Temp, MAXSIZE - 1, &Number);
				Temp[Number] = '\0';
				strcpy_s(ret + l, Number + 1, Temp);
				l += Number;
			}

			InternetCloseHandle(hHttp);
			hHttp = NULL;
		}
		InternetCloseHandle(hSession);
		hSession = NULL;
	}

	return ret;
}