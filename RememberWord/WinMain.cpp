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
Word word(L"");

void QueryWord(Word* pW);
void Btn_Click(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
void Wnd_KeyDown(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	pUi->Initialize(hInstance);
	int width = 700, height = 500, cx = GetSystemMetrics(SM_CXSCREEN), cy = GetSystemMetrics(SM_CYSCREEN);
	pWnd = dynamic_cast<KrWindow*>(pUi->AddWindow(L"不要查单词", (cx - width) / 2, (cy - height) / 2, width, height));
	pWnd->RegMsg(WM_KEYDOWN, reinterpret_cast<MSGPROC>(Wnd_KeyDown));
	pEdit = dynamic_cast<KrEdit*>(pWnd->AddControl(KrEdit_t, L"", 50, 70, 450, 35));
	pBtn = dynamic_cast<KrButton*>(pWnd->AddControl(KrButton_t, L"查询", 550, 70, 100, 35));
	pBtn->RegMsg(KM_CLICK, reinterpret_cast<MSGPROC>(Btn_Click));

	pLbl = dynamic_cast<KrLabel*>(pWnd->AddControl(KrLabel_t, L"", 60, 120, 600, 600));
	pLbl->SetLineAlignment(Gdiplus::StringAlignmentNear);
	return pUi->MessageLoop();
}

void Btn_Click(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	if (pEdit == nullptr || pLbl == nullptr || pEdit->GetText().size() == 0)return;
	word.SetWord(pEdit->GetText());
	_beginthread(reinterpret_cast<_beginthread_proc_type>(QueryWord), 0, &word);
}

void Wnd_KeyDown(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	if (wp == VK_RETURN)pBtn->CallMsgProc(KM_CLICK, wp, lp);
}

void QueryWord(Word* pW)
{
	pLbl->SetName(L"查询中......");
	GetEntry(pW);
	pLbl->SetName(pW->GetDetail());
	int height = static_cast<int>(GetTextSize(pW->GetDetail(), pLbl->GetFont(), Gdiplus::Rect(0, 0, pLbl->GetWidth(), pLbl->GetHeight())).Height);
	if (((height + pLbl->GetY()) < 500))
	{
		pWnd->SetHeight(500);
	}
	else
	{
		pWnd->SetHeight(height + pLbl->GetY() + 50);
	}
	pW->Clear();
}