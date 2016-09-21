
// 20141014_TRY_QMSL_MSVC9R.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "20141014_TRY_QMSL_MSVC9R.h"
#include "20141014_TRY_QMSL_MSVC9RDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20141014_TRY_QMSL_MSVC9RApp

BEGIN_MESSAGE_MAP(CMy20141014_TRY_QMSL_MSVC9RApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMy20141014_TRY_QMSL_MSVC9RApp construction

CMy20141014_TRY_QMSL_MSVC9RApp::CMy20141014_TRY_QMSL_MSVC9RApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMy20141014_TRY_QMSL_MSVC9RApp object

CMy20141014_TRY_QMSL_MSVC9RApp theApp;


// CMy20141014_TRY_QMSL_MSVC9RApp initialization

BOOL CMy20141014_TRY_QMSL_MSVC9RApp::InitInstance()
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

	CMy20141014_TRY_QMSL_MSVC9RDlg dlg;
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

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
