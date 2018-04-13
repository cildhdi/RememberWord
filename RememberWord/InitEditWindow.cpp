#include "InitEditWindow.h"



KrWindow* pWndEdit = nullptr;
KrList* pWordList = nullptr;
KrButton* pBtnSa = nullptr;
KrButton* pBtnNsa = nullptr;
KrButton* pBtnDel = nullptr;
std::string path;
char szPath[MAX_PATH];
tinyxml2::XMLDocument xmlDoc;

LRESULT SelectAll(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
LRESULT SelectNoItem(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
LRESULT DelItem(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
LRESULT EditWndDel(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
void InitEditWindow()
{
	if (hEditWnd != nullptr)
	{
		::SetFocus(hEditWnd);
		return;
	}
	int width = 500, height = 650, cx = GetSystemMetrics(SM_CXSCREEN), cy = GetSystemMetrics(SM_CYSCREEN);
	pWndEdit = KrUIManager::GetpKrUIManager()->AddWindow(L"选中要删除的单词", (cx - width) / 2, (cy - height) / 2, width, height);
	hEditWnd = pWndEdit->GetHWND();
	pWordList = pWndEdit->AddList(L"", 30, 70, 440, 500);
	pWordList->SetMultiSelectable(true);
	pBtnNsa = pWndEdit->AddButton(L"全不选", 130, 590);
	pBtnNsa->RegMsg(KM_CLICK, SelectNoItem);
	pBtnSa = pWndEdit->AddButton(L"全选", 250, 590);
	pBtnSa->RegMsg(KM_CLICK, SelectAll);
	pBtnDel = pWndEdit->AddButton(L"删除", 370, 590);
	pBtnDel->RegMsg(KM_CLICK, DelItem);
	pWndEdit->RegMsg(KM_WNDDELETE, EditWndDel);
	LoadXml(pWordList);
}

LRESULT EditWndDel(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	hEditWnd = nullptr;
	return 0;
}

LRESULT SelectAll(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	pWordList->SelectAllItems(true);
	return 0;
}
LRESULT SelectNoItem(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	pWordList->SelectAllItems(false);
	return 0;
}

LRESULT DelItem(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	for (auto li : pWordList->GetSelectedItems())
	{
		tinyxml2::XMLElement* pEleWord = xmlDoc.FirstChildElement();
		while (pEleWord != nullptr)
		{
			if (StringToWideString(pEleWord->Name()) == li.m_ItemName)
			{
				tinyxml2::XMLElement* pEleTemp = pEleWord;
				pEleWord = pEleWord->NextSiblingElement();
				xmlDoc.DeleteChild(pEleTemp);
			}
			if (pEleWord != nullptr)pEleWord = pEleWord->NextSiblingElement();
		}
		pWordList->RemoveItem(li.m_Index);
	}
	xmlDoc.SaveFile(path.c_str());
	MessageBox(pWndEdit->GetHWND(), L"删除成功，即将重新启动本程序。", L"提示", MB_OK);
	WinExec(szPath, SW_SHOW);
	PostQuitMessage(0);
	return 0;
}

void LoadXml(KrUI::KrList* pL)
{
	GetModuleFileNameA(NULL, szPath, MAX_PATH);
	path = szPath;
	path = path.substr(0, path.size() - 16) + "words.xml";
	tinyxml2::XMLError err = xmlDoc.LoadFile(path.c_str());
	if (err == tinyxml2::XMLError::XML_ERROR_FILE_NOT_FOUND)
	{
		xmlDoc.SaveFile(path.c_str());
	}
	else
	{
		tinyxml2::XMLElement* pEleWord = xmlDoc.FirstChildElement();
		while (pEleWord != nullptr)
		{
			pL->AddItem(StringToWideString(pEleWord->Name()));
			pEleWord = pEleWord->NextSiblingElement();
		}
	}
}