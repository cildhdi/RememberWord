#include <windows.h>
#include "KrUI/KrCore.h"
#include "MainWindow.h"

using namespace KrUI;
KrUI::KrUIManager* pUi = KrUIManager::GetpKrUIManager();

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	pUi->Initialize(hInstance);

	pUi->AddWindow(new MainWindow, L"6374", 0, 0, 500, 300);

	return pUi->MessageLoop();
}