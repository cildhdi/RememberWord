#pragma once
#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <iostream>
#include <windows.h>
#include <codecvt>
bool WCharStringToUTF8String(const std::wstring &wstr, std::string &u8str);
bool UTF8StringToWCharString(const std::string &u8str, std::wstring &wstr);
std::wstring StringToWideString(const std::string& src);
std::string WideStringToString(const std::wstring& src);

#endif

