#pragma once
#ifndef _INITMAINWINDOW_H_
#define _INITMAINWINDOW_H_

#include "KrUI/KrCore.h"
#include "Word.h"
#include "GetEntry.h"
#include "TinyXML2/tinyxml2.h"
#include "InitEditWindow.h"
using namespace KrUI;

void QueryWord(Word* pW);
void Btn_Query_Click(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
void Wnd_KeyDown(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
void List_Change(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
void Btn_Delete_Click(KrMessageHandler* kmh, WPARAM wp, LPARAM lp);
void InitMainWindow();

#endif
