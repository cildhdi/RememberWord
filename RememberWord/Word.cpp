#include "Word.h"

Word::Word(std::wstring key)
{
	m_Key = key;
}

void Word::SetWord(std::wstring strWord)
{
	m_Key = strWord;
}

std::wstring Word::GetWord()
{
	return m_Key;
}

void Word::AddAcceptation(std::wstring pos, std::wstring acception)
{
	m_Acceptations.insert(std::pair<std::wstring, std::wstring>(pos, acception));
}


bool Word::RemoveAcceptation(std::wstring pos)
{
	return 0 != m_Acceptations.erase(pos);
}

void Word::ClearAcceptation()
{
	m_Acceptations.clear();
}

std::wstring Word::GetDetail()
{
	std::wstring acceptations;
	for (auto acp : m_Acceptations)
	{
		acceptations += (acp.first + L"  " + acp.second + L"\n");
	}
	return m_Key + L"\n" + acceptations;
}