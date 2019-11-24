///////////////////////////////////////////////////////////
//	Client.cpp
//
//	HvE '99
//
//	Creates a mediator component and calls 
//	that components startup funtcion
//	through the given interfacepointer
//

#include <iostream>
#include <objbase.h>
#include "client.h"
#include "..\\mediator\\mediator.h"
#include "..\\ControlCentreContainer\\ControlCentreContainer.h"
#include "..\\SourceContainer\\SourceContainer.h"
#include "..\\InterfaceContainer\\InterfaceContainer.h"

using std::cout;
using std::endl;

extern "C" CLSID CLSID_SDWMediator;
extern "C" CLSID CLSID_SDWControlCentreContainer;
extern "C" CLSID CLSID_SDWSourceContainer;
extern "C" CLSID CLSID_SDWInterfaceContainer;

void GiveMsgBox(HRESULT hr);
HRESULT CreateComponent(const CLSID &clsid, const IID &iid, void ** ppv);

int main(int argc, char* argv[])
{
	ISDWMediator * pMed = NULL;
	ISDWControlCentreContainer * pConCenCon = NULL;
	ISDWSourceContainer * pSrc = NULL;
	ISDWInterfaceContainer * pInt = NULL;

	HRESULT hr;

	// Initialize COM library
	hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		GiveMsgBox(hr);
		exit(0);
	}

	hr = CreateComponent(	CLSID_SDWMediator,
									IID_ISDWMediator,
									(void **) &pMed	);
	

	if ( SUCCEEDED(hr) )
	{
		cout << "We hebben een Interface pointer !" << endl;
		
		ULONG ulRet = pMed->SDWStartup();
	}
	else
	{
		GiveMsgBox(hr);
	}

/*
	hr = CreateComponent(	CLSID_SDWControlCentreContainer,
									IID_ISDWControlCentreContainer,
									(void **) &pConCenCon	);
	

	if ( SUCCEEDED(hr) )
	{
		cout << "We hebben een Interface pointer !" << endl;

		ULONG ulRet = pConCenCon->Release();
	}
	else
	{
		GiveMsgBox(hr);
	}

	hr = CreateComponent(	CLSID_SDWSourceContainer,
									IID_ISDWSourceContainer,
									(void **) &pSrc	);
	

	if ( SUCCEEDED(hr) )
	{
		cout << "We hebben een Interface pointer !" << endl;

		ULONG ulRet = pSrc->Release();
	}
	else
	{
		GiveMsgBox(hr);
	}
	
	hr = CreateComponent(	CLSID_SDWInterfaceContainer,
									IID_ISDWInterfaceContainer,
									(void **) &pInt	);
	

	if ( SUCCEEDED(hr) )
	{
		cout << "We hebben een Interface pointer !" << endl;
		
		ULONG ulRet = pInt->Release();
	}
	else
	{
		GiveMsgBox(hr);
	}
*/	
	// Uninitialize COM library
	CoUninitialize();

	return 0;
}

///////////////////////////////////////////////////////////
//
//	Show the string belonging to a HRESULT 
//
// 

void GiveMsgBox(HRESULT hr)
{
	void * pMsg;

	FormatMessage(	FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
						NULL,
						hr,
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
						(LPSTR) & pMsg,
						0,
						NULL	);

	MessageBox(NULL, (LPSTR)pMsg, "ERROR", MB_OK);

	LocalFree(pMsg);
}

///////////////////////////////////////////////////////////
//
//	Create a component with the given parameters
//
// 

HRESULT CreateComponent(const CLSID &clsid, const IID &iid, void ** ppv)
{
	HRESULT hr;

	hr = CoCreateInstance(	clsid,
									NULL,
									CLSCTX_INPROC_SERVER,
									iid,
									ppv );

	return hr;
}