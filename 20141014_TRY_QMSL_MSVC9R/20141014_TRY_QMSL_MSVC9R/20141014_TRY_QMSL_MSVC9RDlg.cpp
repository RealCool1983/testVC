
// 20141014_TRY_QMSL_MSVC9RDlg.cpp : implementation file
//

#include "stdafx.h"
#include "20141014_TRY_QMSL_MSVC9R.h"
#include "20141014_TRY_QMSL_MSVC9RDlg.h"
#include "QLib.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20141014_TRY_QMSL_MSVC9RDlg dialog




CMy20141014_TRY_QMSL_MSVC9RDlg::CMy20141014_TRY_QMSL_MSVC9RDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy20141014_TRY_QMSL_MSVC9RDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy20141014_TRY_QMSL_MSVC9RDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy20141014_TRY_QMSL_MSVC9RDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CMy20141014_TRY_QMSL_MSVC9RDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMy20141014_TRY_QMSL_MSVC9RDlg message handlers

BOOL CMy20141014_TRY_QMSL_MSVC9RDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy20141014_TRY_QMSL_MSVC9RDlg::OnPaint()
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
HCURSOR CMy20141014_TRY_QMSL_MSVC9RDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy20141014_TRY_QMSL_MSVC9RDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	unsigned int iPort = 7;
	HANDLE m_hPhone = NULL;
	unsigned long saharaVer = 0;
	unsigned char cret;

	QLIB_UploadBootFileBeforeHexFile(m_hPhone, "abc");

	//QLIB_UploadMultiImage
	//QLIB_UploadHexFile
	//QLIB_UploadBootFileBeforeHexFile
	OnOK();
}
