// regapplc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "regapplc.h"
#include "regapplcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "../MyUtility/CommandLineParser.h"
using namespace Ambiesoft;

/////////////////////////////////////////////////////////////////////////////
// CRegapplcApp

BEGIN_MESSAGE_MAP(CRegapplcApp, CWinApp)
	//{{AFX_MSG_MAP(CRegapplcApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegapplcApp construction

CRegapplcApp::CRegapplcApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRegapplcApp object

CRegapplcApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRegapplcApp initialization

BOOL CRegapplcApp::InitInstance()
{
	Ambiesoft::CCommandLineInfo clinfo[] = {
		{1, _T("aaa"), Ambiesoft::ArgType_Int, 0},
		{2, _T("affeaa"), Ambiesoft::ArgType_Int, 0},
	};

	Ambiesoft::CCommandLineParser parser;
	if(!parser.construct(clinfo, sizeof(clinfo)/sizeof(clinfo[0])))
	{
		return FALSE;
	}

	CRegapplcDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
