#include "Word.h"

Word::Word(std::wstring key)
{
	m_Key = key;
	m_bFound = false;
}

Word::Word(tinyxml2::XMLDocument* xmlDoc)
{
	FromXMLDoc(xmlDoc);
}

void Word::FromXMLDoc(tinyxml2::XMLDocument* xmlDoc)
{
	m_bFound = true;
	tinyxml2::XMLElement* elmtRoot = xmlDoc->RootElement();
	tinyxml2::XMLElement* elmtKey = elmtRoot->FirstChildElement("key");
	//m_Key = StringToWideString(elmtKey->GetText());

	tinyxml2::XMLElement* elmtPos = elmtRoot->FirstChildElement("pos");
	tinyxml2::XMLElement* elmtAcceptation = elmtRoot->FirstChildElement("acceptation");
	if (elmtPos == nullptr || elmtAcceptation == nullptr) m_bFound = false;
	while ((elmtPos != nullptr) && (elmtAcceptation != nullptr))
	{
		AddAcceptation(StringToWideString(elmtPos->GetText()), StringToWideString(elmtAcceptation->GetText()));
		elmtPos = elmtPos->NextSiblingElement("pos");
		elmtAcceptation = elmtAcceptation->NextSiblingElement("acceptation");
	}

	tinyxml2::XMLElement* elmtStc = elmtRoot->FirstChildElement("sent");
	tinyxml2::XMLElement* elmtOrig = nullptr;
	tinyxml2::XMLElement* elmtTrans = nullptr;
	while (elmtStc != nullptr)
	{
		elmtOrig = elmtStc->FirstChildElement("orig");
		elmtTrans = elmtStc->FirstChildElement("trans");
		AddSentence(StringToWideString(elmtOrig->GetText()), StringToWideString(elmtTrans->GetText()));
		elmtStc = elmtStc->NextSiblingElement("sent");
	}
}

void Word::SetWord(std::wstring strWord)
{
	m_Key = strWord;
}



void Word::AddAcceptation(std::wstring pos, std::wstring acception)
{
	m_Acceptations.insert(std::pair<std::wstring, std::wstring>(pos, acception));
}


void Word::ClearAcceptations()
{
	m_Acceptations.clear();
}

void Word::AddSentence(std::wstring orig, std::wstring trans)
{
	m_Sentences.insert(std::pair<std::wstring, std::wstring>(orig, trans));
}

void Word::ClearSentences()
{
	m_Sentences.clear();
}

std::wstring Word::GetWord()
{
	return m_Key;
}

std::wstring Word::GetDetail()
{
	if (!m_bFound) return L"未查询到单词，请检查网络连接和是否有拼写错误。";
	std::wstring acceptations;
	for (auto acp : m_Acceptations)
	{
		acceptations += (L"   " + acp.first + L"   " + acp.second/* + L"\n"*/);
	}
	std::wstring sentences;
	int i = 1;
	for (auto stc : m_Sentences)
	{
		sentences += (L"  " + std::to_wstring(i) + L". " + stc.first.substr(1, stc.first.size() - 1) + L"     " + stc.second.substr(1, stc.second.size() - 1)/* + L"\n"*/);
		i++;
	}
	return  L"单词：" + m_Key + L"\n意义：\n" + acceptations + std::wstring(L"例句：\n") + sentences;
}

void Word::Clear()
{
	m_Key.clear();
	m_Acceptations.clear();
	m_Sentences.clear();
}

bool Word::IsFound()
{
	return m_bFound;
}