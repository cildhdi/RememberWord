#include "MainWindow.h"
using namespace KrUI;
KrUI::KrUIManager* pUi = KrUIManager::GetpKrUIManager();

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	pUi->Initialize(hInstance);
	int width = 650, height = 500, cx = GetSystemMetrics(SM_CXSCREEN), cy = GetSystemMetrics(SM_CYSCREEN);
	KrWindow* pWnd = dynamic_cast<KrWindow*>(pUi->AddWindow(new MainWindow, L"¿¼Ç°±³µ¥´Ê", (cx - width) / 2, (cy - height) / 2, width, height));
	return pUi->MessageLoop();
}