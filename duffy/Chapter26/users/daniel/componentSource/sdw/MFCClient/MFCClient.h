// MFCClient.h : main header file for the MFCCLIENT application
//

#if !defined(AFX_MFCCLIENT_H__38925FE4_21A6_11D3_A6B3_0080AD712109__INCLUDED_)
#define AFX_MFCCLIENT_H__38925FE4_21A6_11D3_A6B3_0080AD712109__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCClientApp:
// See MFCClient.cpp for the implementation of this class
//


class CMFCClientApp : public CWinApp
{
public:
	CMFCClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMFCClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCCLIENT_H__38925FE4_21A6_11D3_A6B3_0080AD712109__INCLUDED_)
