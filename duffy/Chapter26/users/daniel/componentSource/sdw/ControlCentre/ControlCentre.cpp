///////////////////////////////////////////////////////////
//
//	ControlCentre.cpp
//
//  HvE 
//  06-05-99

#include "ControlCentre.h"
#include "..\\registry.h"
#include "..\\controlcentrecontainer\\controlcentrecontainer.h"
#include "..\\watch\\watch.h"


extern "C" CLSID CLSID_SDWControlCentreContainer;
extern "C" CLSID CLSID_SDWControlCentre;
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
const char g_szFriendlyName[]	=	"SDW ControlCentre component";

// Version indepedend progID
const char g_szVerIndProgID[]	=	"SDW.ControlCentre";

// ProgID
const char g_szProgID[]		=	"SDW.ControlCentre.1";


///////////////////////////////////////////////////////////
//
//	Class definition
//
// 

// This class is the ControlCentre component. It is implemented using
// the examples from the Fundamental COM Course

class CControlCentre	:	public IUnknown
{
private :
	// A nested class to represent the ISDWControlCentre Interface
	class SDWControlCentre	:	public ISDWControlCentre
	{
	public:
		CControlCentre * m_pParent;

		// IUnknown Methods
		HRESULT __stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG	__stdcall AddRef();
		ULONG	__stdcall Release();
													
		// ISDWControlCentre members
		HRESULT __stdcall SDWInitialise(/*[in]*/long h,/*[in]*/ long m);
		HRESULT __stdcall SDWAccept();
		HRESULT __stdcall SDWNoaccept();
		HRESULT __stdcall SDWPush();
		HRESULT __stdcall SDWUpdate(/*[in]*/long h,/*[in]*/ long m);
		HRESULT __stdcall SDWState(/*[in]*/ long * state);

	}	m_objSDWControlCentre; // The membervariable that holds the object

	class SDWConnector	:	public ISDWConnector
	{
	public:
		CControlCentre * m_pParent;

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
	long m_nRefCnt;
	BOOL m_fStat;

	
	ISDWControlCentreContainer		*m_pConCenCon;
	ISDWWatch							*m_pWatch;

public :
	// C'TOR
	CControlCentre();
	// D'TOR
	~CControlCentre();

	// IUnknown Implementation
	HRESULT	__stdcall QueryInterface(const IID & iid, void ** ppv);
	ULONG	__stdcall AddRef();
	ULONG	__stdcall Release();

	// Friend classes
	friend class SDWControlCentre;
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

CControlCentre::CControlCentre()	:	m_nRefCnt(0)
{

	m_fStat = false;

	// reference count for DLL usage
	InterlockedIncrement(&g_cComponents);

	// initialize parent variables
	m_objSDWControlCentre.m_pParent = this;
	m_objSDWConnector.m_pParent = this;

	m_pConCenCon = NULL;
	m_pWatch = NULL;

}

CControlCentre::~CControlCentre()
{
	InterlockedDecrement(&g_cComponents);
}

// IUnknown Implementation
HRESULT	__stdcall CControlCentre::QueryInterface(const IID & iid, void ** ppv)
{
	
	HRESULT hr = S_OK;

	// Are we asked for a known interface ?
	if ( iid == IID_IUnknown )
	{
		*ppv = this;
	}
	else
		if ( iid == IID_ISDWControlCentre )
		{
			*ppv = &m_objSDWControlCentre;
		}
		else
			if ( iid == IID_ISDWConnector )
			{
				*ppv = &m_objSDWConnector;
			}
			else
			// Oeps, the requested interface is not here
			{
				*ppv = NULL;
				return E_NOINTERFACE;
			}
	IUnknown * pUnk = (IUnknown*) *ppv;
	// Adding a referencecount for this interface
	pUnk->AddRef();

	return hr;
}

ULONG	__stdcall CControlCentre::AddRef()
{
	return InterlockedIncrement(&m_nRefCnt);
}

ULONG	__stdcall CControlCentre::Release()
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
//	Now it's time to implement the innerclass SDWControlCentre
//
// 

HRESULT	__stdcall CControlCentre::SDWControlCentre::SDWInitialise(long h, long m)
{

	if ( m_pParent->m_pWatch != NULL )
	{
		m_pParent->m_pWatch->SDWTime(h, m);
	}
	else
		return E_FAIL;

	return S_OK;
}

HRESULT	__stdcall CControlCentre::SDWControlCentre::SDWAccept()
{

	if ( m_pParent->m_pConCenCon != NULL )
	{
		m_pParent->m_pConCenCon->SDWEnable();
	}
	else
		return E_FAIL;

	return S_OK;
}

HRESULT	__stdcall CControlCentre::SDWControlCentre::SDWNoaccept()
{

	if ( m_pParent->m_pConCenCon != NULL )
	{
		m_pParent->m_pConCenCon->SDWDisable();
	}
	else
		return E_FAIL;
	
	return S_OK;
}


HRESULT	__stdcall CControlCentre::SDWControlCentre::SDWPush()
{

	if ( m_pParent->m_pWatch != NULL )
	{
		m_pParent->m_pWatch->SDWIncrement_m();
	}
	else
		return E_FAIL;
	
	return S_OK;
}

HRESULT __stdcall CControlCentre::SDWControlCentre::SDWUpdate(long h, long m)
{

	if ( m_pParent->m_pConCenCon != NULL )
	{
		m_pParent->m_pConCenCon->SDWNotify(h , m);
	}
	else 
		return E_FAIL;
	
	return S_OK;
}

HRESULT	__stdcall CControlCentre::SDWControlCentre::SDWState(long * state)
{
	
	*state = m_pParent->m_fStat;
	
	return S_OK;
}


HRESULT	__stdcall CControlCentre::SDWControlCentre::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CControlCentre::SDWControlCentre::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CControlCentre::SDWControlCentre::Release()
{
	return m_pParent->Release();
}


///////////////////////////////////////////////////////////
//
//	The SDWConnection implementation
//
// 

HRESULT __stdcall CControlCentre::SDWConnector::SDWSetLowerConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWWatch, (void **) &m_pParent->m_pWatch );

	return hr;
}

HRESULT __stdcall CControlCentre::SDWConnector::SDWSetUpperConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWControlCentreContainer, (void **) &m_pParent->m_pConCenCon);
	
	return hr;
}

HRESULT __stdcall CControlCentre::SDWConnector::SDWKillConnection()
{
	HRESULT hr = S_OK;

	// is there a connecntion to the Watch
	if ( m_pParent->m_pWatch )
	{
		ISDWConnector * pCon = NULL;
		
		// Query for the Connector Interface
		hr = m_pParent->m_pWatch->QueryInterface(IID_ISDWConnector, (void **) &pCon );
		
		if (FAILED(hr))
			return E_FAIL;

		// Kill the connection of the Watch
		hr = pCon->SDWKillConnection();

		// release the Connector interface
		pCon->Release();

		if (FAILED(hr))
			return E_FAIL;

		// release the watch interfacepointer
		m_pParent->m_pWatch->Release();
	}

	// release the ControlCentreContainer interface
	if ( m_pParent->m_pConCenCon ) 
		m_pParent->m_pConCenCon->Release();

	return hr;
}



HRESULT	__stdcall CControlCentre::SDWConnector::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CControlCentre::SDWConnector::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CControlCentre::SDWConnector::Release()
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

	CControlCentre * pCCen = new CControlCentre;

	if ( pCCen == NULL )
	{
		return E_OUTOFMEMORY;
	}

	HRESULT hr = pCCen->QueryInterface(iid, ppv);

	if ( FAILED(hr) )
		delete pCCen;

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
	if (clsid != CLSID_SDWControlCentre)
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
							CLSID_SDWControlCentre, 
							g_szFriendlyName,
							g_szVerIndProgID,
							g_szProgID	);
}

STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_SDWControlCentre,
							g_szVerIndProgID,
							g_szProgID	);
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void * lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		g_hModule = static_cast<HMODULE> (hModule);

	return true;
}
