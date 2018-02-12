#pragma once

#include <iostream>
#include <windows.h>
#include <codecvt>
#include "KrUI/Tools/KrTools.h"
using namespace KrUI;
#define CURL_STATICLIB
#include "curl/curl.h"
#pragma comment(lib,"curl/libcurl.lib")
#include "TinyXML2/tinyxml2.h"

void GetEntry(void* pParam);

