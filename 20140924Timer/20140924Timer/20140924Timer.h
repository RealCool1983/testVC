
// 20140924Timer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy20140924TimerApp:
// See 20140924Timer.cpp for the implementation of this class
//

class CMy20140924TimerApp : public CWinAppEx
{
public:
	CMy20140924TimerApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy20140924TimerApp theApp;