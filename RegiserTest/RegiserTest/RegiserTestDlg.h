
// RegiserTestDlg.h : header file
//

#pragma once


// CRegiserTestDlg dialog
class CRegiserTestDlg : public CDialog
{
// Construction
public:
	CRegiserTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_REGISERTEST_DIALOG };

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

	HKEY m_hRegKey;
	void SetRegStringValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue);
	CString GetRegStringValue(LPCTSTR lpszKeyName, LPCTSTR lpszDefRegValue);
	void RegistryManager(void);
	
public:
	afx_msg void OnBnClickedOk();
};
