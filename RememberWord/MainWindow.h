#pragma once
#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include "KrUI/KrCore.h"
using namespace KrUI;
class MainWindow :public KrWindow
{
public:
	KrEdit * pEdit;
	KrLabel* pLbl;
	KrButton* pBtn;
public:
	MainWindow();
	static void Btn_Click(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
	static void Wnd_Create(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
	static void Btn_KeyDown(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
};

#endif