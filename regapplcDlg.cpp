// regapplcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "regapplc.h"
#include "regapplcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegapplcDlg dialog

CRegapplcDlg::CRegapplcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegapplcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegapplcDlg)
	m_strCaption = _T("");
	m_strInput = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegapplcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegapplcDlg)
	DDX_Text(pDX, IDC_STATIC_CAPTION, m_strCaption);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_strInput);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRegapplcDlg, CDialog)
	//{{AFX_MSG_MAP(CRegapplcDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegapplcDlg message handlers

BOOL CRegapplcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetWindowText(m_strTitle);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRegapplcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRegapplcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRegapplcDlg::OnOK() 
{
	CDialog::OnOK();
}
