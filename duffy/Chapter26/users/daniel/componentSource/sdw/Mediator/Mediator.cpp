///////////////////////////////////////////////////////////
//
//	Mediator.cpp
//
//	HvE
//	5-5-99

#include "Mediator.h"
#include "..\\registry.h"
// DD aug 2006 #include <fstream.h>
#include <fstream>
#include "..\\SourceContainer\\SourceContainer.h"
#include "..\\ControlCentreContainer\\ControlCentreContainer.h"
#include "..\\InterfaceContainer\\InterfaceContainer.h"

extern "C" CLSID CLSID_SDWSourceContainer;
extern "C" CLSID CLSID_SDWMediator;
extern "C" CLSID CLSID_SDWControlCentreContainer;
extern "C" CLSID CLSID_SDWInterfaceContainer;
using namespace std;

///////////////////////////////////////////////////////////
//
//	Global stuff
//
//

static HMODULE g_hModule = NULL;	// DLL Module Handle
static long g_cComponents = 0;		// Active component counter
static long g_cServerLocks = 0;		// Lock Counter

// Friendly name of Component
const char g_szFriendlyName[]	=	"SDW Mediator component";

// Version indepedend progID
const char g_szVerIndProgID[]	=	"SDW.Mediator";

// ProgID
const char g_szProgID[]		=	"SDW.Mediator.1";


///////////////////////////////////////////////////////////
//
//
//
// 
class CMediator	:	public IUnknown
{
private :
	// A nested class to represent the ISDWMediator Interface
	class SDWMediator	:	public ISDWMediator
	{
	public:
		CMediator * m_pParent;

		// IUnknown Methods
		HRESULT __stdcall QueryInterface(const IID & iid, void ** ppv);
		ULONG	__stdcall AddRef();
		ULONG	__stdcall Release();

													
		// ISDWMediator members
		HRESULT __stdcall SDWEnable();
		HRESULT __stdcall SDWDisable();
		HRESULT __stdcall SDWPush();
		HRESULT __stdcall SDWNotify(/*[in]*/ long h, /*[in]*/ long m);
		HRESULT __stdcall SDWStartup();
		HRESULT __stdcall SDWShutdown();


	}	m_objSDWMediator; // The membervariable that holds the object


	long				m_nRefCnt;
	ISDWSourceContainer						*m_pSrcCon;
	ISDWControlCentreContainer				*m_pCCenCon;
	ISDWInterfaceContainer					*m_pIntCon;



public :
	// C'TOR
	CMediator();
	// D'TOR
	~CMediator();

	// IUnknown Implementation
	HRESULT	__stdcall QueryInterface(const IID & iid, void ** ppv);
	ULONG	__stdcall AddRef();
	ULONG	__stdcall Release();

	void SetSrcCon(ISDWSourceContainer * pSrcCon);
	void SetCCenCon(ISDWControlCentreContainer * pCCenCon);
	void SetIntCon(ISDWInterfaceContainer * pIntCon);

	// Friend classes
	friend class SDWMediator;
};

///////////////////////////////////////////////////////////
//
//	the ClassFactory
//
// 

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

	private:
		CLSID	clsidLayer1,
				clsidLayer2,
				clsidLayer3;

		HRESULT ReadFile();
		HRESULT CreateLayers(CMediator * pMed);

	
	}	m_objFactory;
};

///////////////////////////////////////////////////////////
//
//	Now the outer class
//
// 

CMediator::CMediator()	:	m_nRefCnt(0)
{
	// reference count for DLL usage
	InterlockedIncrement(&g_cComponents);

	// initialize parent variables
	m_objSDWMediator.m_pParent = this;

	m_pSrcCon = NULL;
	m_pCCenCon = NULL;
	m_pIntCon = NULL;
}

CMediator::~CMediator()
{
	InterlockedDecrement(&g_cComponents);
	
	ULONG nRet = 0;
}

// IUnknown Implementation
HRESULT	__stdcall CMediator::QueryInterface(const IID & iid, void ** ppv)
{
	if ( iid == IID_IUnknown )
	{
		*ppv = this;
	}
	else
	{
		if ( iid == IID_ISDWMediator )
		{
			*ppv = &m_objSDWMediator;
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

ULONG	__stdcall CMediator::AddRef()
{
	return InterlockedIncrement(&m_nRefCnt);
}

ULONG	__stdcall CMediator::Release()
{
	if ( InterlockedDecrement(&m_nRefCnt) == 0 )
	{
		delete this;
		return 0;
	}

	return m_nRefCnt;
}

void CMediator::SetSrcCon(ISDWSourceContainer * pSrcCon)
{
	m_pSrcCon = pSrcCon;
}

void CMediator::SetCCenCon(ISDWControlCentreContainer * pCCenCon)
{
	m_pCCenCon = pCCenCon;
}

void CMediator::SetIntCon(ISDWInterfaceContainer * pIntCon)
{
	m_pIntCon = pIntCon;
}

///////////////////////////////////////////////////////////
//
//	Now it's time to implement the innerclass SDWMediator
//
// 

HRESULT	__stdcall CMediator::SDWMediator::SDWDisable()
{
	if ( m_pParent->m_pSrcCon != NULL )
	{
		m_pParent->m_pSrcCon->SDWDisable();
		return S_OK;
	}
	else
		return E_FAIL;
	
}

HRESULT	__stdcall CMediator::SDWMediator::SDWEnable()
{
	if ( m_pParent->m_pSrcCon != NULL )
	{
		m_pParent->m_pSrcCon->SDWEnable();
		return S_OK;
	}
	else
	{
		return S_OK;
	}
}

HRESULT	__stdcall CMediator::SDWMediator::SDWNotify(long h, long m)
{
	if ( m_pParent->m_pIntCon != NULL )
	{
		m_pParent->m_pIntCon->SDWNotify(h, m);
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT	__stdcall CMediator::SDWMediator::SDWPush()
{
	if ( m_pParent->m_pCCenCon != NULL )
	{	
		m_pParent->m_pCCenCon->SDWPush();
		return S_OK;
	}
	else 
		return E_FAIL;
}

HRESULT	__stdcall CMediator::SDWMediator::SDWStartup()
{
	if ( m_pParent->m_pCCenCon != NULL && m_pParent->m_pSrcCon != NULL )
	{
		m_pParent->m_pCCenCon->SDWInitialise(9, 58);
		
		m_pParent->m_pSrcCon->SDWInitialise();
		
		return S_OK;
	}
	else
		return E_FAIL;

}

HRESULT __stdcall CMediator::SDWMediator::SDWShutdown()
{
	HRESULT hr = S_OK;
	ISDWConnector * pCon;

	// Is there a valid pointer ?
	if ( m_pParent->m_pSrcCon )
	{
		// Query for the Connector interface
		hr = m_pParent->m_pSrcCon->QueryInterface( IID_ISDWConnector, (void **) &pCon );
		
		if ( SUCCEEDED(hr) )
		{
			// Kill the connection. This kills al the layers in the group
			hr = pCon->SDWKillConnection();

			// Release the connectionpointer
			pCon->Release();
		}
		// Release the Containerpointer
		m_pParent->m_pSrcCon->Release();
	}

	// Is there a valid pointer ?
	if ( m_pParent->m_pCCenCon )
	{
		// Query for the Connector interface
		hr = m_pParent->m_pCCenCon->QueryInterface( IID_ISDWConnector, (void **) &pCon );

		if ( SUCCEEDED(hr) )
		{
			// Kill the connection. This kills al the layers in the group
			hr = pCon->SDWKillConnection();

			// Release the connectionpointer
			pCon->Release();
		}
		// Release the Containerpointer
		m_pParent->m_pCCenCon->Release();
	}

	// Is there a valid pointer ?
	if ( m_pParent->m_pIntCon )
	{
		// Query for the Connector interface
		hr = m_pParent->m_pIntCon->QueryInterface( IID_ISDWConnector, (void **) &pCon );

		if ( SUCCEEDED(hr) )
		{
			// Kill the connection. This kills al the layers in the group
			hr = pCon->SDWKillConnection();

			// Release the connectionpointer
			pCon->Release();
		}
		// Release the Containerpointer
		m_pParent->m_pIntCon->Release();
	}

	return hr;
}



HRESULT	__stdcall CMediator::SDWMediator::QueryInterface(const IID &iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG	__stdcall CMediator::SDWMediator::AddRef()
{
	return m_pParent->AddRef();
}

ULONG	__stdcall CMediator::SDWMediator::Release()
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

	CMediator * pMed = new CMediator;

	if ( pMed == NULL )
	{
		return E_OUTOFMEMORY;
	}

	HRESULT hr = pMed->QueryInterface(iid, ppv);

	if ( FAILED(hr) )
		delete pMed;

	hr = ReadFile();
	if ( FAILED(hr) )
	{
		return hr;
	}

	hr = CreateLayers(pMed);

	return hr;
}

HRESULT CFactory::Factory::ReadFile()
{
	// curious ! if we use <fstream> instead of <fstream.h>
	// we get an error sdaying that ios::nocreate is not an meber of base_ios
	//ifstream in("d:\\projects\\sdwv3~1\\mediator.cfg", ios::in | ios::nocreate );
	ifstream in("d:\\projects\\sdwv3~1\\mediator.cfg");
	
	if ( in.fail() )
	{
		MessageBox(0,"Cannot open configfile mediator.cfg",0,0);
		return E_FAIL;
	}

	char szStr[39];
	wchar_t wszStr [39];
	HRESULT hr = S_OK;
	
	// 40 charachters to read, since the clsid is 39, and 
	// we DO want to read the delimeter '\n' which is the default 
	// third parameter. After readin the delimeter the fileposition is 
	// at the beginning of the next line
	in.getline(szStr, 40);

	// Convert it to a normal ANSI string
	mbstowcs(wszStr, szStr, 39);
	// Create a CLSID from the string
	hr = CLSIDFromString(wszStr, &clsidLayer1);

	if ( FAILED(hr) )
	{
		MessageBox(0,"Something is wrong with the first CLSID in the cfg file", 0,0);
		in.close();
		return hr;
	}

	in.getline(szStr, 40);
	mbstowcs(wszStr, szStr, 39);
	hr = CLSIDFromString(wszStr, &clsidLayer2);

	if ( FAILED(hr) )
	{
		MessageBox(0,"Something is wrong with the second CLSID in the cfg file", 0,0);
		in.close();
		return hr;
	}

	in.getline(szStr, 40);
	mbstowcs(wszStr, szStr, 39);
	hr = CLSIDFromString(wszStr, &clsidLayer3);

	if ( FAILED(hr) )
	{
		MessageBox(0,"Something is wrong with the third CLSID in the cfg file", 0,0);
		in.close();
		return hr;
	}

	// close the file
	in.close();

	return hr;
}

HRESULT CFactory::Factory::CreateLayers(CMediator * pMed)
{
	ISDWInterfaceContainer * pIntCon;
	ISDWSourceContainer * pSrcCon;
	ISDWControlCentreContainer * pCCenCon;
	ISDWConnector * pCon;

	HRESULT hr;

	// First we're going to create the components
	hr = CoCreateInstance(	clsidLayer1,
									NULL,
									CLSCTX_LOCAL_SERVER,
									IID_ISDWSourceContainer,
									(void **) &pSrcCon	);

	if ( FAILED(hr) )
	{
		return hr;
	}

	hr = CoCreateInstance(	clsidLayer2,
									NULL,
									CLSCTX_LOCAL_SERVER,
									IID_ISDWControlCentreContainer,
									(void **) &pCCenCon	);

	if ( FAILED(hr) )
	{
		return hr;
	}

	hr = CoCreateInstance(	clsidLayer3,
									NULL,
									CLSCTX_LOCAL_SERVER,
									IID_ISDWInterfaceContainer,
									(void **) &pIntCon	);

	if ( FAILED(hr) )
	{
		return hr;
	}

	// now it is time to connect the components, using QueryInterface
	hr = pSrcCon->QueryInterface(IID_ISDWConnector, (void **) &pCon );

	if ( FAILED(hr) )
	{
		return hr;
	}

	// if we have an ISDWConnector we're using it to connect the layers with eachother
	pCon->SDWSetUpperConnection(pMed);
	pCon->Release();

	hr = pCCenCon->QueryInterface(IID_ISDWConnector, (void **) &pCon );

	if ( FAILED(hr) )
	{
		return hr;
	}

	pCon->SDWSetUpperConnection(pMed);
	pCon->Release();

	hr = pIntCon->QueryInterface(IID_ISDWConnector, (void **) &pCon );

	if ( FAILED(hr) )
	{
		return hr;
	}

	pCon->SDWSetUpperConnection(pMed);  
	pCon->Release();

	pMed->SetSrcCon(pSrcCon);
	pMed->SetCCenCon(pCCenCon);
	pMed->SetIntCon(pIntCon);

	return S_OK;	
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
	if (clsid != CLSID_SDWMediator)
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
									CLSID_SDWMediator, 
									g_szFriendlyName,
									g_szVerIndProgID,
									g_szProgID	);
}

STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_SDWMediator,
									g_szVerIndProgID,
									g_szProgID	);
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void * lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		g_hModule = static_cast<HMODULE> (hModule);

	return true;
}


