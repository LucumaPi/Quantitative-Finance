// MFCClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCClient.h"
#include "MFCClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCClientDlg dialog

CMFCClientDlg::CMFCClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMFCClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMFCClientDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMFCClientDlg, CDialog)
	//{{AFX_MSG_MAP(CMFCClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_WM_CLOSE()
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCClientDlg message handlers

BOOL CMFCClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	GetDlgItem(IDC_START)->EnableWindow(TRUE);	//	enable
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);	// disable
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCClientDlg::OnPaint() 
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
HCURSOR CMFCClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMFCClientDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	try
	{
			m_pMed->SDWShutdown();
			// Essantail, or else the mediator dll keeps alive forever
			m_pMed->Release();
			// So we can check the pointer later to see if it is valid
			m_pMed = NULL;
			
			GetDlgItem(IDC_START)->EnableWindow(TRUE);	// enable
			GetDlgItem(IDOK)->EnableWindow(TRUE);			// enable
			GetDlgItem(IDC_STOP)->EnableWindow(FALSE);	// disable
	}
	catch (...)
	{
		AfxMessageBox("Exception catched in OnStop");
	}
}

void CMFCClientDlg::OnStart() 
{
	// TODO: Add your control notification handler code here
	HRESULT hr = S_OK;

	GetDlgItem(IDC_STOP)->EnableWindow();			// enable
	GetDlgItem(IDC_START)->EnableWindow(FALSE);	// disable
	GetDlgItem(IDOK)->EnableWindow(FALSE);			// disable

	hr = CoCreateInstance(	CLSID_SDWMediator,
							NULL,
							CLSCTX_INPROC_SERVER,
							IID_ISDWMediator,
							(void **) &m_pMed	);

	if (FAILED(hr))
	{
		AfxMessageBox("Cannot create the mediator component");
		OnClose();
	}
	else
		m_pMed->SDWStartup();
}


void CMFCClientDlg::OnClose() 
{
	// First check if we must shutdown the system
	if ( m_pMed )
		m_pMed->SDWShutdown();

	CDialog::OnClose();
}

