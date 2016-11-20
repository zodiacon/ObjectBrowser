
// ObjectBrowser.h : main header file for the ObjectBrowser application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CObjectBrowserApp:
// See ObjectBrowser.cpp for the implementation of this class
//

class CObjectBrowserApp : public CWinApp
{
public:
	CObjectBrowserApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CObjectBrowserApp theApp;
