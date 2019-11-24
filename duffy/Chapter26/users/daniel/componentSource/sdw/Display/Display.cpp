///////////////////////////////////////////////////////////
//	Display.cpp
//
//	HvE
//	6-5-99

#include "display.h"
#include "..\\registry.h"
#include "..\\router\\router.h"

#include <iostream>
#include <ctime>

using namespace std;

///////////////////////////////////////////////////////////
//
//	Global stuff
//
// 
extern "C" CLSID CLSID_SDWRouter;
extern "C" CLSID CLSID_SDWDisplay;

static HMODULE g_hModule = NULL;	// DLL Module Handle
static long g_cComponents = 0;		// Active component counter
static long g_cServerLocks = 0;		// Lock Counter

// Friendly name of Component
const char g_szFriendlyName[]	=	"SDW Display component";

// Version indepedend progID
const char g_szVerIndProgID[]	=	"SDW.Display";

// ProgID
const char g_szProgID[]		=	"SDW.Display.1";

// the windowprocedure witch catches the messages for the Dispwindow
LRESULT CALLBACK DispWndProc ( HWND, UINT, WPARAM, LPARAM );

///////////////////////////////////////////////////////////
//
//	The CDisplay class.
//
// 


class CDisplay	:	public IUnknown
{
private :
	// A nested class to represent the ISDWDisplay Interface
	class SDWDisplay	:	public ISDWDisplay
	{
	public:
		CDisplay * m_pParent;

		// IUnknown Methods
		HRESULT __stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG	__stdcall AddRef();
		ULONG	__stdcall Release();

													
		// ISDWDisplay members
		HRESULT	__stdcall SDWDisplayTime(/*[in]*/ long h, /*[in]*/ long m);

	}	m_objSDWDisplay; // The membervariable that holds the object

	class SDWConnector	:	public ISDWConnector
	{
	public:
		CDisplay * m_pParent;

		// IUnknown Methods
		HRESULT __stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG	__stdcall AddRef();
		ULONG	__stdcall Release();

		// ISDWConnector members
		HRESULT	__stdcall SDWSetUpperConnection(IUnknown * pUnk );
		HRESULT	__stdcall SDWSetLowerConnection(IUnknown * pUnk );
		HRESULT	__stdcall SDWKillConnection();
	}	m_objSDWConnector;	// The member that holds the object;
	
	long m_nRefCnt;
	ISDWRouter * m_pRouter;
	HWND		m_hwnd;
	long m_lHour;
	long m_lMinute;

	

	// Helperfunction to creta a window where we can display the time
	void CreateDispWindow();
	
public :
	// C'TOR
	CDisplay();
	// D'TOR
	~CDisplay();

	// IUnknown Implementation
	HRESULT	__stdcall QueryInterface(const IID & iid, void ** ppv);
	ULONG	__stdcall AddRef();
	ULONG	__stdcall Release();

	// Friend classes
	friend class SDWDisplay;
	friend class SDWConnector;
	static char szTime [10];
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

// The static class emeber to store the time.
char CDisplay::szTime [10];

CDisplay::CDisplay()	:	m_nRefCnt(0)
{
	// reference count for DLL usage
	InterlockedIncrement(&g_cComponents);

	// initialize parent variables
	m_objSDWDisplay.m_pParent = this;
	m_objSDWConnector.m_pParent = this;

	m_pRouter = NULL;

	// Now it's time to create the window
	CreateDispWindow();
}

CDisplay::~CDisplay()
{
	InterlockedDecrement(&g_cComponents);
}

void CDisplay::CreateDispWindow()
{
	static char szAppName [] = "The Simple Digital Watch";

	WNDCLASSEX	wndclass;

	HANDLE hInstance = GetModuleHandle(NULL);

	wndclass.cbSize			=	sizeof(wndclass);
	wndclass.style				=	CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE ;
	wndclass.lpfnWndProc		=	DispWndProc;
	wndclass.cbClsExtra		=	0;
	wndclass.cbWndExtra		=	0;
	wndclass.hInstance		=	(HINSTANCE) hInstance;
	wndclass.hIcon				=	LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor			=	LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground	=	(HBRUSH) GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName	=	NULL;
	wndclass.lpszClassName	=	szAppName;
	wndclass.hIconSm			=	LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	// The best solution for the size and position would
	// be using GetSystemMetrics() ofcourse, but for now
	//  0,0,50,50 is nice enough
	m_hwnd	=	CreateWindow (	szAppName,
										"SDW",
										WS_OVERLAPPEDWINDOW,
										0,//CW_USEDEFAULT,
										0,//CW_USEDEFAULT,
										50,//CW_USEDEFAULT,
										50,//CW_USEDEFAULT,
										NULL,
										NULL,
										(HINSTANCE) hInstance,
										NULL	);

	ShowWindow( m_hwnd, SW_SHOW );
	SetWindowPos( m_hwnd, HWND_TOPMOST, 0, 0, 50, 50, SWP_NOSIZE | SWP_NOMOVE );
	UpdateWindow( m_hwnd );
}

// IUnknown Implementation
HRESULT	__stdcall CDisplay::QueryInterface(const IID & iid, void ** ppv)
{
	if ( iid == IID_IUnknown )
	{
		*ppv = this;
	}
	else
		if ( iid == IID_ISDWDisplay )
		{
			*ppv = &m_objSDWDisplay;
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

ULONG	__stdcall CDisplay::AddRef()
{
	return InterlockedIncrement(&m_nRefCnt);
}

ULONG	__stdcall CDisplay::Release()
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
//	Now it's time to implement the innerclass SDWDisplay
//
// 

HRESULT	__stdcall CDisplay::SDWDisplay::SDWDisplayTime(long h, long m)
{
	// Take care of the right format	
	if ( h < 10 && m < 10 )
		sprintf (szTime, "0%d:0%d", h,m);
	else
		if ( h < 10 && m >= 10)
			sprintf (szTime, "0%d:%d", h,m);
		else
			if ( h >= 10 && m < 10 )
				sprintf (szTime, "%d:0%d", h,m);
			else
				sprintf (szTime, "%d:%d", h,m);

	

	// Now Invalidate the complete window
	// so we will get a repaint with the new time
	RECT rect;
	
	GetClientRect(m_pParent->m_hwnd, &rect);
	InvalidateRect(m_pParent->m_hwnd, &rect, true);

	return S_OK;
}

HRESULT	__stdcall CDisplay::SDWDisplay::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CDisplay::SDWDisplay::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CDisplay::SDWDisplay::Release()
{
	return m_pParent->Release();
}

///////////////////////////////////////////////////////////
//
//	The SDWConnection implementation
//
// 

HRESULT __stdcall CDisplay::SDWConnector::SDWSetLowerConnection(IUnknown * pUnk)
{
	return E_FAIL;
}

HRESULT __stdcall CDisplay::SDWConnector::SDWSetUpperConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWRouter, (void **) &m_pParent->m_pRouter );
	
	return hr;
}

HRESULT __stdcall CDisplay::SDWConnector::SDWKillConnection()
{
	if ( m_pParent->m_pRouter )
	{
		m_pParent->m_pRouter->Release();
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT	__stdcall CDisplay::SDWConnector::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CDisplay::SDWConnector::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CDisplay::SDWConnector::Release()
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

HRESULT	_stdcall CFactory::Factory::QueryInterface(const IID & iid, void ** ppv)
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

	CDisplay * pDisp = new CDisplay;

	if ( pDisp == NULL )
	{
		return E_OUTOFMEMORY;
	}

	HRESULT hr = pDisp->QueryInterface(iid, ppv);

	if ( FAILED(hr) )
		delete pDisp;

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
	if (clsid != CLSID_SDWDisplay)
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
							CLSID_SDWDisplay, 
							g_szFriendlyName,
							g_szVerIndProgID,
							g_szProgID	);
}

STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_SDWDisplay,
							g_szVerIndProgID,
							g_szProgID	);
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void * lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		g_hModule = static_cast<HMODULE> (hModule);

	return true;
}



LRESULT CALLBACK DispWndProc ( HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT	ps;
	RECT			rect;

	switch (iMsg)
	{
	case WM_PAINT :
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		DrawText(hdc, CDisplay::szTime, -1, &rect,
					DT_SINGLELINE | DT_CENTER | DT_VCENTER );

		EndPaint( hwnd, &ps);

		return 0;
	}
	return DefWindowProc( hwnd, iMsg, wParam, lParam );
}