
// 20140715TestDlg.h : header file
//

#pragma once


// CMy20140715TestDlg dialog
class CMy20140715TestDlg : public CDialog
{
// Construction
public:
	CMy20140715TestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MY20140715TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	//static bool MkDir(CString strDesPath);
	CString mkdir();
	void GetProperty();
	void writeLOG(CString msg);
	void useMutex();
	void changeType();

};
