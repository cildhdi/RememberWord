#include "tools.h"


std::string WideStringToString(const std::wstring& src)
{
	std::locale sys_locale("");

	const wchar_t* data_from = src.c_str();
	const wchar_t* data_from_end = src.c_str() + src.size();
	const wchar_t* data_from_next = 0;

	int wchar_size = 4;
	char* data_to = new char[(src.size() + 1) * wchar_size];
	char* data_to_end = data_to + (src.size() + 1) * wchar_size;
	char* data_to_next = 0;

	memset(data_to, 0, (src.size() + 1) * wchar_size);

	typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
	mbstate_t out_state = { 0 };
	auto result = std::use_facet<convert_facet>(sys_locale).out(
		out_state, data_from, data_from_end, data_from_next,
		data_to, data_to_end, data_to_next);
	if (result == convert_facet::ok)
	{
		std::string str = data_to;
		return str;
		delete[] data_to;
	}
	delete[] data_to;
	return "";
}

std::wstring StringToWideString(const std::string& src)
{
	std::locale sys_locale("");
	const char* data_from = src.c_str();
	const char* data_from_end = src.c_str() + src.size();
	const char* data_from_next = 0;

	wchar_t* data_to = new wchar_t[src.size() + 1];
	wchar_t* data_to_end = data_to + src.size() + 1;
	wchar_t* data_to_next = 0;

	wmemset(data_to, 0, src.size() + 1);

	typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
	mbstate_t in_state = { 0 };
	auto result = std::use_facet<convert_facet>(sys_locale).in(
		in_state, data_from, data_from_end, data_from_next,
		data_to, data_to_end, data_to_next);
	if (result == convert_facet::ok)
	{
		std::wstring wstr = data_to;
		return wstr;
		delete[] data_to;
	}
	delete[] data_to;
	return L"";
}


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
