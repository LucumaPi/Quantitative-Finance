///////////////////////////////////////////////////////////
//	Router.cpp
//
//	HvE	
//	6-5-99


#include "Router.h"
#include "..\\registry.h"
#include "..\\interface\\interface.h"
#include "..\\display\\display.h"


#include <iostream>

using std::cout;
using std::endl;

extern "C" CLSID CLSID_SDWInterface;
extern "C" CLSID CLSID_SDWDisplay;
extern "C" CLSID CLSID_SDWRouter;


///////////////////////////////////////////////////////////
//
//	Global stuff
//
// 

static HMODULE g_hModule = NULL;	// DLL Module Handle
static long g_cComponents = 0;		// Active component counter
static long g_cServerLocks = 0;		// Lock Counter

// Friendly name of Component
const char g_szFriendlyName[]	=	"SDW Router component";

// Version indepedend progID
const char g_szVerIndProgID[]	=	"SDW.Router";

// ProgID
const char g_szProgID[]		=	"SDW.Router.1";


///////////////////////////////////////////////////////////
//
//	Class definition
//
// 

// This class is the Router component. It is implemented using
// the examples from the Fundamental COM Course

class CRouter	:	public IUnknown
{
private :
	// A nested class to represent the ISDWRouter Interface
	class SDWRouter	:	public ISDWRouter
	{
	public:
		CRouter * m_pParent;

		// IUnknown Methods
		HRESULT __stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG	__stdcall AddRef();
		ULONG	__stdcall Release();

													
		// ISDWRouter members
		HRESULT	__stdcall SDWInitialise();
		HRESULT	__stdcall SDWNotify(/*[in]*/ long h , /*[in]*/ long m);

	}	m_objSDWRouter; // The membervariable that holds the object

	class SDWConnector	:	public ISDWConnector
	{
	public:
		CRouter * m_pParent;

		// IUnknown Methods
		HRESULT __stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG	__stdcall AddRef();
		ULONG	__stdcall Release();

		// ISDWConnector members
		HRESULT	__stdcall SDWSetUpperConnection(IUnknown * pUnk );
		HRESULT	__stdcall SDWSetLowerConnection(IUnknown * pUnk );
		HRESULT	__stdcall SDWKillConnection();
	}	m_objSDWConnector;	// The member that holds the object;

	// Datamembers
	long			m_nRefCnt;
	ISDWInterface	*m_pInt;
	ISDWDisplay		*m_pDisp;


public :
	// C'TOR
	CRouter();
	// D'TOR
	~CRouter();

	// IUnknown Implementation
	HRESULT	__stdcall QueryInterface(const IID & iid, void ** ppv);
	ULONG	__stdcall AddRef();
	ULONG	__stdcall Release();

	// Friend classes
	friend class SDWRouter;
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

CRouter::CRouter()	:	m_nRefCnt(0)
{

	// reference count for DLL usage
	InterlockedIncrement(&g_cComponents);

	// initialize parent variables
	m_objSDWRouter.m_pParent = this;
	m_objSDWConnector.m_pParent = this;

	m_pDisp = NULL;
	m_pInt = NULL;

}

CRouter::~CRouter()
{
	InterlockedDecrement(&g_cComponents);
}

// IUnknown Implementation
HRESULT	__stdcall CRouter::QueryInterface(const IID & iid, void ** ppv)
{

	HRESULT hr = S_OK;

	if ( iid == IID_IUnknown )
	{
		*ppv = this;
	}
	else
		if ( iid == IID_ISDWRouter )
		{
			*ppv = &m_objSDWRouter;
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

	IUnknown * pUnk = static_cast <IUnknown *> (*ppv);
	pUnk->AddRef();	// reference counting

	return hr;
}

ULONG	__stdcall CRouter::AddRef()
{
	return InterlockedIncrement(&m_nRefCnt);
}

ULONG	__stdcall CRouter::Release()
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
//	Now it's time to implement the innerclass SDWRouter
//
// 

HRESULT	__stdcall CRouter::SDWRouter::SDWInitialise()
{
	return S_OK;
}

HRESULT	__stdcall CRouter::SDWRouter::SDWNotify(long h, long m)
{
	
	if ( m_pParent->m_pDisp != NULL )
	{
		m_pParent->m_pDisp->SDWDisplayTime(h, m);
		return S_OK;
	}
	else 
		return E_FAIL;
}


HRESULT	__stdcall CRouter::SDWRouter::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CRouter::SDWRouter::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CRouter::SDWRouter::Release()
{
	return m_pParent->Release();
}


///////////////////////////////////////////////////////////
//
//	The SDWConnection implementation
//
// 

HRESULT __stdcall CRouter::SDWConnector::SDWSetLowerConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWDisplay, (void**) &m_pParent->m_pDisp );
	
	return hr;
}

HRESULT __stdcall CRouter::SDWConnector::SDWSetUpperConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWInterface, (void **) &m_pParent->m_pInt );
	return hr;
}

HRESULT __stdcall CRouter::SDWConnector::SDWKillConnection()
{
	HRESULT hr = S_OK;

	// is there a connecntion to the Display
	if ( m_pParent->m_pDisp )
	{
		ISDWConnector * pCon = NULL;
		
		// Query for the Connector Interface
		hr = m_pParent->m_pDisp->QueryInterface(IID_ISDWConnector, (void **) &pCon );
		
		if (FAILED(hr))
			return E_FAIL;

		// Kill the connection of the Display
		hr = pCon->SDWKillConnection();

		// release the Connector interface
		pCon->Release();

		if (FAILED(hr))
			return E_FAIL;

		// release the Display interfacepointer
		m_pParent->m_pDisp->Release();
	}

	// release the Interface interface
	if ( m_pParent->m_pInt ) 
		m_pParent->m_pInt->Release();

	return hr;
}

HRESULT	__stdcall CRouter::SDWConnector::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CRouter::SDWConnector::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CRouter::SDWConnector::Release()
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

	CRouter * pRouter = new CRouter;

	if ( pRouter == NULL )
	{
		return E_OUTOFMEMORY;
	}

	HRESULT hr = pRouter->QueryInterface(iid, ppv);

	if ( FAILED(hr) )
		delete pRouter;

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
	if (clsid != CLSID_SDWRouter)
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
							CLSID_SDWRouter, 
							g_szFriendlyName,
							g_szVerIndProgID,
							g_szProgID	);
}

STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_SDWRouter,
							g_szVerIndProgID,
							g_szProgID	);
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void * lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		g_hModule = static_cast<HMODULE> (hModule);

	return true;
}
