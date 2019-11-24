///////////////////////////////////////////////////////////
//	Panel.cpp
//
//	HvE
//	6-5-99

#include "Panel.h"
#include "..\\registry.h"
#include "..\\Watch\\Watch.h"

#include <iostream>
#include <ctime>

using namespace std;

///////////////////////////////////////////////////////////
//
//	Global stuff
//
// 
extern "C" CLSID CLSID_SDWWatch;
extern "C" CLSID CLSID_SDWPanel;

static HMODULE g_hModule = NULL;	// DLL Module Handle
static long g_cComponents = 0;		// Active component counter
static long g_cServerLocks = 0;		// Lock Counter

// Friendly name of Component
const char g_szFriendlyName[]	=	"SDW Panel component";

// Version indepedend progID
const char g_szVerIndProgID[]	=	"SDW.Panel";

// ProgID
const char g_szProgID[]		=	"SDW.Panel.1";

// The window procedure for the PanelWindow;
LRESULT CALLBACK PanelWndProc (HWND, UINT, WPARAM, LPARAM );

typedef HRESULT (*PressFunc) (void);

class CPanel	:	public IUnknown
{
private :
	// A nested class to represent the ISDWPanel Interface
	class SDWPanel	:	public ISDWPanel
	{
	public:
		CPanel * m_pParent;

		// IUnknown Methods
		HRESULT	__stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG		__stdcall AddRef();
		ULONG		__stdcall Release();

												
		// ISDWPanel members
		HRESULT	__stdcall SDWA();
		HRESULT	__stdcall SDWB();
		HRESULT	__stdcall SDWState(/*[out]*/ unsigned char * state);

	}	m_objSDWPanel; // The membervariable that holds the object

	class SDWConnector	:	public ISDWConnector
	{
	public:
		CPanel * m_pParent;

		// IUnknown Methods
		HRESULT	__stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG		__stdcall AddRef();
		ULONG		__stdcall Release();

		// ISDWConnector members
		HRESULT	__stdcall SDWSetUpperConnection(IUnknown * pUnk );
		HRESULT	__stdcall SDWSetLowerConnection(IUnknown * pUnk );
		HRESULT	__stdcall SDWKillConnection();
	}	m_objSDWConnector;	// The member that holds the object;
	
	long m_nRefCnt;
	long m_nSta;	//	3 moodes
						//	Setup (start transactions)
						//	Carry out tasks
						//	Commit Transactions

	ISDWWatch * m_pWatch;

	void CreatePanelWindow();

public :
	// C'TOR
	CPanel();
	// D'TOR
	~CPanel();

	// IUnknown Implementation
	HRESULT	__stdcall QueryInterface(const IID & iid, void ** ppv);
	ULONG	__stdcall AddRef();
	ULONG	__stdcall Release();

	// Friend classes
	friend class SDWPanel;
	friend class SDWConnector;
	static SDWPanel * m_sObj;
};



class CFactory : public IUnknown
{
private:
	long m_nRefCnt;

public:
	// C'TOR
	CFactory();
	// D'TOR
	~CFactory();

	// IUnknown Interface
	HRESULT	__stdcall QueryInterface(const IID & iid, void ** ppv);
	ULONG	__stdcall AddRef();
	ULONG	__stdcall Release();

	// Derived Class for the ICalssFactory interface
	class Factory	:	public IClassFactory
	{
	public:
		CFactory * m_pParent;

		// IUnknown interface
		HRESULT	__stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG	__stdcall AddRef();
		ULONG	__stdcall Release();

		// IClassFactory Interface
		HRESULT	__stdcall CreateInstance(	IUnknown *pUnkOuter,
														const IID & iid,
														void ** ppv	);
		HRESULT	__stdcall LockServer	(	BOOL bLock	);
	
	}	m_objFactory;
};

///////////////////////////////////////////////////////////
//
//	Now the outer class
//
// 

// this is a pointer to the 
class CPanel::SDWPanel *  CPanel::m_sObj;

CPanel::CPanel()	:	m_nRefCnt(0)
{
	// reference count for DLL usage
	InterlockedIncrement(&g_cComponents);

	// initialize parent variables
	m_objSDWPanel.m_pParent = this;
	m_objSDWConnector.m_pParent = this;

	m_nSta = 0;

	m_pWatch = NULL;

	CreatePanelWindow();

	
	m_sObj = &(this->m_objSDWPanel);
}

CPanel::~CPanel()
{
	InterlockedDecrement(&g_cComponents);
}



void CPanel::CreatePanelWindow()
{
	static char szAppName[] = "PanelWindow";
   HWND        hwnd;
 
   WNDCLASSEX  wndclass;

	HANDLE hInstance = GetModuleHandle(NULL);

	wndclass.cbSize        = sizeof (wndclass);
   wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;
   wndclass.lpfnWndProc   = PanelWndProc;
   wndclass.cbClsExtra    = 0;
   wndclass.cbWndExtra    = 0;
   wndclass.hInstance     = (HINSTANCE) hInstance;
   wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
   wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
   wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
   wndclass.lpszMenuName  = NULL;
   wndclass.lpszClassName = szAppName;
	wndclass.hIconSm       = LoadIcon (NULL, IDI_APPLICATION);

   RegisterClassEx (&wndclass);

	// The best solution for the size and position would
	// be using GetSystemMetrics() ofcourse, but for now
	//  0,0,50,50 is nice enough
   hwnd = CreateWindow (	szAppName,
									"PanelWindow",
									WS_OVERLAPPEDWINDOW,
									110,//CW_USEDEFAULT,
									0,//CW_USEDEFAULT,
									185,//CW_USEDEFAULT,
									115,//CW_USEDEFAULT,
									NULL,
									NULL,
									(HINSTANCE)hInstance,
									NULL	);


   ShowWindow (hwnd, SW_SHOW);
   UpdateWindow (hwnd);
}

// IUnknown Implementation
HRESULT	__stdcall CPanel::QueryInterface(const IID & iid, void ** ppv)
{
	if ( iid == IID_IUnknown )
	{
		*ppv = this;
	}
	else
		if ( iid == IID_ISDWPanel )
		{
			*ppv = &m_objSDWPanel;
		}
		else
		{
			if ( iid == IID_ISDWConnector )
			{
				*ppv = &m_objSDWConnector;
			}
			else
				// Oeps, there is no requested interface
				{
					*ppv = NULL;
					return E_NOINTERFACE;
				}
		}
		IUnknown * pUnk = (IUnknown*) *ppv;
		// Adding a referencecount for this interface
		pUnk->AddRef();

		return S_OK;
}

ULONG	__stdcall CPanel::AddRef()
{
	return InterlockedIncrement(&m_nRefCnt);
}

ULONG	__stdcall CPanel::Release()
{
	if ( InterlockedDecrement(&m_nRefCnt) == 0 )
	{
		delete this;
		return 0;
	}

	return m_nRefCnt;
}

///////////////////////////////////////////////////////////
//
//	Now it's time to implement the innerclass SDWPanel
//
// 

HRESULT	__stdcall CPanel::SDWPanel::SDWA()
{
	if ( m_pParent->m_pWatch != NULL )
	{
		switch (m_pParent->m_nSta)
		{
			case 0:
				{ 
					m_pParent->m_nSta = 1;
					m_pParent->m_pWatch->SDWFreeze();
					break;
				}	
			
			case 1:
				{
					m_pParent->m_nSta = 2;
					break;
				}
			
			case 2:
				{ // Scenario R2.3, inform Watch that we are finished
					m_pParent->m_nSta = 0;
					m_pParent->m_pWatch->SDWUnfreeze();
				}
		}
	}
	else
		return E_FAIL;

	return S_OK;
}


HRESULT	__stdcall CPanel::SDWPanel::SDWB()
{

	if ( m_pParent->m_pWatch != NULL )
	{

		if (m_pParent->m_nSta == 0)
		{
			cout << "************ Error, ring Houston! ******************" << endl;
			return E_FAIL;
		}

		if (m_pParent->m_nSta == 1)
		{
			
			m_pParent->m_pWatch->SDWIncrement_h();
		}

		if (m_pParent->m_nSta == 2)
		{
			// cout << "S2.1 setting minutes to Watch\n";
			m_pParent->m_pWatch->SDWIncrement_m();
		}
	}

	return S_OK;
}

HRESULT __stdcall CPanel::SDWPanel::SDWState(unsigned char * state)
{
	state = reinterpret_cast<unsigned char *> ("First");

	if (m_pParent->m_nSta == 1)
		state = reinterpret_cast<unsigned char *> ("second");
	if (m_pParent->m_nSta == 2)
		state = reinterpret_cast<unsigned char *> ("last");

	return S_OK;
}


HRESULT	__stdcall CPanel::SDWPanel::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CPanel::SDWPanel::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CPanel::SDWPanel::Release()
{
	return m_pParent->Release();
}

///////////////////////////////////////////////////////////
//
//	The SDWConnection implementation
//
// 

HRESULT __stdcall CPanel::SDWConnector::SDWSetLowerConnection(IUnknown * pUnk)
{
	return E_FAIL;
}

HRESULT __stdcall CPanel::SDWConnector::SDWSetUpperConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;
	
	if (pUnk != NULL)
		hr = pUnk->QueryInterface( IID_ISDWWatch, (void **) & m_pParent->m_pWatch);

	return hr;
}

HRESULT __stdcall CPanel::SDWConnector::SDWKillConnection()
{
	if ( m_pParent->m_pWatch )
	{
		m_pParent->m_pWatch->Release();
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT	__stdcall CPanel::SDWConnector::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CPanel::SDWConnector::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CPanel::SDWConnector::Release()
{
	return m_pParent->Release();
}

///////////////////////////////////////////////////////////
//
//	The implementation of the ClassFactory
//
// 

CFactory::CFactory()	:	m_nRefCnt(0)
{
	m_objFactory.m_pParent = this;
}

CFactory::~CFactory()
{
	InterlockedDecrement(&m_nRefCnt);
}

HRESULT	__stdcall CFactory::QueryInterface(const IID & iid, void ** ppv)
{

	if ( iid == IID_IUnknown )
	{
		*ppv = this;
	}
	else
		if ( iid == IID_IClassFactory )
		{
			*ppv = &m_objFactory;
		}
		else
		{
			// Oops, the requested interface is not present
			*ppv = NULL;
			return E_NOINTERFACE;
		}

	IUnknown * pUnk = static_cast <IUnknown *> (*ppv);
	pUnk->AddRef();	// reference counting

	return S_OK;
}

ULONG	__stdcall CFactory::AddRef()
{

	return InterlockedIncrement(&m_nRefCnt);
}

ULONG	__stdcall CFactory::Release()
{
	if ( InterlockedDecrement(&m_nRefCnt) == 0 ) 
	{
		delete this;
		return 0;
	}
	return m_nRefCnt;
}

///////////////////////////////////////////////////////////
//
//	The implementation of the nested factory class
//
// 

HRESULT	__stdcall CFactory::Factory::QueryInterface(const IID & iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	 __stdcall CFactory::Factory::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CFactory::Factory::Release()
{
	return m_pParent->Release();
}

HRESULT	__stdcall CFactory::Factory::CreateInstance(IUnknown * pUnkOuter,
													const IID &iid,
													void ** ppv	)
{
	if ( pUnkOuter != NULL )
	{
		// No aggrgation supported
		return CLASS_E_NOAGGREGATION;
	}

	CPanel * pPan = new CPanel;

	if ( pPan == NULL )
	{
		return E_OUTOFMEMORY;
	}

	HRESULT hr = pPan->QueryInterface(iid, ppv);

	if ( FAILED(hr) )
		delete pPan;

	return hr;
}

HRESULT	__stdcall CFactory::Factory::LockServer( BOOL bLock )
{
	if ( bLock )
	{
		InterlockedIncrement(&g_cServerLocks);
	}
	else
	{
		InterlockedDecrement(&g_cServerLocks);
	}

	return S_OK;
}

///////////////////////////////////////////////////////////
//
//	Export functions
//
// 

STDAPI DllCanUnloadNow()
{
	if ( (g_cComponents == NULL) && (g_cServerLocks == 0) )
	{
		return S_OK;
	}
	else
	{
		return S_FALSE;
	}
}

STDAPI DllGetClassObject(const CLSID &clsid, const IID &iid, void ** ppv)
{
	// Check if the component can be created
	if (clsid != CLSID_SDWPanel)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}

	CFactory *pFact = new CFactory;

	if ( pFact == NULL )
	{
		return E_OUTOFMEMORY;
	}

	HRESULT hr = pFact->QueryInterface(iid, ppv);
	if (FAILED(hr))
	{
		delete pFact;
	}

	return hr;
}

STDAPI DllRegisterServer()
{
	return RegisterServer(	g_hModule,
							CLSID_SDWPanel, 
							g_szFriendlyName,
							g_szVerIndProgID,
							g_szProgID	);
}

STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_SDWPanel,
							g_szVerIndProgID,
							g_szProgID	);
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void * lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		g_hModule = static_cast<HMODULE> (hModule);

	return true;
}

LRESULT CALLBACK PanelWndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	static HWND		hwndA, hwndB;
	static RECT		rect ;
	static int		cxChar, cyChar ;
	HDC				hdc ;
	PAINTSTRUCT		ps ;
	TEXTMETRIC		tm ;
	HRESULT			hr = S_OK;


	
	switch (iMsg)
	{
	case WM_CREATE :
	   hdc = GetDC (hwnd);
	   SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));
	   GetTextMetrics (hdc, &tm);
	   cxChar = tm.tmAveCharWidth;
	   cyChar = tm.tmHeight + tm.tmExternalLeading;
	   ReleaseDC (hwnd, hdc);

		hwndA = CreateWindow (	"button",
										"BUTTON A",
										WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
										cxChar,
										cyChar * (1 + 2 * 0),
										20 * cxChar, 7 * cyChar / 4,
										hwnd,
										(HMENU) 0,
										((LPCREATESTRUCT) lParam) -> hInstance,
										NULL	);

		hwndB = CreateWindow (	"button",
										"BUTTON B",
										WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
										cxChar,
										cyChar * (1 + 2 * 1),
										20 * cxChar, 7 * cyChar / 4,
										hwnd,
										(HMENU) 1,
										((LPCREATESTRUCT) lParam) -> hInstance,
										NULL);		

		return 0;

	case WM_SIZE :
	   rect.left   = 24 * cxChar;
	   rect.top    =  2 * cyChar;
	   rect.right  = LOWORD (lParam);
	   rect.bottom = HIWORD (lParam);
	   return 0 ;		
	case WM_PAINT :
	   InvalidateRect (hwnd, &rect, TRUE);

	   hdc = BeginPaint (hwnd, &ps);

		SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));
	   SetBkMode (hdc, TRANSPARENT);

		EndPaint (hwnd, &ps);
	   return 0 ;

	case WM_DRAWITEM :
	case WM_COMMAND :


		if (wParam == 0)
		{
			CPanel::m_sObj->SDWA();
		}// Here SDWA must be called somehow
		else
		{
			CPanel::m_sObj->SDWB();
		}	// Here SDWB must be called somehow
	   break ;

	case WM_DESTROY :
		PostQuitMessage (0);
	   return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam , lParam);
}










