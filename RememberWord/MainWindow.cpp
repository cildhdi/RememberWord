#include "MainWindow.h"
#include "Word.h"
#include "KrUI/Tools/KrTools.h"
MainWindow::MainWindow()
{
	pEdit = nullptr;
	pLbl = nullptr;
	RegMsg(KM_CREATE, reinterpret_cast<MSGPROC>(Wnd_Create));
}

void MainWindow::Btn_Click(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	MainWindow* pWnd = dynamic_cast<MainWindow*> (dynamic_cast<KrButton*>(kmh)->GetParantWindow());
	if (pWnd->pEdit == nullptr || pWnd->pLbl == nullptr)return;
	Word* pW = new Word(pWnd->pEdit->GetText());
	GetEntry(pW);
	pWnd->pLbl->SetName(pW->GetDetail());
	int height = static_cast<int>(GetTextSize(pW->GetDetail(), pWnd->pLbl->GetFont(), Gdiplus::Rect(0, 0, pWnd->pLbl->GetWidth(), pWnd->pLbl->GetHeight())).Height);
	if (((height + pWnd->pLbl->GetY()) < 500) && pWnd->GetHeight() != 500)
	{
		pWnd->SetHeight(500);
	}
	else
	{
		pWnd->SetHeight(height + pWnd->pLbl->GetY() + 30);
	}
	//MessageBox(NULL, pW->GetDetail().c_str(), L"查询结果：", MB_OK);
}

void MainWindow::Wnd_Create(KrMessageHandler* kmh, WPARAM wp, LPARAM lp)
{
	dynamic_cast<MainWindow*>(kmh)->pEdit = dynamic_cast<KrEdit*>(dynamic_cast<MainWindow*>(kmh)->AddControl(KrEdit_t, L"", 50, 70, 400, 35));
	KrButton* pBtn = dynamic_cast<KrButton*>(dynamic_cast<MainWindow*>(kmh)->AddControl(KrButton_t, L"查询", 500, 70, 100, 35));
	pBtn->RegMsg(KM_CLICK, reinterpret_cast<MSGPROC>(Btn_Click));
	dynamic_cast<MainWindow*>(kmh)->pLbl = dynamic_cast<KrLabel*>(dynamic_cast<MainWindow*>(kmh)->AddControl(KrLabel_t, L"", 50, 120, 600, 600));
	dynamic_cast<MainWindow*>(kmh)->pLbl->SetLineAlignment(Gdiplus::StringAlignmentNear);
}