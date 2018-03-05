#include "KrUI/KrCore.h"
#include "InitMainWindow.h"
using namespace KrUI;

KrUI::KrUIManager* pUi = KrUIManager::GetpKrUIManager();


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	pUi->Initialize(hInstance);
	InitMainWindow();
	return pUi->MessageLoop();
}

