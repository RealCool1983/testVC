
// 20140924TimerDlg.h : header file
//

#pragma once


// CMy20140924TimerDlg dialog
class CMy20140924TimerDlg : public CDialog
{
// Construction
public:
	CMy20140924TimerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MY20140924TIMER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
private:
	int       m_i_timeCount;/*lion*/
	CEdit m_edit_time;/*lion*/
	CEdit* pEdit;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);/*lion*/
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
