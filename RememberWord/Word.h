#pragma once
#ifndef _WORD_H_
#define _WORD_H_
#include <string>
#include <map>
#include <windows.h>
#include "TinyXML2/tinyxml2.h"
#include "KrUI/Tools/KrTools.h"
using namespace KrUI;

#pragma warning(disable:4066)
class Word
{
private:
	bool bExsited;
	std::wstring m_Key;//单词
	std::map<std::wstring, std::wstring> m_Acceptations;//<词性,意义>
	std::map<std::wstring, std::wstring> m_Sentences;//<英文，中文>
public:
	Word(std::wstring key);
	Word(tinyxml2::XMLDocument* xmlDoc);
	std::wstring GetWord();
	void FromXMLDoc(tinyxml2::XMLDocument* xmlDoc);
	void SetWord(std::wstring strWord);
	void AddAcceptation(std::wstring pos, std::wstring acception);
	void ClearAcceptations();
	void AddSentence(std::wstring orig, std::wstring trans);
	void ClearSentences();
	void Clear();
	std::wstring GetDetail();//返回单词和意义和例句
};



#endif