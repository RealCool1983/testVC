
// 20140715Test.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy20140715TestApp:
// See 20140715Test.cpp for the implementation of this class
//

class CMy20140715TestApp : public CWinAppEx
{
public:
	CMy20140715TestApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy20140715TestApp theApp;