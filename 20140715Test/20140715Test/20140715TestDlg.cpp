
// 20140715TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "20140715Test.h"
#include "20140715TestDlg.h"


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


// CMy20140715TestDlg dialog




CMy20140715TestDlg::CMy20140715TestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy20140715TestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy20140715TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy20140715TestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CMy20140715TestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMy20140715TestDlg message handlers

BOOL CMy20140715TestDlg::OnInitDialog()
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

void CMy20140715TestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy20140715TestDlg::OnPaint()
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
HCURSOR CMy20140715TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy20140715TestDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here


	mkdir(); 
	//GetProperty();
	//writeLOG(_T("ABC"));
	changeType();
	OnOK();
}

void CMy20140715TestDlg::changeType(){

	/*  CString -> LPCWSTR */
	CString strF = _T("ABC");
	//CString strF = "ABC";
	LPCWSTR lpStr = strF.AllocSysString();


	CString strF1  = _T("ABC");
	LPCWSTR lpStr1;
//	lpStr1= A2CW((LPCWSTR)strF1);
}
void CMy20140715TestDlg::useMutex(){
	//Handle hMutex = NULL;
	HANDLE hMutex  = NULL;
	//hMutex = ::CreateMutex(NULL,FALSE,_T("MyMutex")); //建立Mutex
	//hMutex = ::CreateMutex(NULL,FALSE,"MyMutex"); //建立Mutex



}
void CMy20140715TestDlg::writeLOG(CString message){

	CString pthLog(_T("D:\\Log\\UI_RD"));
	pthLog = _T("D:\\Log\\UI_RD\\LOG.TXT");
	CStdioFile fLog;
	UINT nOpenFlags =
	    CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::shareDenyWrite;
	message = message + _T("\n");
	if (fLog.Open(pthLog, nOpenFlags))
	{
		fLog.SeekToEnd();
		fLog.WriteString(message);
		fLog.Close();
	}

}
void CMy20140715TestDlg::GetProperty(){
	SYSTEMTIME tLocal;
	::GetLocalTime(&tLocal);
	CString Logtime;
	Logtime.Format(_T("%04d%02d%02d-%02d:%02d:%02d"),
	               tLocal.wYear, tLocal.wMonth, tLocal.wDay,
	               tLocal.wHour, tLocal.wMinute, tLocal.wSecond);

	CString pthLog(_T("D:\\Log\\UI_RD"));
	DWORD dwFalg = ::GetFileAttributes(pthLog);
	if (dwFalg == INVALID_FILE_ATTRIBUTES){
		CreateDirectory(pthLog, NULL);
	}else{
		printf("abc");
	}

}

/*****************************************/
static bool MkDir(CString strDesPath)
{
	CFileFind cfilefind;
	return (cfilefind.FindFile(strDesPath) || CreateDirectory(strDesPath, NULL));
}

CString CMy20140715TestDlg::mkdir(){
	CString pthToolDir;
	::GetModuleFileName(NULL, pthToolDir.GetBuffer(MAX_PATH), MAX_PATH);
	pthToolDir.ReleaseBuffer();
	pthToolDir = pthToolDir.Left(pthToolDir.ReverseFind('\\'));
	CString strDesPath;

		strDesPath = pthToolDir + _T("\\Img");
		strDesPath += _T("\\m_csArrQPhoneName");


		strDesPath = pthToolDir + _T("\\Img");

	if (!MkDir(strDesPath))
		//TraceLog(MSG_INFO, "Create folder Img Failed!");
	return strDesPath;
}

/*****************************************/