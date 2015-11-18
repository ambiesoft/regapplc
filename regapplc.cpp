// regapplc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "regapplc.h"
#include "regapplcDlg.h"

#include "../MyUtility/CommandLineParser.h"
using namespace Ambiesoft;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


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
void CRegapplcApp::DoReg(LPCTSTR pFolder, LPCTSTR pIni, LPCTSTR pSec, LPCTSTR pApp)
{

}

BOOL CRegapplcApp::InitInstance()
{
	Ambiesoft::CAvailableCommandLineInfo clinfo[] = {
		{1, _T("-title"),				1},
		{2, _T("-caption"),				1},
		{3, _T("-input"),				1},
		{4, _T("-key"),					1},
//		{5, _T("-folder"),				1},
		{6, _T("-inifile"),				1},
		{7, _T("-section"),				1},
		{8, _T("-appname"),				1},
		{9, _T("-doreg"),				0},
	};

	Ambiesoft::CCommandLineParser parser(__argc, __targv,
		clinfo, sizeof(clinfo)/sizeof(clinfo[0]));

	tstring title = _T("regapplc");
	tstring caption = _T("&Enter:");
	tstring input = _T("");
	tstring key = _T("");

	while(CInputCommandLineInfo* pInput = parser.GetNext())
	{
		switch(pInput->nID_)
		{
			case 1:
			{
				title = pInput->value_;
			}
			break;

			case 2:
			{
				caption = pInput->value_;
			}

			case 3:
			{
				input = pInput->value_;
			}
			break;

			case 4:
			{
				key = pInput->value_;
			}
			break;

			default:
				ASSERT(FALSE);
				break;
		}
	}

	CRegapplcDlg dlg;
	dlg.m_strTitle = title.c_str();
	dlg.m_strCaption = caption.c_str();
	dlg.m_strInput = input.c_str();
	dlg.m_strKey = key.c_str();

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
