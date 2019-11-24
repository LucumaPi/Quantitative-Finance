/////////////////////////////////////////////////////////
//
//   ConCenComponent.cpp
//
//   Henk van Es
//
//   30-5-99
//
/////////////////////////////////////////////////////////


#include "ConCenComponent.h"
#include "Factory.h"
#include "stdio.h"

CConCenComponent::CConCenComponent() : m_nRefCnt(0)
{
	InterlockedIncrement(&g_cComponents);

	// Set the parent pointers in the nested classes
	m_objSDWControlCentreContainer.m_pParent = this;
	m_objSDWConnector.m_pParent = this;

	m_pMed = NULL;
	m_pCCen = NULL;
}

CConCenComponent::~CConCenComponent()
{
	InterlockedDecrement(&g_cComponents);

	CFactory::CloseExe();
}

// The IUnknown implementation
HRESULT __stdcall CConCenComponent::QueryInterface(const IID & iid, void ** ppv)
{
	if ( iid == IID_IUnknown )
	{
		*ppv = this;
	}
	else
		if ( iid == IID_ISDWControlCentreContainer )
		{
			*ppv = &m_objSDWControlCentreContainer;
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

ULONG __stdcall CConCenComponent::AddRef()
{
	return InterlockedIncrement( &m_nRefCnt );
}

ULONG __stdcall CConCenComponent::Release()
{
	if ( InterlockedDecrement( &m_nRefCnt ) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_nRefCnt;
}


// ISDWControlCentreContainer. Just simple passing functions

HRESULT __stdcall CConCenComponent::SDWControlCentreContainer::SDWEnable()
{
	if ( m_pParent->m_pMed != NULL )
	{
		m_pParent->m_pMed->SDWEnable();
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT __stdcall CConCenComponent::SDWControlCentreContainer::SDWDisable()
{
	if ( m_pParent->m_pMed != NULL )
	{
		m_pParent->m_pMed->SDWDisable();
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT __stdcall CConCenComponent::SDWControlCentreContainer::SDWInitialise(/* [in]*/ long h, /* [in]*/ long m)
{
	if ( m_pParent->m_pCCen != NULL )
	{
		m_pParent->m_pCCen->SDWInitialise(h,m);
		return S_OK;
	}
	else
		return E_FAIL;

}

HRESULT __stdcall CConCenComponent::SDWControlCentreContainer::SDWPush()
{
	if ( m_pParent->m_pCCen != NULL )
	{
		m_pParent->m_pCCen->SDWPush();
		return S_OK;
	}
	else
		return E_FAIL;

}

HRESULT __stdcall CConCenComponent::SDWControlCentreContainer::SDWNotify(/* [in]*/ long h, /* [in]*/ long m)
{
	if ( m_pParent->m_pMed != NULL )
	{
		m_pParent->m_pMed->SDWNotify(h,m);
		return S_OK;
	}
	else
		return E_FAIL;
}


HRESULT __stdcall CConCenComponent::SDWControlCentreContainer::QueryInterface(const IID & iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG __stdcall CConCenComponent::SDWControlCentreContainer::AddRef()
{
	return m_pParent->AddRef();
}

ULONG __stdcall CConCenComponent::SDWControlCentreContainer::Release()
{
	return m_pParent->Release();
}

// ISDWConnector

HRESULT	__stdcall CConCenComponent::SDWConnector::SDWSetUpperConnection(IUnknown * pUnk )
{
	HRESULT hr = E_FAIL;

	if (pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWMediator, (void**) &m_pParent->m_pMed );
	
	return hr;
}

HRESULT	__stdcall CConCenComponent::SDWConnector::SDWSetLowerConnection(IUnknown * pUnk )
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWControlCentre, (void **) & m_pParent->m_pCCen);
	
	return hr;
}

HRESULT __stdcall CConCenComponent::SDWConnector::SDWKillConnection()
{
	HRESULT hr = S_OK;

	// is there a connecntion to the ControlCentre
	if ( m_pParent->m_pCCen )
	{
		ISDWConnector * pCon = NULL;
		
		// Query for the Connector Interface
		hr = m_pParent->m_pCCen->QueryInterface(IID_ISDWConnector, (void **) &pCon );
		
		if (FAILED(hr))
			return E_FAIL;

		// Kill the connection of the ControlCentre
		hr = pCon->SDWKillConnection();

		// release the Connector interface
		pCon->Release();

		if (FAILED(hr))
			return E_FAIL;

		// release the ControlCentre interfacepointer
		m_pParent->m_pCCen->Release();
	}

	// release the Mediator interface
	if ( m_pParent->m_pMed ) 
		m_pParent->m_pMed->Release();

	return hr;
}

HRESULT __stdcall CConCenComponent::SDWConnector::QueryInterface(const IID & iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG __stdcall CConCenComponent::SDWConnector::AddRef()
{
	return m_pParent->AddRef();
}

ULONG __stdcall CConCenComponent::SDWConnector::Release()
{
	return m_pParent->Release();
}


