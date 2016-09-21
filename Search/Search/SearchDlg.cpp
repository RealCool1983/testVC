
// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Search.h"
#include "SearchDlg.h"
#include "io.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSearchDlg dialog




CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CSearchDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSearchDlg message handlers

BOOL CSearchDlg::OnInitDialog()
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

void CSearchDlg::OnPaint()
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
HCURSOR CSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSearchDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnOK();
	run_searchFile();
}

bool CSearchDlg::run_searchFile(){

	CEdit* wEdit1=(CEdit*)GetDlgItem(IDC_EDIT1); // 取得 Edit1 物件指標
	CEdit* wEdit2=(CEdit*)GetDlgItem(IDC_EDIT2); //      Edit2
	CEdit* wEdit3=(CEdit*)GetDlgItem(IDC_EDIT3); //      Edit2


	// 讀取使用者的輸入
	CString strSourceFile;
	CString strWriteFile;
	CString strKeyWord;
	wEdit1->GetWindowText(strSourceFile);
	wEdit2->GetWindowText(strWriteFile);
	wEdit3->GetWindowText(strKeyWord);

	/********************/

	FILE *input;
	FILE *output;
	char string[150];
	CStdioFile readFile, writeFile;
	CString strLine;

	//CString str_iniPath = ("D:\\03.Factory\\08.iF1\\fastboot20131216_2\\TEST2.txt");
	//CString str_iniPath = ("D:\\Log\\UI_RD\\system.CSV");
	//CString str_iniPathW = ("D:\\03.Factory\\08.iF1\\fastboot20131216_2\\TEST_OK.txt");

//	if (_taccess(str_iniPath, 0) != 0) 
//		return false;
	if (_taccess(strSourceFile, 0) != 0) 
		return false;
//	if (_taccess(strWriteFile, 0) != 0) 
	//	return false;

	readFile.Open(strSourceFile , CFile::modeRead);
	writeFile.Open(strWriteFile ,CFile::modeCreate| CFile::modeReadWrite);
	readFile.SeekToBegin(); 
	writeFile.SeekToBegin(); 
	writeFile.Write("/xff/xfe", 2);
	writeFile.Write( "\n",1);  

	while(readFile.ReadString(strLine))
	{
		if (strLine.Find(strKeyWord) == 0 ){

			writeFile.WriteString(strLine);
			//writeFile.Write(strLine,75);         
			writeFile.Write( "\n",1);   
			writeFile.Flush();
		}
	}
	readFile.Close();

	return true;
}


