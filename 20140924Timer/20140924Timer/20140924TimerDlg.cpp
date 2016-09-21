
// 20140924TimerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "20140924Timer.h"
#include "20140924TimerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20140924TimerDlg dialog

CMy20140924TimerDlg::CMy20140924TimerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy20140924TimerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


}

void CMy20140924TimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_Time, m_edit_time);/*lion*/

}

BEGIN_MESSAGE_MAP(CMy20140924TimerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()/*lion*/
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CMy20140924TimerDlg message handlers

BOOL CMy20140924TimerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_i_timeCount = 0; /*lion*/
	::SetTimer(m_hWnd,1,1000,NULL);

	pEdit = new CEdit;
	pEdit->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP|ES_CENTER  ,
	   CRect(50, 50, 90, 70), this, 1);
	pEdit->SetWindowTextW(_T("abc"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


void CMy20140924TimerDlg::OnTimer(UINT_PTR nIDEvent)/*lion*/
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnTimer(nIDEvent);

	CString str_temp;

	if( m_i_timeCount == 5)
	{
		delete pEdit;
	}else if ( m_i_timeCount < 5)
	{
		str_temp.Format(_T("%d"),m_i_timeCount);
		//m_edit_time.SetWindowText(str_temp);
		pEdit->SetWindowTextW(str_temp);	
	}
	 ++m_i_timeCount;

}


void CMy20140924TimerDlg::OnPaint()
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
HCURSOR CMy20140924TimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


