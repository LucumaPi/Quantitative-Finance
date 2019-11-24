/////////////////////////////////////////////////////////
//
//   Factory.cpp
//
//   Henk van Es
//
//   5/28/99
//
/////////////////////////////////////////////////////////


#include "Factory.h"
#include "InterfaceContainerComponent.h"
#include <fstream.h>
#include "..\\Display\\Display.h"
#include "..\\Router\\Router.h"
#include "SDWConnector.h"


DWORD CFactory::s_dwThreadID = 0 ;

CFactory::CFactory() : m_nRefCnt(0)
{
	m_objFactory.m_pParent = this;
}

CFactory::~CFactory()
{
}

HRESULT __stdcall CFactory::QueryInterface(const IID & iid, void ** ppv)
{
	HRESULT hr = S_OK;
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
			// Oh oh, no supported interface requested
			*ppv = NULL;
			return E_NOINTERFACE;
		}

	IUnknown * pUnk = (IUnknown*) *ppv;
	pUnk->AddRef();

	return S_OK;
}

ULONG __stdcall CFactory::AddRef()
{
	return InterlockedIncrement(&m_nRefCnt);
}

ULONG __stdcall CFactory::Release()
{
	if (InterlockedDecrement(&m_nRefCnt) == 0)
	{
		delete this;
		return 0;
	}

	return m_nRefCnt;
}

HRESULT __stdcall CFactory::Factory::QueryInterface(const IID & iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG __stdcall CFactory::Factory::AddRef()
{
	return m_pParent->AddRef();
}

ULONG __stdcall CFactory::Factory::Release()
{
	return m_pParent->Release();
}

HRESULT __stdcall CFactory::Factory::CreateInstance(IUnknown * pUnknownOuter,
																	 const IID & iid,
																	 void ** ppv )
{

	if ( pUnknownOuter != NULL )
	{
		// No aggrgation supported
		return CLASS_E_NOAGGREGATION;
	}

	// This is where the main component in this EXE is generated
	CInterfaceContainerComponent * pIntCon = new CInterfaceContainerComponent;

	if ( pIntCon == NULL )
	{
		return E_OUTOFMEMORY;
	}

	HRESULT hr = pIntCon->QueryInterface(iid, ppv);

	if ( FAILED(hr) )
	{
		delete pIntCon;
		return hr;
	}

	// Here we're going to read a config file and create the components
	// whose classid we have read.

	hr = ReadFile();
	if ( FAILED(hr) )
		return hr;
	
	hr = CreateLayers(pIntCon);

	return hr;

}

HRESULT CFactory::Factory::ReadFile()
{
	// curious ! if we use <fstream> instead of <fstream.h>
	// we get an error sdaying that ios::nocreate is not an meber of base_ios
	ifstream in("d:\\projects\\sdwv3~1\\interface.cfg", ios::in | ios::nocreate );
	
	if ( in.fail() )
	{
		MessageBox(0,"Cannot open configfile interface.cfg",0,0);
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

HRESULT CFactory::Factory::CreateLayers(CInterfaceContainerComponent * pIntCon)
{
	ISDWInterface * pInt;
	ISDWDisplay * pDisp;
	ISDWRouter * pRout;
	ISDWConnector * pCon;

	HRESULT hr;

	// First we're going to create the components
	hr = CoCreateInstance(	clsidLayer1,
									NULL,
									CLSCTX_INPROC_SERVER,
									IID_ISDWInterface,
									(void **) &pInt	);

	if ( FAILED(hr) )
	{
		return hr;
	}

	hr = CoCreateInstance(	clsidLayer2,
									NULL,
									CLSCTX_INPROC_SERVER,
									IID_ISDWRouter,
									(void **) &pRout	);

	if ( FAILED(hr) )
	{
		return hr;
	}

	hr = CoCreateInstance(	clsidLayer3,
									NULL,
									CLSCTX_INPROC_SERVER,
									IID_ISDWDisplay,
									(void **) &pDisp	);

	if ( FAILED(hr) )
	{
		return hr;
	}

	// now it is time to connect the components, using queryinterface
	hr = pDisp->QueryInterface(IID_ISDWConnector, (void **) &pCon );

	if ( FAILED(hr) )
	{
		return hr;
	}

	// if we have an ISDWConnector we're using it to connect the layers with eachother
	pCon->SDWSetUpperConnection(pRout);
	pCon->Release();

	hr = pRout->QueryInterface(IID_ISDWConnector, (void **) &pCon );

	if ( FAILED(hr) )
	{
		return hr;
	}

	pCon->SDWSetUpperConnection(pInt);
	pCon->SDWSetLowerConnection(pDisp);
	pCon->Release();

	hr = pInt->QueryInterface(IID_ISDWConnector, (void **) &pCon );

	if ( FAILED(hr) )
	{
		return hr;
	}

	pCon->SDWSetLowerConnection(pRout);
	pCon->SDWSetUpperConnection(pIntCon);  
	pCon->Release();

	hr = pIntCon->QueryInterface(IID_ISDWConnector, (void**) &pCon );

	if ( FAILED(hr) )
	{
		return hr;
	}

	// here we only connect the lower layer. the upper layer will be 
	// connected in the mediator component
	pCon->SDWSetLowerConnection(pInt);
	
	pCon->Release();

	pInt->Release();
	pDisp->Release();
	pRout->Release();

	return S_OK;	
}

HRESULT __stdcall CFactory::Factory::LockServer(BOOL bLock)
{
	if (bLock)
		InterlockedIncrement(&g_cServerLocks);
	else
		InterlockedDecrement(&g_cServerLocks);

	return S_OK;
}
																			
void CFactory::CloseExe()
{
	// If there are no more active components, than we send a 
	// WM_QUIT message to the exe to let it destroy itself
	if ( g_cComponents == 0 )
	{
	//	MessageBox(0,"Components gets TERMINATED !",0,0);
		PostThreadMessage( s_dwThreadID, WM_QUIT, 0, 0 );
	}
}
