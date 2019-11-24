/******************************************************************************************
FileName		: Source.cpp
Author			: your name here
Purpose		    : Implementation of the Source component
Date Of Creation: 4/28/99
Modification History :
Date             Modifications
******************************************************************************************/

#include "Source.h"
#include "..\\Converter\\Converter.h"
#include "..\\SourceContainer\\SourceContainer.h"
#include "..\\registry.h"

#include <iostream>

using std::cout;
using std::endl;

extern "C" CLSID CLSID_SDWSource;
extern "C" CLSID CLSID_SDWConverter;
extern "C" CLSID CLSID_SDWSourceContainer;
///////////////////////////////////////////////////////////
//
//	Global stuff
//
// 

static HMODULE g_hModule = NULL;	// DLL Module Handle
static long g_cComponents = 0;		// Active component counter
static long g_cServerLocks = 0;		// Lock Counter

// Friendly name of Component
const char g_szFriendlyName[]	=	"SDW Source component";

// Version indepedend progID
const char g_szVerIndProgID[]	=	"SDW.Source";

// ProgID
const char g_szProgID[]		=	"SDW.Source.1";


///////////////////////////////////////////////////////////
//
//	Class definition
//
// 

// This class is the Source component. It is implemented using
// the examples from the Fundamental COM Course

class CSource	:	public IUnknown
{
private :
	// A nested class to represent the ISDWSource Interface
	class SDWSource	:	public ISDWSource
	{
	public:
		CSource * m_pParent;

		// IUnknown Methods
		HRESULT __stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG	__stdcall AddRef();
		ULONG	__stdcall Release();
													
		// ISDWSource members
		HRESULT	__stdcall SDWEnable();
		HRESULT	__stdcall SDWDisable();
		HRESULT	__stdcall SDWInitialise();
		HRESULT	__stdcall SDWUpdate();
		HRESULT	__stdcall SDWState(/*out*/long * value);

	}	m_objSDWSource; // The membervariable that holds the object

	class SDWConnector	:	public ISDWConnector
	{
	public:
		CSource * m_pParent;

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

	ISDWConverter	*m_pConv;
	ISDWSourceContainer	*m_pSrcCon;

public :
	// C'TOR
	CSource();
	// D'TOR
	~CSource();

	// IUnknown Implementation
	HRESULT	__stdcall QueryInterface(const IID & iid, void ** ppv);
	ULONG	__stdcall AddRef();
	ULONG	__stdcall Release();

	// Friend classes
	friend class SDWSource;
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

CSource::CSource()	:	m_nRefCnt(0)
{

	m_fStat = false;

	// reference count for DLL usage
	InterlockedIncrement(&g_cComponents);

	// initialize parent variables
	m_objSDWSource.m_pParent = this;
	m_objSDWConnector.m_pParent = this;

	m_pConv = NULL;
	m_pSrcCon = NULL;
}

CSource::~CSource()
{
	InterlockedDecrement(&g_cComponents);
}

// IUnknown Implementation
HRESULT	__stdcall CSource::QueryInterface(const IID & iid, void ** ppv)
{
	
	HRESULT hr = S_OK;

	// Are we asked for a known interface ?
	if ( iid == IID_IUnknown )
	{
		*ppv = this;
	}
	else
	{
		if ( iid == IID_ISDWSource )
		{
			*ppv = &m_objSDWSource;
		}
		else
			if (iid == IID_ISDWConnector)
			{
				*ppv = &m_objSDWConnector;
			}
			else
			// Oeps, the requested interface is not here
			{
				*ppv = NULL;
				return E_NOINTERFACE;
			}
	}
	IUnknown * pUnk = (IUnknown*) *ppv;
	// Adding a referencecount for this interface

	pUnk->AddRef();
	
	return hr;
}

ULONG	__stdcall CSource::AddRef()
{
	return InterlockedIncrement(&m_nRefCnt);
}

ULONG	__stdcall CSource::Release()
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
//	Now it's time to implement the innerclass SDWSource
//
// 

HRESULT	__stdcall CSource::SDWSource::SDWInitialise()
{
	if ( m_pParent->m_pConv != NULL )
	{
		m_pParent->m_pConv->SDWInitialise();
		return S_OK;
	}
	else 
		return E_FAIL;
}

HRESULT	__stdcall CSource::SDWSource::SDWEnable()
{
	m_pParent->m_fStat = false;
	
	if (	m_pParent->m_pConv != NULL )
	{
		m_pParent->m_pConv->SDWEnable();
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT	__stdcall CSource::SDWSource::SDWDisable()
{
	m_pParent->m_fStat = true;

	if ( m_pParent->m_pConv != NULL )
	{
		m_pParent->m_pConv->SDWDisable();
		return S_OK;
	}
	else
		return E_FAIL;
}


HRESULT	__stdcall CSource::SDWSource::SDWUpdate()
{
	if ( m_pParent->m_fStat == 1)
	{
		// Sanity check: no action if disabled
		cout << "Source disabled, no Watch update\n";
	}

	if ( m_pParent->m_fStat == 0)
	{
		// Hier moet ie de SourceContainer een push gaan geven
		if ( m_pParent->m_pSrcCon != NULL )
		{
			m_pParent->m_pSrcCon->SDWPush();
		}
		else
			return E_FAIL;
	}
	return S_OK;
}

HRESULT	__stdcall CSource::SDWSource::SDWState(long * value)
{
	*value = m_pParent->m_fStat;
	
	return S_OK;
}


HRESULT	__stdcall CSource::SDWSource::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CSource::SDWSource::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CSource::SDWSource::Release()
{
	return m_pParent->Release();
}

///////////////////////////////////////////////////////////
//
//	The SDWConnection implementation
//
// 

HRESULT __stdcall CSource::SDWConnector::SDWSetLowerConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;
	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWConverter, (void **) &m_pParent->m_pConv );
	
	return hr;
}

HRESULT __stdcall CSource::SDWConnector::SDWSetUpperConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWSourceContainer, (void **) &m_pParent->m_pSrcCon );

	return hr;
}

HRESULT __stdcall CSource::SDWConnector::SDWKillConnection()
{
	HRESULT hr = S_OK;

	// is there a connecntion to the Converter
	if ( m_pParent->m_pConv )
	{
		ISDWConnector * pCon = NULL;
		
		// Query for the Connector Interface
		hr = m_pParent->m_pConv->QueryInterface(IID_ISDWConnector, (void **) &pCon );
		
		if (FAILED(hr))
			return E_FAIL;

		// Kill the connection of the Converter
		hr = pCon->SDWKillConnection();

		// release the Connector interface
		pCon->Release();

		if (FAILED(hr))
			return E_FAIL;

		// release the Converter interfacepointer
		m_pParent->m_pConv->Release();
	}

	// release the SourceContainer interfacepointer
	if ( m_pParent->m_pSrcCon ) 
		m_pParent->m_pSrcCon->Release();

	return hr;
}

HRESULT	__stdcall CSource::SDWConnector::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CSource::SDWConnector::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CSource::SDWConnector::Release()
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

	CSource * pSrc = new CSource;

	if ( pSrc == NULL )
	{
		return E_OUTOFMEMORY;
	}

	HRESULT hr = pSrc->QueryInterface(iid, ppv);

	if ( FAILED(hr) )
		delete pSrc;

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
	if (clsid != CLSID_SDWSource)
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
									CLSID_SDWSource, 
									g_szFriendlyName,
									g_szVerIndProgID,
									g_szProgID	);
}

STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_SDWSource,
									g_szVerIndProgID,
									g_szProgID	);
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void * lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		g_hModule = static_cast<HMODULE> (hModule);

	return true;
}













