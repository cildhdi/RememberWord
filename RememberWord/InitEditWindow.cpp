#include "InitEditWindow.h"

KrWindow* pWndEdit = nullptr;
KrList* pWordList = nullptr;
std::string path;
tinyxml2::XMLDocument xmlDoc;

void InitEditWindow()
{
	int width = 1000, height = 630, cx = GetSystemMetrics(SM_CXSCREEN), cy = GetSystemMetrics(SM_CYSCREEN);
	pWndEdit = KrUIManager::GetpKrUIManager()->AddWindow(L"±à¼­±¾µØ´Ê¿â", (cx - width) / 2, (cy - height) / 2, width, height);
	pWordList = pWndEdit->AddList(L"", 30, 50, 200, 500);
	char szPath[MAX_PATH];
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
			pWordList->AddItem(StringToWideString(pEleWord->Name()));
			pEleWord = pEleWord->NextSiblingElement();
		}
	}
}