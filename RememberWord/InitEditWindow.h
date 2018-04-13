#pragma once
#ifndef _INITEDITWINDOW_H_

#endif
#include "KrUI/KrCore.h"
#include "Word.h"
#include "GetEntry.h"
#include "TinyXML2/tinyxml2.h"
using namespace KrUI;

static HWND hEditWnd = nullptr;

void InitEditWindow();
void LoadXml(KrUI::KrList* pL);