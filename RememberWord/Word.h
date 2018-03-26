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
	std::wstring m_Key;//����
	std::map<std::wstring, std::wstring> m_Acceptations;//<����,����>
	std::map<std::wstring, std::wstring> m_Sentences;//<Ӣ�ģ�����>
public:
	Word(std::wstring key);
	Word(tinyxml2::XMLDocument* xmlDoc);
	std::wstring GetWord();
	void FromXMLDoc(tinyxml2::XMLDocument* xmlDoc);//��xml�ĵ��н���������
	void FromXMLStr(std::string str);//��xml�ַ����н���������
	void AddToXmlDoc(tinyxml2::XMLDocument* xmlDoc);//���������xml�����ļ�
	std::string GetXml();//��ȡxml�����ļ�
	void SetWord(std::wstring strWord);
	void AddAcceptation(std::wstring pos, std::wstring acception);//��Ӻ���
	void ClearAcceptations();
	void AddSentence(std::wstring orig, std::wstring trans);//�������
	void ClearSentences();
	void Clear();//�����������
	bool IsFound();//�����Ƿ��ҵ�����
	std::wstring GetDetail();//���ص��ʺ����������
};



#endif