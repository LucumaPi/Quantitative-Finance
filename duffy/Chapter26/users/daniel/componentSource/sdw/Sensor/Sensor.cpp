///////////////////////////////////////////////////////////
//	
//	Sensor.cpp
//
// (C) Datasim Education 1999
// May 1999 HvE started
//
// The implementation of the Sensor class.
///////////////////////////////////////////////////////////
#include "sensor.h"
#include "..\\registry.h"
#include "..\\converter\\converter.h"

#include <iostream>
#include <ctime>

using namespace std;

UINT TimerID;

///////////////////////////////////////////////////////////
//
//	Global stuff
//
// 
extern "C" CLSID CLSID_SDWSensor;
extern "C" CLSID CLSID_SDWConverter;

static HMODULE g_hModule = NULL;	// DLL Module Handle
static long g_cComponents = 0;		// Active component counter
static long g_cServerLocks = 0;		// Lock Counter

// Friendly name of Component
const char g_szFriendlyName[]	=	"SDW Sensor component";

// Version indepedend progID
const char g_szVerIndProgID[]	=	"SDW.Sensor";

// ProgID
const char g_szProgID[]		=	"SDW.Sensor.1";


///////////////////////////////////////////////////////////
//
//	
//
// 


class CSensor	:	public IUnknown
{
private :
	// A nested class to represent the ISDWSensor Interface
	class SDWSensor	:	public ISDWSensor
	{
	public:
		CSensor * m_pParent;

		// IUnknown Methods
		HRESULT __stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG	__stdcall AddRef();
		ULONG	__stdcall Release();

													
		// ISDWSensor members
		HRESULT	__stdcall SDWStart_pulsing();
		HRESULT __stdcall SDWStop_pulsing();

	}	m_objSDWSensor; // The membervariable that holds the object

	class SDWConnector	:	public ISDWConnector
	{
	public:
		CSensor * m_pParent;

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
public:

	static ISDWConverter * m_pConv;

	static void CALLBACK TimerProc( HWND hwnd, UINT iMsg, UINT TimerID, DWORD dwTime );
	
public :
	// C'TOR
	CSensor();
	// D'TOR
	~CSensor();

	// IUnknown Implementation
	HRESULT	__stdcall QueryInterface(const IID & iid, void ** ppv);
	ULONG	__stdcall AddRef();
	ULONG	__stdcall Release();

	// Friend classes
	friend class SDWSensor;
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

CSensor::CSensor()	:	m_nRefCnt(0)
{
	// reference count for DLL usage
	InterlockedIncrement(&g_cComponents);

	// initialize parent variables
	m_objSDWSensor.m_pParent = this;
	m_objSDWConnector.m_pParent = this;

	m_pConv = NULL;
}

CSensor::~CSensor()
{
	InterlockedDecrement(&g_cComponents);
}

// IUnknown Implementation
HRESULT	__stdcall CSensor::QueryInterface(const IID & iid, void ** ppv)
{
	if ( iid == IID_IUnknown )
	{
		*ppv = this;
	}
	else
		if ( iid == IID_ISDWSensor )
		{
			*ppv = &m_objSDWSensor;
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

ULONG	__stdcall CSensor::AddRef()
{
	return InterlockedIncrement(&m_nRefCnt);
}

ULONG	__stdcall CSensor::Release()
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
//	Now it's time to implement the innerclass SDWSensor
//
// 
ISDWConverter * CSensor::m_pConv;

void CALLBACK CSensor::TimerProc( HWND hwnd, UINT iMsg, UINT TimerID, DWORD dwTime )
{
	if ( m_pConv != NULL )
	{
	
		m_pConv->SDWUpdate();
	}

}


HRESULT	__stdcall CSensor::SDWSensor::SDWStart_pulsing()
{
	HRESULT hr = S_OK;
	
	TimerID = SetTimer( NULL, NULL, 1000, ( TIMERPROC ) (m_pParent->TimerProc) );

	return hr;
}



HRESULT	__stdcall CSensor::SDWSensor::SDWStop_pulsing()
{
	// Kill the timer
	KillTimer(0,TimerID);
	return S_OK;
}

HRESULT	__stdcall CSensor::SDWSensor::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CSensor::SDWSensor::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CSensor::SDWSensor::Release()
{
	return m_pParent->Release();
}

///////////////////////////////////////////////////////////
//
//	The SDWConnection implementation
//
// 

HRESULT __stdcall CSensor::SDWConnector::SDWSetLowerConnection(IUnknown * pUnk)
{
	return E_FAIL;
}

HRESULT __stdcall CSensor::SDWConnector::SDWSetUpperConnection(IUnknown * pUnk)
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
	{
		hr = pUnk->QueryInterface( IID_ISDWConverter, (void **) &m_pParent->m_pConv);
	}

	return hr;
}

HRESULT __stdcall CSensor::SDWConnector::SDWKillConnection()
{
	KillTimer(NULL, TimerID);
	if ( m_pParent->m_pConv )
	{
		m_pParent->m_pConv->Release();
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT	__stdcall CSensor::SDWConnector::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CSensor::SDWConnector::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CSensor::SDWConnector::Release()
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

	CSensor * pSens = new CSensor;

	if ( pSens == NULL )
	{
		return E_OUTOFMEMORY;
	}

	HRESULT hr = pSens->QueryInterface(iid, ppv);

	if ( FAILED(hr) )
		delete pSens;

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
	if (clsid != CLSID_SDWSensor)
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
							CLSID_SDWSensor, 
							g_szFriendlyName,
							g_szVerIndProgID,
							g_szProgID	);
}

STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_SDWSensor,
							g_szVerIndProgID,
							g_szProgID	);
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void * lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		g_hModule = static_cast<HMODULE> (hModule);

	return true;
}













