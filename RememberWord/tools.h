#pragma once
#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <iostream>
#include <windows.h>
#include <codecvt>

#define CURL_STATICLIB
#include "curl/curl.h"
#pragma comment(lib,"curl/libcurl.lib")

bool WCharStringToUTF8String(const std::wstring &wstr, std::string &u8str);
bool UTF8StringToWCharString(const std::string &u8str, std::wstring &wstr);
std::wstring StringToWideString(std::string src);
std::string WideStringToString(std::wstring src);
void GetEntry(void* pParam);
#endif

