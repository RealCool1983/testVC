// DLL_AFX_MANAGE_STATE.h : main header file for the DLL_AFX_MANAGE_STATE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDLL_AFX_MANAGE_STATEApp
// See DLL_AFX_MANAGE_STATE.cpp for the implementation of this class
//

class CDLL_AFX_MANAGE_STATEApp : public CWinApp
{
public:
	CDLL_AFX_MANAGE_STATEApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
