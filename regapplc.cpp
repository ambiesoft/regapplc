// regapplc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "regapplc.h"
#include "regapplcDlg.h"


using namespace Ambiesoft;
using namespace std;

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


bool isnotalnum(TCHAR t)
{
	return !_istalnum(t);
}

BOOL IsUserAdmin(HANDLE hToken=NULL)
{
    HANDLE hAccessToken;
    UCHAR InfoBuffer[4096]; 
    PTOKEN_GROUPS ptgGroups = (PTOKEN_GROUPS)InfoBuffer;
    DWORD dwInfoBufferSize;
    PSID psidAdministrators;
    SID_IDENTIFIER_AUTHORITY siaNtAuthority = SECURITY_NT_AUTHORITY;
    UINT x;
    BOOL bSuccess;


    if (hToken)
        hAccessToken = hToken;
    else
        if(!OpenProcessToken(GetCurrentProcess(),TOKEN_READ,&hAccessToken))
            //        return(FALSE);
            return(TRUE);

    bSuccess =GetTokenInformation(hAccessToken,TokenGroups,InfoBuffer,
        sizeof(InfoBuffer), &dwInfoBufferSize);

    CloseHandle(hAccessToken);

    if( !bSuccess )
        //        return FALSE;
        return(TRUE);

    if(!AllocateAndInitializeSid(&siaNtAuthority, 2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &psidAdministrators))
        //    return FALSE;
        return(TRUE);

    // assume that we don't find the admin SID.
    bSuccess = FALSE;

    for(x=0;x<ptgGroups->GroupCount;x++)
    {
        if(EqualSid(psidAdministrators, ptgGroups->Groups[x].Sid) )
        {
            bSuccess = TRUE;
            break;
        }
    }
    FreeSid(psidAdministrators);
    return bSuccess;
}

bool isSepEnd(LPCTSTR p, TCHAR sep)
{
	if(*p==0)
		return true;

	if(*p==sep)
		return true;

	if(sep==_T(' '))
		return !!_istspace(*p);

	return false;
}

void getappandparam(LPCTSTR pCommand, wstring&app, wstring&param)
{
	if(!pCommand)
		return;

	while(_istspace(*pCommand))
		++pCommand;

	TCHAR sep = *pCommand;
	LPCTSTR pStart=NULL;
	if(sep==_T('"') || sep==_T('\''))
	{
		app += sep;
		pStart = pCommand+1;
	}
	else
	{
		sep=_T(' ');
		pStart = pCommand;
	}

	for( ;  ; ++pStart)
	{
		app += *pStart;
		if(isSepEnd(pStart,sep))
		{
			++pStart;
			break;
		}
	}
	
	while(_istspace(*pStart))
		++pStart;
	param = pStart;
	return;
}

bool shellrunas(LPCTSTR pCommand, LPCTSTR pCurDir)
{
	wstring app,param;
	getappandparam(pCommand,app,param);

	TRACE(app.c_str());
	TRACE(_T("\r\n"));
	TRACE(param.c_str());
	TRACE(_T("\r\n"));

	SHELLEXECUTEINFO sei = {0};

	sei.cbSize = sizeof(sei);
	sei.lpVerb = L"runas";
	sei.lpFile = app.c_str();
	sei.lpParameters = param.c_str();
	sei.nShow = SW_SHOW;
	sei.lpDirectory = pCurDir;
	return !!ShellExecuteEx(&sei);
}

void ShowErrorAndExit(LPCTSTR pMessage)
{
	wstring message(pMessage);
	message += L"\r\n\r\n";

	
	message += L"ex: regapplc -title \"Register CBRevamper\" -caption \"Enter Key\" -key DERTAON -inifile \"C:\\dir\\regcbr.ini\" -section Reg -appname Reg";
	AfxMessageBox(message.c_str());
	exit(1);
}

// -title "Register CBRevamper" -caption "Enter Key" -lickey DERTAON -inifile "regcbr.ini" -keyname Reg -appname Reg
BOOL CRegapplcApp::InitInstance()
{
	wstring origcurdir = stdGetCurrentDirectory();

//	Ambiesoft::CAvailableCommandLineInfo clinfo[] = {
//		{1, _T("-title"),				1},
//		{2, _T("-caption"),				1},
//		{3, _T("-input"),				1},
//		{4, _T("-lickey"),				1},
////		{5, _T("-foldertype"),			1},
//		{6, _T("-inifile"),				1},
//		{7, _T("-keyname"),				1},
//		{8, _T("-appname"),				1},
////		{9, _T("-folder"),				1},
//		{10, _T("-asadmin"),				0},
//	};

	Ambiesoft::CCommandLineParser parser;

	tstring title = _T("regapplc");
	parser.AddOption(L"-title", 1, &title);

	tstring caption = _T("&Enter:");
	parser.AddOption(L"-caption", 1, &caption);

	tstring input = _T("");
	parser.AddOption(L"-input", 1, &input);

	tstring lickey = _T("");
	parser.AddOption(L"-lickey", 1, &lickey);


	tstring inifile;
	parser.AddOption(L"-inifile", 1, &inifile);

	tstring keyname;
	parser.AddOption(L"-keyname", 1, &keyname);

	tstring appname;
	parser.AddOption(L"-appname", 1, &appname);

//	tstring folder;
	bool asadmin=false;
	parser.AddOption(L"-asadmin", 0, &asadmin);

	parser.Parse();

	if (parser.hadUnknownOption())
	{
		CString message;
		message += L"Unknown Option: ";
		message += parser.getUnknowOptionStrings().c_str();
		AfxMessageBox(message);
		return FALSE;
	}


	if(!stdIsFullPath(inifile.c_str()))
	{
		ShowErrorAndExit(I18N(L"-inifile must be full path"));
	}

	if(lickey.empty())
	{
		ShowErrorAndExit(I18N(L"-lickey must be specified"));
	}

	if(appname.empty())
	{
		ShowErrorAndExit(I18N(L"-appname must be specified"));
	}
	if(keyname.empty())
	{
		ShowErrorAndExit(I18N(L"-keyname must be specified"));
	}

	if(lstrcmpi(appname.c_str(), L"test")==0)
	{
		ShowErrorAndExit(I18N(L"-appname must not be \"test\""));
	}
	if(lstrcmpi(keyname.c_str(), L"test")==0)
	{
		ShowErrorAndExit(I18N(L"-keyname must not be \"test\""));
	}

	if(find_if(appname.begin(), appname.end(), isnotalnum) != appname.end())
	{
		ShowErrorAndExit(I18N(L"-appname must not be alnum"));
	}
	if(find_if(keyname.begin(), keyname.end(), isnotalnum) != keyname.end())
	{
		ShowErrorAndExit(I18N(L"-keyname must not be alnum"));
	}
	
	
	TCHAR szR[16];
	wsprintf(szR, L"%d", GetTickCount());
	if(!WritePrivateProfileString(L"Test", L"Test", szR, inifile.c_str()))
	{
		DWORD dwL = GetLastError();
		if(asadmin)
		{
			wstring message = GetLastErrorString(dwL);
			ShowErrorAndExit(message.c_str());
		}

		wstring command=GetCommandLine();
		command += L" -asadmin";

		shellrunas(command.c_str(), origcurdir.c_str());
		return FALSE;
	}
	TCHAR szRT[16];
	GetPrivateProfileString(L"Test", L"Test", L"", szRT, sizeof(szRT)/sizeof(szRT[0]), inifile.c_str());
	DWORD dwGPPS = GetLastError();
	if(lstrcmp(szR,szRT) != 0)
	{
		if(asadmin)
		{
			wstring message = GetLastErrorString(dwGPPS);
			ShowErrorAndExit(message.c_str());
		}

		wstring command=GetCommandLine();
		command += L" -asadmin";
		shellrunas(command.c_str(), origcurdir.c_str());
		return FALSE;
	}
	CRegapplcDlg dlg;
	dlg.m_strTitle = title.c_str();
	dlg.m_strCaption = caption.c_str();
	dlg.m_strInput = input.c_str();


	m_pMainWnd = &dlg;

	int nResponse = dlg.DoModal();
	if (nResponse != IDOK)
		return FALSE;

	
	while(PumpMessage())
		;

	if(dlg.m_strInput != lickey.c_str())
	{
		AfxMessageBox(I18N(L"Wrong key"));
	}
	else
	{
		if(!WritePrivateProfileString(appname.c_str(),keyname.c_str(),_T("1"), inifile.c_str()))
		{
			AfxMessageBox(I18N(L"Registration Failed"));
		}
		else
		{
			AfxMessageBox(I18N(L"Registration Succeeded"), MB_ICONINFORMATION);
		}
	}


	return FALSE;
}
