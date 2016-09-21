
// 20141014_TRY_QMSL_MSVC9RDlg.h : header file
//

#pragma once


// CMy20141014_TRY_QMSL_MSVC9RDlg dialog
class CMy20141014_TRY_QMSL_MSVC9RDlg : public CDialog
{
// Construction
public:
	CMy20141014_TRY_QMSL_MSVC9RDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MY20141014_TRY_QMSL_MSVC9R_DIALOG };

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
	afx_msg void OnBnClickedOk();
};
