
// RegiserTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RegiserTest.h"
#include "RegiserTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CRegiserTestDlg dialog




CRegiserTestDlg::CRegiserTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegiserTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegiserTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRegiserTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CRegiserTestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRegiserTestDlg message handlers

BOOL CRegiserTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRegiserTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRegiserTestDlg::OnPaint()
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
HCURSOR CRegiserTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRegiserTestDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	RegistryManager();
	TCHAR szResult[100] = {0};
	TCHAR szItem[100] = {0};

	TCHAR szResult1[100] = {0};
	TCHAR szItem1[100] = {0};

	//TCHAR portName[100] = {0};
	_stprintf_s(szResult,sizeof(szResult)/sizeof(TCHAR), _T("pass") );
	_stprintf_s(szItem,sizeof(szItem)/sizeof(TCHAR), _T("burnin"));

//	strcpy(szResult, "pass");
//	strcpy(szItem, "BurnIn");

//	SetRegStringValue(szItem, szResult);
	CString sResult = NULL;
	sResult = GetRegStringValue(szItem, szResult);
	OnOK();
}


CString CRegiserTestDlg::GetRegStringValue(LPCTSTR lpszKeyName, LPCTSTR lpszDefRegValue)
{
	CString regData;
	DWORD regType, regDataLen = 1000;
	LONG res = ::RegQueryValueEx(m_hRegKey, lpszKeyName, NULL, &regType, (BYTE*)regData.GetBuffer(regDataLen), &regDataLen);

	regData.ReleaseBuffer();
	//if (res != ERROR_SUCCESS) {
		//regData = lpszDefRegValue;
		//::RegSetValueEx(m_hRegKey, lpszKeyName, NULL, REG_SZ, (BYTE*)(LPCTSTR)regData, (regData.GetLength()+1)*sizeof(TCHAR));
//	}

	return regData;
}

void CRegiserTestDlg::SetRegStringValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue)
{
	if (lpszValue == NULL)
		::RegSetValueEx(m_hRegKey, lpszKeyName, NULL, REG_SZ, (BYTE*)lpszValue, 0);
	else
		::RegSetValueEx(m_hRegKey, lpszKeyName, NULL, REG_SZ, (BYTE*)lpszValue, ((DWORD)_tcslen(lpszValue)+1)*sizeof(TCHAR));
}

void CRegiserTestDlg::RegistryManager(void)
{
	::RegCreateKey(HKEY_CURRENT_USER, _T("burnInResult"), &m_hRegKey);
	//::RegCreateKey(HKEY_CURRENT_USER, _T("Software\\UnifyUI\\EnterParameter"), &m_hRegKey);
}
