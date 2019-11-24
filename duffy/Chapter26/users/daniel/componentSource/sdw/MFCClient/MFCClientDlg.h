// MFCClientDlg.h : header file
//

#if !defined(AFX_MFCCLIENTDLG_H__38925FE6_21A6_11D3_A6B3_0080AD712109__INCLUDED_)
#define AFX_MFCCLIENTDLG_H__38925FE6_21A6_11D3_A6B3_0080AD712109__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




extern "C" CLSID CLSID_SDWMediator;

#include "..\\mediator\\mediator.h"





/////////////////////////////////////////////////////////////////////////////
// CMFCClientDlg dialog

class CMFCClientDlg : public CDialog
{
// Construction
public:
	CMFCClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMFCClientDlg)
	enum { IDD = IDD_MFCCLIENT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMFCClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStop();
	afx_msg void OnStart();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ISDWMediator * m_pMed;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCCLIENTDLG_H__38925FE6_21A6_11D3_A6B3_0080AD712109__INCLUDED_)
