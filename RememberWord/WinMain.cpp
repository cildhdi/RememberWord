#include "KrUI/KrCore.h"
#include "Word.h"
#include "GetEntry.h"
#include "TinyXML2/tinyxml2.h"
using namespace KrUI;

KrUI::KrUIManager* pUi = KrUIManager::GetpKrUIManager();
KrWindow* pWnd = nullptr;
KrEdit * pEdit = nullptr;
KrLabel* pLbl = nullptr;
KrButton* pBtn_Query = nullptr;
KrButton* pBtn_Delete = nullptr;
KrList* pList = nullptr;
Word word(L"");

std::string strPath;
tinyxml2::XMLDocument doc;
void QueryWord(Word* pW);
void Btn_Query_Click(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
void Wnd_KeyDown(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
void List_Change(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
void Btn_Delete_Click(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	pUi->Initialize(hInstance);

	int width = 1000, height = 630, cx = GetSystemMetrics(SM_CXSCREEN), cy = GetSystemMetrics(SM_CYSCREEN);
	pWnd = dynamic_cast<KrWindow*>(pUi->AddWindow(L"不要查单词", (cx - width) / 2, (cy - height) / 2, width, height));
	pWnd->RegMsg(WM_KEYDOWN, reinterpret_cast<MSGPROC>(Wnd_KeyDown));
	pEdit = pWnd->AddEdit(L"", 30, 50, 690, 35);
	pBtn_Query = pWnd->AddButton(L"查询", 750, 50, 100, 35);
	pBtn_Query->RegMsg(KM_CLICK, reinterpret_cast<MSGPROC>(Btn_Query_Click));
	pBtn_Delete = pWnd->AddButton(L"删除", 870, 50, 100, 35);
	pBtn_Delete->RegMsg(KM_CLICK, reinterpret_cast<MSGPROC>(Btn_Delete_Click));
	pLbl = pWnd->AddLabel(L"", 260, 100, 700, 600);
	pLbl->SetLineAlignment(Gdiplus::StringAlignmentNear);
	pList = pWnd->AddList(L"WordList", 30, 100, 200, 500);
	pList->RegMsg(KM_SELECTEDITEMCHANGE, reinterpret_cast<MSGPROC>(List_Change));

	char szPath[MAX_PATH];
	GetModuleFileNameA(NULL, szPath, MAX_PATH);
	strPath = szPath;
	strPath = strPath.substr(0, strPath.size() - 16) + "words.xml";
	tinyxml2::XMLError err = doc.LoadFile(strPath.c_str());
	if (err == tinyxml2::XMLError::XML_ERROR_FILE_NOT_FOUND)
	{
		doc.SaveFile(strPath.c_str());
	}
	else
	{
		tinyxml2::XMLElement* pEleWord = doc.FirstChildElement();
		while (pEleWord != nullptr)
		{
			pList->AddItem(StringToWideString(pEleWord->Name()));
			pEleWord = pEleWord->NextSiblingElement();
		}
	}
	return pUi->MessageLoop();
}

void List_Change(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	pEdit->SetText(pList->GetSelectedItem().m_ItemName);
	pBtn_Query->CallMsgProc(KM_CLICK, wp, lp);
}

void Btn_Query_Click(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	if (pEdit == nullptr || pLbl == nullptr || pEdit->GetText().size() == 0)return;
	tinyxml2::XMLElement* pEleWord = doc.FirstChildElement();
	while (pEleWord != nullptr)
	{
		if (StringToWideString(pEleWord->Name()) == pEdit->GetText())
		{
			pLbl->SetName(StringToWideString(pEleWord->GetText()));
			return;
		}
		pEleWord = pEleWord->NextSiblingElement();
	}
	word.SetWord(pEdit->GetText());
	word.ClearAcceptations();
	word.ClearSentences();
	QueryWord(&word);
	if (word.IsFound())
	{
		pList->AddItem(pEdit->GetText());
		tinyxml2::XMLElement* pEle = doc.NewElement("word");
		pEle->SetName(WideStringToString(word.GetWord()).c_str());
		pEle->SetText(WideStringToString(word.GetDetail()).c_str());
		doc.InsertEndChild(pEle);
		doc.SaveFile(strPath.c_str());
	}
	pWnd->SetFocusedCtrl(pEdit);
	//_beginthread(reinterpret_cast<_beginthread_proc_type>(QueryWord), 0, &word);
}

void Btn_Delete_Click(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	tinyxml2::XMLElement* pEleWord = doc.FirstChildElement();
	while (pEleWord != nullptr)
	{
		if (StringToWideString(pEleWord->Name()) == pEdit->GetText())
		{
			tinyxml2::XMLElement* pEleTemp = pEleWord;
			pEleWord = pEleWord->NextSiblingElement();
			pList->RemoveItem(pEdit->GetText());
			doc.DeleteChild(pEleTemp);
			doc.SaveFile(strPath.c_str());
			return;
		}
		pEleWord = pEleWord->NextSiblingElement();
	}
}

void Wnd_KeyDown(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	if (wp == VK_RETURN)pBtn_Query->CallMsgProc(KM_CLICK, wp, lp);
	if (wp == VK_DELETE)pBtn_Delete->CallMsgProc(KM_CLICK, wp, lp);
}

void QueryWord(Word* pW)
{
	GetEntry(pW);
	pLbl->SetName(pW->GetDetail());
	int height = static_cast<int>(GetTextSize(pW->GetDetail(), pLbl->GetFont(), Gdiplus::Rect(0, 0, pLbl->GetWidth(), pLbl->GetHeight())).Height);
	if (((height + pLbl->GetY()) < 610))
		pWnd->SetHeight(610);
	else
		pWnd->SetHeight(height + pLbl->GetY() + 50);
}