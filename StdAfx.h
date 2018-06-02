// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__DD6A0187_D404_4743_95E7_ECA13A491AA8__INCLUDED_)
#define AFX_STDAFX_H__DD6A0187_D404_4743_95E7_ECA13A491AA8__INCLUDED_
#pragma warning(disable:4786)
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "target.h"

#include <vld.h>

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <algorithm>

#include "../lsMisc/CommandLineParser.h"
#include "../lsMisc/GetLastErrorString.h"
#include "../lsMisc/stdwin32/stdwin32.h"
using namespace stdwin32;

#define INVALID_FILE_ATTRIBUTE 0xFFFFFFFF

#include "../lsMisc/I18N.h"
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__DD6A0187_D404_4743_95E7_ECA13A491AA8__INCLUDED_)
