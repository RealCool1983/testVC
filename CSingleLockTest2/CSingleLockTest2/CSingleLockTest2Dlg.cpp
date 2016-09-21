
// CSingleLockTest2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "CSingleLockTest2.h"
#include "CSingleLockTest2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCSingleLockTest2Dlg dialog




CCSingleLockTest2Dlg::CCSingleLockTest2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCSingleLockTest2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCSingleLockTest2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCSingleLockTest2Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	//ON_EN_CHANGE(IDC_EDIT1, &CCSingleLockTest2Dlg::OnEnChangeEdit1)
END_MESSAGE_MAP()

void CCSingleLockTest2Dlg::EnterCriticalSection_A(){
	CSingleLock singleLock(&m_CritSection);
	for(int i = 0 ; i < 100 ; i ++){

		singleLock.Lock();  // Attempt to lock the shared resource
		if (singleLock.IsLocked())  // Resource has been locked
		{
				CString csMsg;
				csMsg.Format(_T("EnterCriticalSection_A = %d /r/n"), i);
			//	printf("EnterCriticalSection_A Lock/n");
			//	OutputDebugString(csMsg);

		//   int nLength = pEdit->SendMessage(WM_GETTEXTLENGTH);
		//   pEdit->SetSel(nLength, nLength);
		   pEdit->SetSel(-1,-1);
		   pEdit->ReplaceSel(csMsg);
		   
		   pEdit->UpdateData(true);

				Sleep(500);

		   //...use the shared resource...

		   // Now that we are finished, 
		   // unlock the resource for others.
		   singleLock.Unlock();
		}
	}
}

void CCSingleLockTest2Dlg::EnterCriticalSection_B(){
	CSingleLock singleLock(&m_CritSection);

	for(int i = 0 ; i < 100 ; i ++){
		singleLock.Lock();  // Attempt to lock the shared resource
		if (singleLock.IsLocked())  // Resource has been locked
		{
			CString csMsg("Start");
			//for(int i = 0 ; i < 5 ; i ++){
				csMsg.Format(_T("EnterCriticalSection_B = %d /r/n"), i);
			//	printf("EnterCriticalSection_A Lock/n");
				OutputDebugString(csMsg);

			   //int nLength = pEdit->SendMessage(WM_GETTEXTLENGTH);
			   //pEdit->SetSel(nLength, nLength);
			   pEdit->SetSel(-1,-1);
			   pEdit->ReplaceSel(csMsg);
			 //  pEdit->ReplaceSel(csMsg);

				//printf("EnterCriticalSection_B Lock/n");
				Sleep(1000);
		//	}

		   //...use the shared resource...

		   // Now that we are finished, 
		   // unlock the resource for others.
		   singleLock.Unlock();
		}
	}
}

UINT CCSingleLockTest2Dlg::A_Thread(LPVOID pVar){
	CCSingleLockTest2Dlg *pCSingleLockTest2App = (CCSingleLockTest2Dlg*)pVar;
	pCSingleLockTest2App->EnterCriticalSection_A();
//	EnterCriticalSection_A();
	return 0;
}

UINT CCSingleLockTest2Dlg::B_Thread(LPVOID pVar){
	CCSingleLockTest2Dlg *pCSingleLockTest2App = (CCSingleLockTest2Dlg*)pVar;
	pCSingleLockTest2App->EnterCriticalSection_B();
//	EnterCriticalSection_B();
	return 0;
}


// CCSingleLockTest2Dlg message handlers

BOOL CCSingleLockTest2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

pEdit = new CEdit();
	pEdit->Create( ES_MULTILINE |WS_CHILD | WS_VISIBLE |ES_AUTOVSCROLL ,
	   CRect(50, 50, 400, 300), this, 1);
	//pEdit->SetWindowTextW(_T("abc"));

	//CString csMsg("Start");
	//OutputDebugString(csMsg);
	the_A_Thread = AfxBeginThread(A_Thread , (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	the_B_Thread = AfxBeginThread(B_Thread , (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	//EnterCriticalSection_A();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCSingleLockTest2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCSingleLockTest2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


