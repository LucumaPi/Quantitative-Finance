/******************************************************************************************
FileName		: Converter.cpp
Author			: your name here
Purpose		    : Implementation of the Converter component
Date Of Creation: 4/28/99
Modification History :
Date             Modifications
******************************************************************************************/

#include "Converter.h"
#include "..\\registry.h"
#include "..\\source\\source.h"
#include "..\\sensor\\sensor.h"


#include <iostream>

using std::cout;
using std::endl;

extern "C" CLSID CLSID_SDWConverter;
extern "C" CLSID CLSID_SDWSensor;


///////////////////////////////////////////////////////////
//
//	Global stuff
//
// 

static HMODULE g_hModule = NULL;	// DLL Module Handle
static long g_cComponents = 0;		// Active component counter
static long g_cServerLocks = 0;		// Lock Counter

// Friendly name of Component
const char g_szFriendlyName[]	=	"SDW Converter component";

// Version indepedend progID
const char g_szVerIndProgID[]	=	"SDW.Converter";

// ProgID
const char g_szProgID[]		=	"SDW.Converter.1";


///////////////////////////////////////////////////////////
//
//	Class definition
//
// 

// This class is the Converter component. It is implemented using
// the examples from the Fundamental COM Course

class CConverter	:	public IUnknown
{
private :
	// A nested class to represent the ISDWConverter Interface
	class SDWConverter	:	public ISDWConverter
	{
	public:
		CConverter * m_pParent;

		// IUnknown Methods
		HRESULT __stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG	__stdcall AddRef();
		ULONG	__stdcall Release();

													
		// ISDWConverter members
		HRESULT	__stdcall SDWEnable();
		HRESULT	__stdcall SDWDisable();
		HRESULT	__stdcall SDWInitialise();
		HRESULT	__stdcall SDWUpdate();
		HRESULT	__stdcall SDWValue(/*out*/long * value);

	}	m_objSDWConverter; // The membervariable that holds the object

	class SDWConnector	:	public ISDWConnector
	{
	public:
		CConverter * m_pParent;

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
	
	// The referencount
	long			m_nRefCnt;

	// SDWConverter datamembers
	BOOL			m_fStat;
	long			m_iCounter;

	// Pointers to the components above and below
	ISDWSensor	*m_pSens;
	ISDWSource	*m_pSrc;

public :
	// C'TOR	CConverter();
	// D'TOR
	~CConverter();

	// IUnknown Implementation
	HRESULT	__stdcall QueryInterface(const IID & iid, void ** ppv);
	ULONG	__stdcall AddRef();
	ULONG	__stdcall Release();

	// Friend classes
	friend class SDWConverter;
	friend class SDWConnector;
};

class CFactory : public IUnknown
{
private:
	// Reference counter
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

CConverter::CConverter()	:	m_nRefCnt(0)
{
	m_fStat = false;
	m_iCounter = 0;

	// reference count for DLL usage
	InterlockedIncrement(&g_cComponents);

	// initialize parent variables
	m_objSDWConverter.m_pParent = this;
	m_objSDWConnector.m_pParent = this;

	m_pSrc = NULL;
	m_pSens = NULL;
}

CConverter::~CConverter()
{
	InterlockedDecrement(&g_cComponents);
}

// IUnknown Implementation
HRESULT	__stdcall CConverter::QueryInterface(const IID & iid, void ** ppv)
{
	HRESULT hr = S_OK;

	if ( iid == IID_IUnknown )
	{
		*ppv = this;
	}
	else
		if ( iid == IID_ISDWConverter )
		{
			*ppv = &m_objSDWConverter;
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

ULONG	__stdcall CConverter::AddRef()
{
	return InterlockedIncrement(&m_nRefCnt);
}

ULONG	__stdcall CConverter::Release()
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
//	Now it's time to implement the innerclass SDWConverter
//
// 

HRESULT	__stdcall CConverter::SDWConverter::SDWInitialise()
{
	// Give it to the next layer
	if ( m_pParent->m_pSens != NULL)
	{
		m_pParent->m_pSens->SDWStart_pulsing();
		return S_OK;
	}
	return E_FAIL;
}

HRESULT	__stdcall CConverter::SDWConverter::SDWEnable()
{
	m_pParent->m_fStat = false;
	
	if ( m_pParent->m_pSens != NULL )
	{
		m_pParent->m_pSens->SDWStart_pulsing();
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT	__stdcall CConverter::SDWConverter::SDWDisable()
{
	m_pParent->m_fStat = true;

	if ( m_pParent->m_pSens != NULL )
	{
		m_pParent->m_pSens->SDWStop_pulsing();
		m_pParent->m_iCounter = 0;
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT	__stdcall CConverter::SDWConverter::SDWUpdate()
{
	if (m_pParent->m_iCounter == 60)
	{
		m_pParent->m_iCounter = 0;

		if ( m_pParent->m_pSrc != NULL )
		{
			m_pParent->m_pSrc->SDWUpdate(); 
		}
		else
		{
			m_pParent->m_iCounter += 1;
			return E_FAIL;
		}
	}

	m_pParent->m_iCounter += 1;
	
	return S_OK;
}

HRESULT	__stdcall CConverter::SDWConverter::SDWValue(long * value)
{
	*value = m_pParent->m_iCounter;
	return S_OK;
}

HRESULT	__stdcall CConverter::SDWConverter::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CConverter::SDWConverter::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CConverter::SDWConverter::Release()
{
	return m_pParent->Release();
}


///////////////////////////////////////////////////////////
//
//	The SDWConnection implementation
//
// 

HRESULT __stdcall CConverter::SDWConnector::SDWSetLowerConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;
	
	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWSensor, (void **) &m_pParent->m_pSens);
	
	return hr;
}

HRESULT __stdcall CConverter::SDWConnector::SDWSetUpperConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWSource, (void **) &m_pParent->m_pSrc );

	return hr;
}

HRESULT __stdcall CConverter::SDWConnector::SDWKillConnection()
{
	HRESULT hr = S_OK;

	// is there a connecntion to the Sensor
	if ( m_pParent->m_pSens )
	{
		ISDWConnector * pCon = NULL;
		
		// Query for the Connector Interface
		hr = m_pParent->m_pSens->QueryInterface(IID_ISDWConnector, (void **) &pCon );
		
		if (FAILED(hr))
			return E_FAIL;

		// Kill the connection of the Sensor
		hr = pCon->SDWKillConnection();

		// release the Connector interface
		pCon->Release();

		if (FAILED(hr))
			return E_FAIL;

		// release the Sensor interfacepointer
		m_pParent->m_pSens->Release();
	}

	// release the Source interfacepointer
	if ( m_pParent->m_pSrc ) 
		m_pParent->m_pSrc->Release();

	return hr;

}


HRESULT	__stdcall CConverter::SDWConnector::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CConverter::SDWConnector::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CConverter::SDWConnector::Release()
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

	CConverter * pConv = new CConverter;

	if ( pConv == NULL )
	{
		return E_OUTOFMEMORY;
	}

	HRESULT hr = pConv->QueryInterface(iid, ppv);

	if ( FAILED(hr) )
		delete pConv;

	
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
	if (clsid != CLSID_SDWConverter)
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
							CLSID_SDWConverter, 
							g_szFriendlyName,
							g_szVerIndProgID,
							g_szProgID	);
}

STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_SDWConverter,
							g_szVerIndProgID,
							g_szProgID	);
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void * lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		g_hModule = static_cast<HMODULE> (hModule);

	return true;
}
