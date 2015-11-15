// regapplc.h : main header file for the REGAPPLC application
//

#if !defined(AFX_REGAPPLC_H__2693DB7C_78E9_4630_9328_42A12E1C1DEA__INCLUDED_)
#define AFX_REGAPPLC_H__2693DB7C_78E9_4630_9328_42A12E1C1DEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRegapplcApp:
// See regapplc.cpp for the implementation of this class
//

class CRegapplcApp : public CWinApp
{
public:
	CRegapplcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegapplcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRegapplcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGAPPLC_H__2693DB7C_78E9_4630_9328_42A12E1C1DEA__INCLUDED_)
