// regapplc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "regapplc.h"
#include "regapplcDlg.h"


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

void ShowErrorAndExit(LPCTSTR pMessage)
{
	wstring message(pMessage);
	message += L"\r\n\r\n";

	
	message += L"ex: regapplc -title \"Register CBRevamper\" -caption \"Enter Key\" -key DERTAON -inifile \"regcbr.ini\" -section Reg -appname Reg";
	AfxMessageBox(message.c_str());
	exit(1);
}

// -title "Register CBRevamper" -caption "Enter Key" -lickey DERTAON -inifile "regcbr.ini" -keyname Reg -appname Reg
BOOL CRegapplcApp::InitInstance()
{
	wstring origcurdir = stdGetCurrentDirectory();

	Ambiesoft::CAvailableCommandLineInfo clinfo[] = {
		{1, _T("-title"),				1},
		{2, _T("-caption"),				1},
		{3, _T("-input"),				1},
		{4, _T("-lickey"),				1},
//		{5, _T("-foldertype"),			1},
		{6, _T("-inifile"),				1},
		{7, _T("-keyname"),				1},
		{8, _T("-appname"),				1},
//		{9, _T("-folder"),				1},
		{10, _T("-asadmin"),				0},
	};

	Ambiesoft::CCommandLineParser parser(__argc, __targv,
		clinfo, sizeof(clinfo)/sizeof(clinfo[0]));

	tstring title = _T("regapplc");
	tstring caption = _T("&Enter:");
	tstring input = _T("");
	tstring lickey = _T("");
//	int foldertype=0;
	tstring inifile;
	tstring keyname;
	tstring appname;
//	tstring folder;
	bool asadmin=false;
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
			break;

			case 3:
			{
				input = pInput->value_;
			}
			break;

			case 4:
			{
				lickey = pInput->value_;
			}
			break;

//			case 5:
//			{
//				foldertype = _ttoi(pInput->value_.c_str());
//				if(foldertype != 0 && foldertype != 1 && foldertype != 2)
//				{
//					wstring message = I18N(L"-foldertype must be 0 or 1");
//					ShowErrorAndExit(message.c_str());
//				}
//			}
//			break;

			case 6:
			{
				inifile = pInput->value_;
			}
			break;

			case 7:
			{
				keyname = pInput->value_;
			}
			break;

			case 8:
			{
				appname = pInput->value_;
			}
			break;

//			case 9:
//			{
//				folder = pInput->value_;
//			}
//			break;

			case 10:
			{
				asadmin=true;
			}
			break;
			default:
			{
				CString message;
				message += L"Unknown Option: ";
				message += pInput->option_.c_str();
				AfxMessageBox(message);
				return FALSE;
			}
			break;
		}
	}


/***
	if(!folder.empty())
	{
		if(foldertype != 2)
		{
			LPCTSTR pMessage = I18N(L"-foldertype should be 2 to assing -folder");
			ShowErrorAndExit(pMessage);
		}
		
		DWORD dwAttr = GetFileAttributes(folder.c_str());
		if(dwAttr == INVALID_FILE_ATTRIBUTE ||
			!(dwAttr & FILE_ATTRIBUTE_DIRECTORY))
		{
			TCHAR szT[MAX_PATH + 128];
			wsprintf(szT, I18N(L"%s is not a directory"), folder.c_str());
			ShowErrorAndExit(szT);
		}
	}
	
	if(foldertype==0)
	{
		wstring thisdir = stdGetModuleFileNameW();
		thisdir = stdGetParentDirectory(thisdir.c_str());
		if(!SetCurrentDirectory(thisdir.c_str()))
		{
			wstring message = GetLastErrorStringW(GetLastError());
			ShowErrorAndExit(message.c_str());
		}
	}
	else if(foldertype==1)
	{
	}
	else if(foldertype==2)
	{
		if(!SetCurrentDirectory(folder.c_str()))
		{
			wstring message = GetLastErrorStringW(GetLastError());
			ShowErrorAndExit(message.c_str());
		}
	}
***/

	if(!stdIsFullPath(inifile.c_str()))
	{
		ShowErrorAndExit(I18N(L"-inifile must be full path"));
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
		ShellExecute(???
			NULL,
			L"runas",
			NULL,
			command.c_str(),
			origcurdir.c_str(),
			SW_SHOW);
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
		ShellExecute(
			NULL,
			L"RunAs",
			command.c_str(),
			NULL,
			origcurdir.c_str(),
			SW_SHOW);
		return FALSE;
	}
	CRegapplcDlg dlg;
	dlg.m_strTitle = title.c_str();
	dlg.m_strCaption = caption.c_str();
	dlg.m_strInput = input.c_str();
	dlg.m_strLicKey = lickey.c_str();

	m_pMainWnd = &dlg;

	int nResponse = dlg.DoModal();
	if (nResponse != IDOK)
		return FALSE;




	return FALSE;
}
