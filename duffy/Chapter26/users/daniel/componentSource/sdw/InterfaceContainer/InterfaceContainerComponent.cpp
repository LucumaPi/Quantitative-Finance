/////////////////////////////////////////////////////////
//
//   InterfaceContainerComponent.cpp
//
//   Henk van Es
//
//   6/3/99
//
/////////////////////////////////////////////////////////



#include "InterfaceContainerComponent.h"
#include "Factory.h"

CInterfaceContainerComponent::CInterfaceContainerComponent() : m_nRefCnt(0)
{
	InterlockedIncrement(&g_cComponents);

	// Set the parent pointers in the nested classes
	m_objSDWInterfaceContainer.m_pParent = this;
	m_objSDWConnector.m_pParent = this;

	m_pInt = NULL;
	m_pMed = NULL;
}

CInterfaceContainerComponent::~CInterfaceContainerComponent()
{
	InterlockedDecrement(&g_cComponents);

	CFactory::CloseExe();	
}

// The IUnknown implementation
HRESULT __stdcall CInterfaceContainerComponent::QueryInterface(const IID & iid, void ** ppv)
{
	if ( iid == IID_IUnknown )
	{
		*ppv = this;
	}
	else
		if ( iid == IID_ISDWInterfaceContainer )
		{
			*ppv = &m_objSDWInterfaceContainer;
		}
		else 
			if ( iid == IID_ISDWConnector )
			{
				*ppv = &m_objSDWConnector;
			}
			else
			{
				/*

				// Handy to see what Interfaces were requested
				// but were not supported
				wchar_t *str;
				StringFromIID(iid, &str);

				char szIID [39];

				wcstombs(szIID, str, 39);

				MessageBox(NULL, szIID, "Error", MB_OK);
				CoTaskMemFree(str);

				*/

				// oops, no supported interface requested
				*ppv = NULL;
				return E_NOINTERFACE;
			}

		
		// Synchronize the refcount
		IUnknown * pUnk = (IUnknown *) *ppv;

		pUnk->AddRef();

		return S_OK;
}

ULONG __stdcall CInterfaceContainerComponent::AddRef()
{
	
	return InterlockedIncrement( &m_nRefCnt );
}

#include <iostream>

ULONG __stdcall CInterfaceContainerComponent::Release()
{
	if ( InterlockedDecrement( &m_nRefCnt ) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_nRefCnt;
}


// ISDWInterfaceContainer. Just simple passing functions

HRESULT __stdcall CInterfaceContainerComponent::SDWInterfaceContainer::SDWNotify(long h, long m)
{
	if ( m_pParent->m_pInt != NULL )
	{
		m_pParent->m_pInt->SDWNotify(h, m);
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT __stdcall CInterfaceContainerComponent::SDWInterfaceContainer::SDWInitialise()
{
	if ( m_pParent->m_pInt != NULL )
	{
		m_pParent->m_pInt->SDWInitialise();
		return S_OK;
	}
	else
		return E_FAIL;
}


HRESULT __stdcall CInterfaceContainerComponent::SDWInterfaceContainer::QueryInterface(const IID & iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG __stdcall CInterfaceContainerComponent::SDWInterfaceContainer::AddRef()
{
	return m_pParent->AddRef();
}

ULONG __stdcall CInterfaceContainerComponent::SDWInterfaceContainer::Release()
{
	return m_pParent->Release();
}

// ISDWConnector

HRESULT	__stdcall CInterfaceContainerComponent::SDWConnector::SDWSetUpperConnection(IUnknown * pUnk )
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWMediator, (void **) &m_pParent->m_pMed );
	
	return hr;
}

HRESULT	__stdcall CInterfaceContainerComponent::SDWConnector::SDWSetLowerConnection(IUnknown * pUnk )
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWInterface, (void **) &m_pParent->m_pInt);

	return hr;
}

HRESULT	__stdcall CInterfaceContainerComponent::SDWConnector::SDWKillConnection()
{
	HRESULT hr = S_OK;

	// is there a connecntion to the Interface
	if ( m_pParent->m_pInt )
	{
		ISDWConnector * pCon = NULL;
		
		// Query for the Connector Interface
		hr = m_pParent->m_pInt->QueryInterface(IID_ISDWConnector, (void **) &pCon );
		
		if (FAILED(hr))
			return E_FAIL;

		// Kill the connection of the Interface
		hr = pCon->SDWKillConnection();

		// release the Connector interface
		pCon->Release();

		if (FAILED(hr))
			return E_FAIL;

		// release the Interface interfacepointer
		m_pParent->m_pInt->Release();
	}

	// release the Mediator interface
	if ( m_pParent->m_pMed ) 
		m_pParent->m_pMed->Release();

	return hr;
}

HRESULT __stdcall CInterfaceContainerComponent::SDWConnector::QueryInterface(const IID & iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG __stdcall CInterfaceContainerComponent::SDWConnector::AddRef()
{
	return m_pParent->AddRef();
}

ULONG __stdcall CInterfaceContainerComponent::SDWConnector::Release()
{
	return m_pParent->Release();
}


