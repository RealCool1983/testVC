// Dlltest.h : main header file for the Dlltest DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDlltestApp
// See Dlltest.cpp for the implementation of this class
//

class CDlltestApp : public CWinApp
{
public:
	CDlltestApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
