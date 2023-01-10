
// MFCLoginDlg.h : header file
//

#pragma once


// CMFCLoginDlg dialog
class CMFCLoginDlg : public CDialogEx
{
// Construction
public:
	CMFCLoginDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCLOGIN_DIALOG };
#endif

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
	CString m_name;
	CString m_pass;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString m_passtwo;
	CString m_passagain;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
