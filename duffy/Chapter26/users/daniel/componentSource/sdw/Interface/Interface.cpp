///////////////////////////////////////////////////////////
//
//	Interface.cpp
//
//	HvE 06-05-99

#include "Interface.h"
#include "..\\InterfaceContainer\\InterfaceContainer.h"
#include "..\\Router\\Router.h"
#include "..\\registry.h"

#include <iostream>

using std::cout;
using std::endl;

extern "C" CLSID CLSID_SDWInterface;
extern "C" CLSID CLSID_SDWInterfaceContainer;
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
const char g_szFriendlyName[]	=	"SDW Interface component";

// Version indepedend progID
const char g_szVerIndProgID[]	=	"SDW.Interface";

// ProgID
const char g_szProgID[]		=	"SDW.Interface.1";


///////////////////////////////////////////////////////////
//
//	Class definition
//
// 

// This class is the Interface component. It is implemented using
// the examples from the Fundamental COM Course

class CInterface	:	public IUnknown
{
private :
	// A nested class to represent the ISDWInterface Interface
	class SDWInterface	:	public ISDWInterface
	{
	public:
		CInterface * m_pParent;

		// IUnknown Methods
		HRESULT __stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG	__stdcall AddRef();
		ULONG	__stdcall Release();
													
		// ISDWInterface members
		HRESULT	__stdcall SDWInitialise();
		HRESULT __stdcall SDWNotify(/*[in]*/ long h, /*[in]*/ long m);

	}	m_objSDWInterface; // The membervariable that holds the object

	class SDWConnector	:	public ISDWConnector
	{
	public:
		CInterface * m_pParent;

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

	ISDWRouter		*m_pRouter;
	ISDWInterfaceContainer	*m_pIntCon;

public :
	// C'TOR
	CInterface();
	// D'TOR
	~CInterface();

	// IUnknown Implementation
	HRESULT	__stdcall QueryInterface(const IID & iid, void ** ppv);
	ULONG	__stdcall AddRef();
	ULONG	__stdcall Release();

	// Friend classes
	friend class SDWInterface;
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

CInterface::CInterface()	:	m_nRefCnt(0)
{

	// reference count for DLL usage
	InterlockedIncrement(&g_cComponents);

	// initialize parent variables
	m_objSDWInterface.m_pParent = this;
	m_objSDWConnector.m_pParent = this;

	m_pRouter = NULL;
	m_pIntCon = NULL;
}

CInterface::~CInterface()
{
	InterlockedDecrement(&g_cComponents);
}

// IUnknown Implementation
HRESULT	__stdcall CInterface::QueryInterface(const IID & iid, void ** ppv)
{
	
	HRESULT hr = S_OK;
	// Are we asked for a known interface ?
	if ( iid == IID_IUnknown )
	{
		*ppv = this;
	}
	else
	{
		if ( iid == IID_ISDWInterface )
		{
			*ppv = &m_objSDWInterface;
		}
		else
		{
			if ( iid == IID_ISDWConnector )
			{
				*ppv = &m_objSDWConnector;
			}
			// Oeps, the requested interface is not here
			else
			{
				*ppv = NULL;
				return E_NOINTERFACE;
			}
		}
	}

	IUnknown * pUnk = (IUnknown*) *ppv;
	// Adding a referencecount for this interface
	pUnk->AddRef();
	
	return hr;
}


ULONG	__stdcall CInterface::AddRef()
{
	return InterlockedIncrement(&m_nRefCnt);
}

ULONG	__stdcall CInterface::Release()
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
//	Now it's time to implement the innerclass SDWInterface
//
// 

HRESULT	__stdcall CInterface::SDWInterface::SDWInitialise()
{
	if ( m_pParent->m_pRouter != NULL )
	{
		m_pParent->m_pRouter->SDWInitialise();
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT	__stdcall CInterface::SDWInterface::SDWNotify(long h, long m)
{
	if ( m_pParent->m_pRouter != NULL )
	{
		m_pParent->m_pRouter->SDWNotify(h, m);
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT	__stdcall CInterface::SDWInterface::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CInterface::SDWInterface::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CInterface::SDWInterface::Release()
{
	return m_pParent->Release();
}

///////////////////////////////////////////////////////////
//
//	The SDWConnection implementation
//
// 

HRESULT __stdcall CInterface::SDWConnector::SDWSetLowerConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWRouter, (void **) & m_pParent->m_pRouter );

	return hr;
}

HRESULT __stdcall CInterface::SDWConnector::SDWSetUpperConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWInterfaceContainer, (void**) &m_pParent->m_pIntCon);

	return hr;
}

HRESULT __stdcall CInterface::SDWConnector::SDWKillConnection()
{
	HRESULT hr = S_OK;

	// is there a connecntion to the Router
	if ( m_pParent->m_pRouter )
	{
		ISDWConnector * pCon = NULL;
		
		// Query for the Connector Interface
		hr = m_pParent->m_pRouter->QueryInterface(IID_ISDWConnector, (void **) &pCon );
		
		if (FAILED(hr))
			return E_FAIL;

		// Kill the connection of the Router
		hr = pCon->SDWKillConnection();

		// release the Connector interface
		pCon->Release();

		if (FAILED(hr))
			return E_FAIL;

		// release the Router interfacepointer
		m_pParent->m_pRouter->Release();
	}

	// release the InterfaceContainer interface
	if ( m_pParent->m_pIntCon ) 
		m_pParent->m_pIntCon->Release();

	return hr;
}


HRESULT	__stdcall CInterface::SDWConnector::QueryInterface(const IID &iid, void ** ppv)
{

	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CInterface::SDWConnector::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CInterface::SDWConnector::Release()
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

	CInterface * pInt = new CInterface;

	if ( pInt == NULL )
	{
		return E_OUTOFMEMORY;
	}

	HRESULT hr = pInt->QueryInterface(iid, ppv);

	if ( FAILED(hr) )
		delete pInt;

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
	if (clsid != CLSID_SDWInterface)
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
							CLSID_SDWInterface, 
							g_szFriendlyName,
							g_szVerIndProgID,
							g_szProgID	);
}

STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_SDWInterface,
							g_szVerIndProgID,
							g_szProgID	);
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void * lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		g_hModule = static_cast<HMODULE> (hModule);

	return true;
}













