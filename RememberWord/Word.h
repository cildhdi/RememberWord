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
	bool m_bFound;
	std::string m_Xml;
	std::wstring m_Key;//单词
	std::map<std::wstring, std::wstring> m_Acceptations;//<词性,意义>
	std::map<std::wstring, std::wstring> m_Sentences;//<英文，中文>
public:
	Word(std::wstring key);
	Word(tinyxml2::XMLDocument* xmlDoc);
	std::wstring GetWord();
	void FromXMLDoc(tinyxml2::XMLDocument* xmlDoc);//从xml文档中解析出单词
	void FromXMLStr(std::string str);//从xml字符串中解析出单词
	void AddToXmlDoc(tinyxml2::XMLDocument* xmlDoc);//将词添加至xml描述文件
	std::string GetXml();//获取xml描述文件
	void SetWord(std::wstring strWord);
	void AddAcceptation(std::wstring pos, std::wstring acception);//添加含义
	void ClearAcceptations();
	void AddSentence(std::wstring orig, std::wstring trans);//添加例句
	void ClearSentences();
	void Clear();//清除所有内容
	bool IsFound();//返回是否找到单词
	std::wstring GetDetail();//返回单词和意义和例句
};



#endif