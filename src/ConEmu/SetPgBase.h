﻿
/*
Copyright (c) 2016 Maximus5
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#pragma once

#include <windows.h>

//HWND hMain, hExt, hFar, hKeys, hTabs, hColors, hCmdTasks, hViews, hInfo, hDebug, hUpdate, hSelection;
enum TabHwndIndex
{
	thi_Fonts = 0,    // "Main"
	thi_SizePos,      //   "Size & Pos"
	thi_Appear,       //   "Appearance"
	thi_Backgr,       //   "Background"
	thi_Tabs,         //   "Tabs"
	thi_Confirm,      //   "Confirmations"
	thi_Taskbar,      //   "Task bar"
	thi_Update,       //   "Update"
	thi_Startup,      // "Startup"
	thi_Tasks,        //   "Tasks"
	thi_Comspec,      //   "ComSpec"
	thi_Environment,  //   "Environment"
	thi_Ext,          // "Features"
	thi_Cursor,       //   "Text cursor"
	thi_Colors,       //   "Colors"
	thi_Transparent,  //   "Transparency"
	thi_Status,       //   "Status bar"
	thi_Apps,         //   "App distinct"
	thi_Integr,       // "Integration"
	thi_DefTerm,      //   "Default terminal"
	thi_Keys,         // "Keys & Macro"
	thi_KeybMouse,    //   "Controls"
	thi_MarkCopy,     //   "Mark & Copy"
	thi_Paste,        //   "Paste"
	thi_Hilight,      //   "Highlight"
	thi_Far,          // "Far Manager"
	thi_FarMacro,     //   "Far macros"
	thi_Views,        //   "Views"
	thi_Info,         // "Info"
	thi_Debug,        //   "Debug"
					  //
	thi_Last
};

#if 0
enum ConEmuSetupItemType
{
	sit_Bool = 1,
	sit_Byte = 2,
	sit_Char = 3,
	sit_Long = 4,
	sit_ULong = 5,
	sit_Rect = 6,
	sit_FixString = 7,
	sit_VarString = 8,
	sit_MSZString = 9,
	sit_FixData = 10,
	sit_Fonts = 11,
	sit_FontsAndRaster = 12,
};
struct ConEmuSetupItem
{
	//DWORD nDlgID; // ID диалога
	DWORD nItemID; // ID контрола в диалоге, 0 - последний элемент в списке
	ConEmuSetupItemType nDataType; // Тип данных

	void* pData; // Ссылка на элемент в gpSet
	size_t nDataSize; // Размер или maxlen, если pData фиксированный

	ConEmuSetupItemType nListType; // Тип данных в pListData
	const void* pListData; // Для DDLB - можно задать список
	size_t nListItems; // количество элементов в списке

	#ifdef _DEBUG
	BOOL bFound; // для отладки корректности настройки
	#endif

	//wchar_t sItemName[32]; // Имя элемента в настройке (reg/xml)
};
#endif

struct ConEmuSetupPages
{
	int              DialogID;     // Page Dialog ID (IDD_SPG_FONTS, ...)
	int              Level;        // 0, 1
	wchar_t          PageName[64]; // Label in treeview
	TabHwndIndex     PageIndex;    // thi_Fonts, thi_SizePos, etc.
	bool             Collapsed;
	// Filled after creation
	bool             DpiChanged;
	HTREEITEM        hTI;
	#if 0
	ConEmuSetupItem* pItems;
	#endif
	HWND             hPage;
	CSetPgBase*      pPage;
	CDpiForDialog*   pDpiAware;
	CDynDialog*      pDialog;
};

class CSetPgBase
{
public:
	CSetPgBase();
	virtual ~CSetPgBase();

public:
	static INT_PTR CALLBACK pageOpProc(HWND hDlg, UINT messg, WPARAM wParam, LPARAM lParam);
	static HWND CreatePage(ConEmuSetupPages* p);

public:
	// Methods

protected:
	// Members

};

