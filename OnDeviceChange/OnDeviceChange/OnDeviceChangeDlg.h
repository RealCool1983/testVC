
// OnDeviceChangeDlg.h : header file
//

#pragma once


// COnDeviceChangeDlg dialog
class COnDeviceChangeDlg : public CDialog
{
// Construction

public:
	COnDeviceChangeDlg(CWnd* pParent = NULL);	// standard constructor
//	bool ExeCmd(CString Command, int i_timeout)
// Dialog Data
	enum { IDD = IDD_ONDEVICECHANGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	CEdit m_edit_time;
	unsigned int       m_i_timeCount;
	int           m_i_testtime;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();


};
