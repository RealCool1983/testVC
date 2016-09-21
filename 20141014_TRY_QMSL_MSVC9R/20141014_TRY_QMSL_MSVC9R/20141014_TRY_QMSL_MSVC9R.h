
// 20141014_TRY_QMSL_MSVC9R.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy20141014_TRY_QMSL_MSVC9RApp:
// See 20141014_TRY_QMSL_MSVC9R.cpp for the implementation of this class
//

class CMy20141014_TRY_QMSL_MSVC9RApp : public CWinAppEx
{
public:
	CMy20141014_TRY_QMSL_MSVC9RApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy20141014_TRY_QMSL_MSVC9RApp theApp;