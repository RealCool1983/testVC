
// CSingleLockTest2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CSingleLockTest2.h"
#include "CSingleLockTest2Dlg.h"
#include "afxmt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//CSingleLock singleLock(&m_CritSection);


// CCSingleLockTest2App

BEGIN_MESSAGE_MAP(CCSingleLockTest2App, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCSingleLockTest2App construction

CCSingleLockTest2App::CCSingleLockTest2App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCSingleLockTest2App object

CCSingleLockTest2App theApp;


// CCSingleLockTest2App initialization

BOOL CCSingleLockTest2App::InitInstance()
{
	CWinAppEx::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CCSingleLockTest2Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	printf("ABC");
	
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}



// Test0622.cpp : Defines the entry point for the console application.
//

