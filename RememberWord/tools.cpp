#include "tools.h"
#include "Word.h"
#include "TinyXML2/tinyxml2.h"


bool WCharStringToUTF8String(const std::wstring &wstr, std::string &u8str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	u8str = conv.to_bytes(wstr);
	return true;
}

bool UTF8StringToWCharString(const std::string &u8str, std::wstring &wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
	wstr = conv.from_bytes(u8str);
	return true;
}

std::string WideStringToString(std::wstring wStr)
{
	if (wStr.size() == 0)
	{
		return "";
	}

	char *pszBuf = NULL;
	int needBytes = WideCharToMultiByte(CP_ACP, 0, wStr.c_str(), -1, NULL, 0, NULL, NULL);
	if (needBytes > 0)
	{
		pszBuf = new char[needBytes + 1];
		ZeroMemory(pszBuf, (needBytes + 1) * sizeof(char));
		WideCharToMultiByte(CP_ACP, 0, wStr.c_str(), -1, pszBuf, needBytes, NULL, NULL);
	}
	std::string str = pszBuf;
	delete[] pszBuf;
	return str;
}

std::wstring StringToWideString(std::string str)
{
	if (str.size() == 0)
	{
		return L"";
	}

	wchar_t *pszBuf = NULL;
	int needWChar = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	if (needWChar > 0)
	{
		pszBuf = new wchar_t[needWChar + 1];
		ZeroMemory(pszBuf, (needWChar + 1) * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pszBuf, needWChar);
	}
	std::wstring wStr = pszBuf;
	delete[] pszBuf;
	return wStr;
}

size_t req_reply(void *ptr, size_t size, size_t nmemb, void *stream)
{
	std::string *str = (std::string*)stream;
	(*str).append((char*)ptr, size*nmemb);
	return size * nmemb;
}

CURLcode curl_get_req(const std::string &url, std::string &response)
{
	CURL *curl = curl_easy_init();
	CURLcode res;
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // url  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // if want to use https  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false  
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3); // set transport and time out time  
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
		res = curl_easy_perform(curl);
	}
	curl_easy_cleanup(curl);
	return res;
}


void GetEntry(void* pParam)
{
	Word* pWord = reinterpret_cast<Word*>(pParam);
	curl_global_init(CURL_GLOBAL_ALL);
	//CURL * curl;
	//CURLcode res;
	std::string strrep;
	curl_get_req("http://dict-co.iciba.com/api/dictionary.php?w=" + WideStringToString(pWord->GetWord()) + "&key=84246457202BD56AE2EDBF8CDBAB66B1", strrep);

	std::wstring str;
	UTF8StringToWCharString(strrep, str);
	unsigned int xmlstart = 0;
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (str[i] == '?')
		{
			xmlstart = i - 1;
			break;
		}
	}
	tinyxml2::XMLDocument docXml;
	std::string strXml;
	str = str.substr(xmlstart, str.size() - xmlstart);
	strXml = WideStringToString(str);
	tinyxml2::XMLError errXml = docXml.Parse(strXml.c_str());
	if (errXml == tinyxml2::XML_SUCCESS)
	{
		pWord->FromXMLDoc(&docXml);
	}
	curl_global_cleanup();
}
