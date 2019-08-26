#pragma once

#include "pch.h"


void wvmscs_print_category(const TCHAR* text);
void wvmscs_print_os(LPCTSTR lpszBuf);
void wvmscs_print_last_error(LPCTSTR lpszBuf);

void wvmscs__print_ckeck_text(const TCHAR* szMsg);
void wvmscs__print_check_result(int result, const TCHAR* szMsg);