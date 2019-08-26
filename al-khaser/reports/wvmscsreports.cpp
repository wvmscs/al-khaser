#include "pch.h"
#include "wvmscsreports.h"

static bool SESSION_CONT = FALSE;
#define OUTPUTFILE  _T("al-khaser-result.txt")

void wvmscs_print( const TCHAR* fmt, ...)
{
	va_list list;
	const TCHAR* p, * r;
	int e;

	FILE* fp = NULL;
	errno_t error;

	if (SESSION_CONT)
		error = _tfopen_s(&fp, OUTPUTFILE, _T("a+"));
	else
		error = _tfopen_s(&fp, OUTPUTFILE, _T("w"));

	// file create/open failed
	if ((error != 0) || (fp == NULL))
		return;

	va_start(list, fmt);

	for (p = fmt; *p; ++p)
	{
		if (*p != '%')//If simple string
			fputc(*p, fp);

		else
		{
			switch (*++p)
			{
				/* string */
			case 's':
			{
				r = va_arg(list, TCHAR*);
				_ftprintf(fp, _T("%s"), r);
				continue;
			}

			/* integer */
			case 'd':
			{
				e = va_arg(list, int);
				_ftprintf(fp, _T("%d"), e);
				continue;
			}

			default:
				fputc(*p, fp);
			}
		}
	}
	va_end(list);
	//fputc('\n', fp);
	SESSION_CONT = TRUE;
	fclose(fp);
}

void wvmscs_print_category(const TCHAR* text) {
	wvmscs_print(TEXT("\n-------------------------[%s]-------------------------\n"), text);
}
void wvmscs_print_os(LPCTSTR lpszBuf) {
	wvmscs_print(_T("\n[*] You are running: %s\n"), lpszBuf);
}
void wvmscs_print_last_error(LPCTSTR lpszBuf) {
	wvmscs_print(TEXT("%s\n"),lpszBuf);
}

void wvmscs__print_ckeck_text(const TCHAR* szMsg) {
	wvmscs_print(TEXT("[-] %s"), szMsg);
}
void wvmscs__print_check_result(int result, const TCHAR* szMsg) {
	if (result == TRUE)
		wvmscs_print(TEXT("[ BAD  ]\n"));
	else
		wvmscs_print(TEXT("[ GOOD ]\n"));
}