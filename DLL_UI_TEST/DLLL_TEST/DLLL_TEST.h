// DLLL_TEST.h : main header file for the DLLL_TEST DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDLLL_TESTApp
// See DLLL_TEST.cpp for the implementation of this class
//

class CDLLL_TESTApp : public CWinApp
{
public:
	CDLLL_TESTApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
