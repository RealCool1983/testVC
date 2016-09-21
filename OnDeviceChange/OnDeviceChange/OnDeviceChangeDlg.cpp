
// OnDeviceChangeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OnDeviceChange.h"
#include "OnDeviceChangeDlg.h"
#include <string>
#include <vector>

#include "Winbase.h"
//#include <afxwin.h>

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


// COnDeviceChangeDlg dialog


void COnDeviceChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_Time, m_edit_time);
}


COnDeviceChangeDlg::COnDeviceChangeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COnDeviceChangeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_i_timeCount = 0;
	m_i_testtime = 2000;
}


BEGIN_MESSAGE_MAP(COnDeviceChangeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &COnDeviceChangeDlg::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// COnDeviceChangeDlg message handlers

BOOL COnDeviceChangeDlg::OnInitDialog()
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

void COnDeviceChangeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COnDeviceChangeDlg::OnPaint()
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
HCURSOR COnDeviceChangeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CString GetDirectory_Img()
{
	CString strDesPath;
	CString pthToolDir;
	::GetModuleFileName(NULL, pthToolDir.GetBuffer(MAX_PATH), MAX_PATH);
	pthToolDir.ReleaseBuffer();
	pthToolDir = pthToolDir.Left(pthToolDir.ReverseFind('\\'));
	strDesPath = pthToolDir;
//	strDesPath += _T("\\Img");
	CFileFind cfilefind;
	if (!cfilefind.FindFile(strDesPath))
	{
		if (!CreateDirectory(strDesPath, NULL))
		{
			AfxMessageBox(_T("Create folder Img Failed!"));
		}
	}
	return strDesPath;
}

void COnDeviceChangeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnTimer(nIDEvent);

	CString str_temp;

	str_temp.Format(_T("%d"), ++m_i_timeCount);
	m_edit_time.SetWindowText(str_temp);

}


void COnDeviceChangeDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	/*Test print err msg by afxDump */

	CString csDirectory = GetDirectory_Img();

	GetDlgItem(IDC_EDIT_Time)->SetWindowText(_T("ABC"));
	CString csText; 


	CString str_temp;

	str_temp.Format(_T("%d"), ++m_i_timeCount);
	m_edit_time.SetWindowText(str_temp);
	::SetTimer(m_hWnd,1,1000,NULL);



	//m_edit_time.SetWindowText(_T("0000"));
	//SetTimer(1,1000,NULL);
		
	//for ( int i = 0 ; i < 10 ; i ++){
	//	csText.Format(_T("%d"), i );
	//	GetDlgItem(IDC_EDIT_Time)->SetWindowText(csText);
	////	GetDlgItem(IDC_EDIT1)->
	//	//GetDlgItem(IDC_EDIT1)->GetWindowText(csText); 
	//	Sleep(1000);
	//}


	
//#ifdef _DEBUG
//
//	std::vector<int> vInt;
//	std::vector<int>::iterator iter;
//	vInt.push_back(100);
//	vInt.push_back(200);
//	vInt.push_back(300);
//
//	CString cs_string;
//
//	for(iter = vInt.begin(); iter != vInt.end(); iter++){
//		int nTmp = *iter;
//		cs_string.Format(_T("nTmp = %d, iter = %d\n"), nTmp, *iter);
//
//		TRACE( cs_string.GetString());
//	}
//
//
//	//vInt vA, vB;
//	//CString a = _T("ABCDE");
//	//std::string pstrRange;
//	//pstrRange =  CW2A( a.GetString());
//	//pstrRange =  CT2A( a.GetString());
//
//	std::string std_a = "11.3740100861 ";
//	double 	dPower = atof(std_a.c_str());
//
////	AfxMessageBox( pstrRange.);
//	//	afxDump << pstrRange << " end\n";
//		//afxDump <<"abc : " << i << " end\n";
//
//
//	  char name[20], tel[50], field[20], areaCode[20], code[20];
//	  int age;
//	  //sscanf("name:john age:40 tel:082-313530", "%s", name);
//	  //afxDump  << name << "\n";
//	  //sscanf("name:john age:40 tel:082-313530", "%8s", name);
//	  //afxDump  << name << "\n";
//	  sscanf("name:john age:40 tel:082-313530", "%[^:]", name);
//	  afxDump  << name << "\n";
//	  sscanf("name:john age:40 tel:082-313530", "%*[^:]", name);
//	  afxDump  << name << "\n";
//	  sscanf("name:john age:40 tel:082-313530", "%[^:]:%s", field, name);
//	   afxDump  << field << ",," << name << "\n";
//	  sscanf("name:john age:40 tel:082-313530", "name:%s age:%d tel:%s", name, &age, tel);
//	   afxDump  << name << "," <<  age << "," << tel << "\n";
//	//  printf("%s %d %s\n", name, age, tel);
//	  sscanf("name:john age:40 tel:082-313530", "%*[^:]:%s %*[^:]:%d %*[^:]:%s", name, &age, tel);
//	  afxDump  << name << "," <<  age << "," << tel << "\n";
////	  printf("%s %d %s\n", name, age, tel);
//	 char protocol[10], site[50], path[50];
//	  sscanf("http://ccckmit.wikidot.com/cp/list/hello.txt", 
//			 "%[^:]:%*2[/]%[^/]/%[a-zA-Z0-9._/-]", 
//			 protocol, site, path);
//	  afxDump << "protocol=" << protocol << " site" << site << " path" << path ;
//#endif

	//OnOK();
}


