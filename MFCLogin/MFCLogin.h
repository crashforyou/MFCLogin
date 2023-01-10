
// MFCLogin.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCLoginApp:
// See MFCLogin.cpp for the implementation of this class
//

class CMFCLoginApp : public CWinApp
{
public:
	CMFCLoginApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCLoginApp theApp;
