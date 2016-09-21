
// CSingleLockTest2Dlg.h : header file
//

#pragma once

static CMutex m_CritSection;
// CCSingleLockTest2Dlg dialog
class CCSingleLockTest2Dlg : public CDialog
{
// Construction
public:
	CCSingleLockTest2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CSINGLELOCKTEST2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnEnChangeEdit1();
	CWinThread *the_A_Thread;
	CWinThread *the_B_Thread;
	void EnterCriticalSection_A();
	void EnterCriticalSection_B();
	static UINT A_Thread(LPVOID pParam);
	static UINT B_Thread(LPVOID pParam);
	CEdit* pEdit;
};
