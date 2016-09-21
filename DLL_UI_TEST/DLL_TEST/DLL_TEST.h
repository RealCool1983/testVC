// DLL_TEST.h : main header file for the DLL_TEST DLL
//

#pragma once


#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDLL_TESTApp
// See DLL_TEST.cpp for the implementation of this class
//

class CDLL_TESTApp : public CWinApp
{
public:
	CDLL_TESTApp();


// Overrides
public:
	virtual BOOL InitInstance();
	
	DECLARE_MESSAGE_MAP()
};
