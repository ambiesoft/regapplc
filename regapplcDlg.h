// regapplcDlg.h : header file
//

#if !defined(AFX_REGAPPLCDLG_H__E6E4E697_CB0B_4547_98BF_F83F6560B114__INCLUDED_)
#define AFX_REGAPPLCDLG_H__E6E4E697_CB0B_4547_98BF_F83F6560B114__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRegapplcDlg dialog

class CRegapplcDlg : public CDialog
{
// Construction
public:
	CRegapplcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRegapplcDlg)
	enum { IDD = IDD_REGAPPLC_DIALOG };
	CString	m_strCaption;
	CString	m_strInput;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegapplcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRegapplcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString m_strTitle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGAPPLCDLG_H__E6E4E697_CB0B_4547_98BF_F83F6560B114__INCLUDED_)
