#pragma once
#ifndef _WORD_H_
#define _WORD_H_
#include <string>
#include <map>
class Word
{
private:
	std::wstring m_Key;//单词
	std::map<std::wstring, std::wstring> m_Acceptations;//<词性,意义>
public:
	Word(std::wstring key);
	std::wstring GetWord();
	void SetWord(std::wstring strWord);
	void AddAcceptation(std::wstring pos, std::wstring acception);
	bool RemoveAcceptation(std::wstring pos);
	void ClearAcceptation();
	std::wstring GetDetail();//返回单词和意义
};
#endif