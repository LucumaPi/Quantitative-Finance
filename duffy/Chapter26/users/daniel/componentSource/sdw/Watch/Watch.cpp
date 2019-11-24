///////////////////////////////////////////////////////////
//	Watch.cpp
// 
//	HvE
//	6-5-99

#include "Watch.h"
#include "..\\registry.h"
#include "..\\controlcentre\\controlcentre.h"
#include "..\\panel\\panel.h"

#include <iostream>

using std::cout;
using std::endl;

extern "C" CLSID CLSID_SDWControlCentre;
extern "C" CLSID CLSID_SDWPanel;
extern "C" CLSID CLSID_SDWWatch;



///////////////////////////////////////////////////////////
//
//	Global stuff
//
// 

static HMODULE g_hModule = NULL;	// DLL Module Handle
static long g_cComponents = 0;		// Active component counter
static long g_cServerLocks = 0;		// Lock Counter

// Friendly name of Component
const char g_szFriendlyName[]	=	"SDW Watch component";

// Version indepedend progID
const char g_szVerIndProgID[]	=	"SDW.Watch";

// ProgID
const char g_szProgID[]		=	"SDW.Watch.1";


///////////////////////////////////////////////////////////
//
//	Class definition
//
// 

// This class is the Watch component. It is implemented using
// the examples from the Fundamental COM Course

class CWatch	:	public IUnknown
{
private :
	// A nested class to represent the ISDWWatch Interface
	class SDWWatch	:	public ISDWWatch
	{
	public:
		CWatch * m_pParent;

		// IUnknown Methods
		HRESULT __stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG	__stdcall AddRef();
		ULONG	__stdcall Release();

													
		// ISDWWatch members
		HRESULT __stdcall SDWIncrement_h();
		HRESULT __stdcall SDWIncrement_m();
		HRESULT __stdcall SDWTime(/*[in]*/ long hours, /*[in]*/ long minutes);
		HRESULT __stdcall SDWUnfreeze();
		HRESULT __stdcall SDWFreeze();

		HRESULT __stdcall SDWDisplay();
		HRESULT __stdcall SDWHours();
		HRESULT __stdcall SDWMinutes();

		//Time time() const;

	}	m_objSDWWatch; // The membervariable that holds the object

	class SDWConnector	:	public ISDWConnector
	{
	public:
		CWatch * m_pParent;

		// IUnknown Methods
		HRESULT __stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG	__stdcall AddRef();
		ULONG	__stdcall Release();

		// ISDWConnector members
		HRESULT	__stdcall SDWSetUpperConnection(IUnknown * pUnk );
		HRESULT	__stdcall SDWSetLowerConnection(IUnknown * pUnk );
		HRESULT	__stdcall SDWKillConnection();
	}	m_objSDWConnector;	// The member that holds the object;

	long		m_nRefCnt;
	long		h;
	long		m;

	enum status {Display, SetH, SetM};
	status sta;
	
	ISDWControlCentre	*m_pCCen;
	ISDWPanel			*m_pPan;


public :
	// C'TOR
	CWatch();
	// D'TOR
	~CWatch();

	// IUnknown Implementation
	HRESULT	__stdcall QueryInterface(const IID & iid, void ** ppv);
	ULONG	__stdcall AddRef();
	ULONG	__stdcall Release();

	// Friend classes
	friend class SDWWatch;
	friend class SDWConnector;
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

CWatch::CWatch()	:	m_nRefCnt(0)
{
	// reference count for DLL usage
	InterlockedIncrement(&g_cComponents);

	// initialize parent variables
	m_objSDWWatch.m_pParent = this;
	m_objSDWConnector.m_pParent = this;

	h = 0;
	m = 0;

	m_pCCen = NULL;
	m_pPan = NULL;
}

CWatch::~CWatch()
{
	InterlockedDecrement(&g_cComponents);
}

// IUnknown Implementation
HRESULT	__stdcall CWatch::QueryInterface(const IID & iid, void ** ppv)
{

	HRESULT hr = S_OK;;

	if ( iid == IID_IUnknown )
	{
		*ppv = this;
	}
	else
		if ( iid == IID_ISDWWatch )
		{
			*ppv = &m_objSDWWatch;
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

		return hr;
}


ULONG	__stdcall CWatch::AddRef()
{
	return InterlockedIncrement(&m_nRefCnt);
}

ULONG	__stdcall CWatch::Release()
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
//	Now it's time to implement the innerclass SDWWatch
//
// 

HRESULT	__stdcall CWatch::SDWWatch::SDWIncrement_h()
{
	
	m_pParent->h++;
	if (m_pParent->h == 24)
	{
		m_pParent->h = 0;
	}

	// Notify new time
	if ( m_pParent->m_pCCen != NULL )
	{
		m_pParent->m_pCCen->SDWUpdate(m_pParent->h, m_pParent->m);
	}
	else
		return E_FAIL;

	return S_OK;
}

HRESULT	__stdcall CWatch::SDWWatch::SDWIncrement_m()
{
	
	m_pParent->m++;
	if (m_pParent->m == 60)
	{
		m_pParent->m = 0;
		m_pParent->h++;
	}

	if (m_pParent->h == 24)
	{

		m_pParent->h = 0;
	}

	// Notify new time
	if ( m_pParent->m_pCCen != NULL )
	{
		m_pParent->m_pCCen->SDWUpdate(m_pParent->h, m_pParent->m);
	}
	else
		return E_FAIL;

	return S_OK;
}

HRESULT	__stdcall CWatch::SDWWatch::SDWTime(long hours, long minutes)
{
	
	m_pParent->h = hours;
	m_pParent->m = minutes;

	if (m_pParent->h == 24)
	{

		m_pParent->h = 0;
	}

	if (m_pParent->m == 60)
	{
		m_pParent->m = 0;
		m_pParent->h++;
	}

	// Notify
	if ( m_pParent->m_pCCen != NULL )
	{
		m_pParent->m_pCCen->SDWUpdate(m_pParent->h, m_pParent->m);
	}
	else
		return E_FAIL;

	return S_OK;
}

HRESULT	__stdcall CWatch::SDWWatch::SDWUnfreeze()
{

	if ( m_pParent->m_pCCen )
	{
		m_pParent->m_pCCen->SDWUpdate (m_pParent->h, m_pParent->m);
		
		m_pParent->m_pCCen->SDWAccept();
	}
	else
		return E_FAIL;

	return S_OK;
}

HRESULT	__stdcall CWatch::SDWWatch::SDWFreeze()
{
	if ( m_pParent->m_pCCen != NULL )
		m_pParent->m_pCCen->SDWNoaccept();
	else
		return E_FAIL;
	return S_OK;
}

HRESULT __stdcall CWatch::SDWWatch::SDWDisplay()
{
	
	m_pParent->sta = Display;	
	return S_OK;
}

HRESULT __stdcall CWatch::SDWWatch::SDWHours()
{
	m_pParent->sta = SetH;
	return S_OK;
}

HRESULT __stdcall CWatch::SDWWatch::SDWMinutes()
{
	m_pParent->sta = SetH;

	return S_OK;
}

/*	Werd nergens voor gebruikt zover ik kon zien
Time Watch::time() const
{
 
	return Time(h, m);
}
*/

HRESULT	__stdcall CWatch::SDWWatch::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CWatch::SDWWatch::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CWatch::SDWWatch::Release()
{
	return m_pParent->Release();
}


///////////////////////////////////////////////////////////
//
//	The SDWConnection implementation
//
// 

HRESULT __stdcall CWatch::SDWConnector::SDWSetLowerConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWPanel, (void **) &m_pParent->m_pPan);
	
	return hr;
}

HRESULT __stdcall CWatch::SDWConnector::SDWSetUpperConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWControlCentre, (void**) &m_pParent->m_pCCen);
	
	return hr;
}

HRESULT __stdcall CWatch::SDWConnector::SDWKillConnection()
{
	HRESULT hr = S_OK;

	// is there a connecntion to the Panel
	if ( m_pParent->m_pPan )
	{
		ISDWConnector * pCon = NULL;
		
		// Query for the Connector Interface
		hr = m_pParent->m_pPan->QueryInterface(IID_ISDWConnector, (void **) &pCon );
		
		if (FAILED(hr))
			return E_FAIL;

		// Kill the connection of the Panel
		hr = pCon->SDWKillConnection();

		// release the Connector interface
		pCon->Release();

		if (FAILED(hr))
			return E_FAIL;

		// release the Panel interfacepointer
		m_pParent->m_pPan->Release();
	}

	// release the ControlCentre interface
	if ( m_pParent->m_pCCen ) 
		m_pParent->m_pCCen->Release();

	return hr;
}



HRESULT	__stdcall CWatch::SDWConnector::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CWatch::SDWConnector::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CWatch::SDWConnector::Release()
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

	CWatch * pWat = new CWatch;

	if ( pWat == NULL )
	{
		return E_OUTOFMEMORY;
	}

	HRESULT hr = pWat->QueryInterface(iid, ppv);

	if ( FAILED(hr) )
		delete pWat;

	
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
	if (clsid != CLSID_SDWWatch)
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
							CLSID_SDWWatch, 
							g_szFriendlyName,
							g_szVerIndProgID,
							g_szProgID	);
}

STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_SDWWatch,
							g_szVerIndProgID,
							g_szProgID	);
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void * lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		g_hModule = static_cast<HMODULE> (hModule);

	return true;
}













