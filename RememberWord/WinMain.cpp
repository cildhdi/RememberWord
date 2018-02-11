#include <process.h>
#include "KrUI/KrCore.h"
#include "Word.h"
#include "GetEntry.h"
using namespace KrUI;

KrUI::KrUIManager* pUi = KrUIManager::GetpKrUIManager();
KrWindow* pWnd = nullptr;
KrEdit * pEdit = nullptr;
KrLabel* pLbl = nullptr;
KrButton* pBtn = nullptr;
KrList* pList = nullptr;
Word word(L"");

void QueryWord(Word* pW);
void Btn_Click(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
void Wnd_KeyDown(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
void List_Change(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	pUi->Initialize(hInstance);
	int width = 1000, height = 630, cx = GetSystemMetrics(SM_CXSCREEN), cy = GetSystemMetrics(SM_CYSCREEN);
	pWnd = dynamic_cast<KrWindow*>(pUi->AddWindow(L"不要查单词", (cx - width) / 2, (cy - height) / 2, width, height));
	pWnd->RegMsg(WM_KEYDOWN, reinterpret_cast<MSGPROC>(Wnd_KeyDown));
	pEdit = dynamic_cast<KrEdit*>(pWnd->AddControl(KrEdit_t, L"", 30, 50, 800, 35));
	pBtn = dynamic_cast<KrButton*>(pWnd->AddControl(KrButton_t, L"查询", 870, 50, 100, 35));
	pBtn->RegMsg(KM_CLICK, reinterpret_cast<MSGPROC>(Btn_Click));

	pLbl = dynamic_cast<KrLabel*>(pWnd->AddControl(KrLabel_t, L"", 360, 100, 600, 600));
	pLbl->SetLineAlignment(Gdiplus::StringAlignmentNear);
	pList = dynamic_cast<KrList*>(pWnd->AddControl(KrList_t, L"WordList", 30, 100, 300, 500));
	pList->RegMsg(KM_SELECTEDITEMCHANGE, reinterpret_cast<MSGPROC>(List_Change));
	return pUi->MessageLoop();
}

void List_Change(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	word.SetWord(pList->GetSelectedItem().m_ItemName);
	QueryWord(&word);
}

void Btn_Click(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	if (pEdit == nullptr || pLbl == nullptr || pEdit->GetText().size() == 0)return;
	word.SetWord(pEdit->GetText());
	QueryWord(&word);
	if (word.IsFound())pList->AddItem(pEdit->GetText());
	pWnd->SetFocusedCtrl(pEdit);
	//_beginthread(reinterpret_cast<_beginthread_proc_type>(QueryWord), 0, &word);
}

void Wnd_KeyDown(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	if (wp == VK_RETURN)pBtn->CallMsgProc(KM_CLICK, wp, lp);
}

void QueryWord(Word* pW)
{
	GetEntry(pW);
	pLbl->SetName(pW->GetDetail());
	int height = static_cast<int>(GetTextSize(pW->GetDetail(), pLbl->GetFont(), Gdiplus::Rect(0, 0, pLbl->GetWidth(), pLbl->GetHeight())).Height);
	if (((height + pLbl->GetY()) < 610))
	{
		pWnd->SetHeight(610);
	}
	else
	{
		pWnd->SetHeight(height + pLbl->GetY() + 50);
	}
	pW->Clear();
}