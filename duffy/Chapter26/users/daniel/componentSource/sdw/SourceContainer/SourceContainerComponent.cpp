/////////////////////////////////////////////////////////
//
//   SourceContainerComponent.cpp
//
//   Henk van Es
//
//   29-5-99
//
/////////////////////////////////////////////////////////

#include "SourceContainerComponent.h"
#include "Factory.h"

CSourceContainerComponent::CSourceContainerComponent() : m_nRefCnt(0)
{
	InterlockedIncrement(&g_cComponents);

	// Set the parent pointers in the nested classes
	m_objSDWSourceContainer.m_pParent = this;
	m_objSDWConnector.m_pParent = this;

	m_pSrc = NULL;
	m_pMed = NULL;
}

CSourceContainerComponent::~CSourceContainerComponent()
{ 
	InterlockedDecrement(&g_cComponents);

	CFactory::CloseExe();	
}

// The IUnknown implementation
HRESULT __stdcall CSourceContainerComponent::QueryInterface(const IID & iid, void ** ppv)
{ 
	if ( iid == IID_IUnknown )
	{
		*ppv = this;
	}
	else
		if ( iid == IID_ISDWSourceContainer )
		{
			*ppv = &m_objSDWSourceContainer;
		}
		else 
			if ( iid == IID_ISDWConnector )
			{
				*ppv = &m_objSDWConnector;
			}
			else
			{
		
				// Handy to see what Interfaces were requested
				// but were not supported
				/*
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

ULONG __stdcall CSourceContainerComponent::AddRef()
{
	
	return InterlockedIncrement( &m_nRefCnt );
}

ULONG __stdcall CSourceContainerComponent::Release()
{
	if ( InterlockedDecrement( &m_nRefCnt ) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_nRefCnt;
}


// ISDWSourceContainer. Just simple passing functions

HRESULT __stdcall CSourceContainerComponent::SDWSourceContainer::SDWEnable()
{
	if ( m_pParent->m_pSrc != NULL )
	{
		m_pParent->m_pSrc->SDWEnable();
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT __stdcall CSourceContainerComponent::SDWSourceContainer::SDWDisable()
{
	if ( m_pParent->m_pSrc != NULL )
	{
		m_pParent->m_pSrc->SDWDisable();
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT __stdcall CSourceContainerComponent::SDWSourceContainer::SDWInitialise()
{
	if ( m_pParent->m_pSrc != NULL )
	{
		m_pParent->m_pSrc->SDWInitialise();
		return S_OK;
	}
	else
		return E_FAIL;

}

HRESULT __stdcall CSourceContainerComponent::SDWSourceContainer::SDWPush()
{
	if ( m_pParent->m_pMed != NULL )
	{

		m_pParent->m_pMed->SDWPush();
		return S_OK;
	}
	else
		return E_FAIL;

}

HRESULT __stdcall CSourceContainerComponent::SDWSourceContainer::QueryInterface(const IID & iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG __stdcall CSourceContainerComponent::SDWSourceContainer::AddRef()
{
	return m_pParent->AddRef();
}

ULONG __stdcall CSourceContainerComponent::SDWSourceContainer::Release()
{
	return m_pParent->Release();
}

// ISDWConnector

HRESULT	__stdcall CSourceContainerComponent::SDWConnector::SDWSetUpperConnection(IUnknown * pUnk )
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface( IID_ISDWMediator, (void **) &m_pParent->m_pMed );

	return hr;
}

HRESULT	__stdcall CSourceContainerComponent::SDWConnector::SDWSetLowerConnection(IUnknown * pUnk )
{
	HRESULT hr = E_FAIL;

	if ( pUnk != NULL )
		hr = pUnk->QueryInterface ( IID_ISDWSource, (void **) &m_pParent->m_pSrc );
	
	return hr;
}

HRESULT __stdcall CSourceContainerComponent::SDWConnector::SDWKillConnection()
{
	HRESULT hr = S_OK;

	// is there a connecntion to the Source
	if ( m_pParent->m_pSrc )
	{
		ISDWConnector * pCon = NULL;
		
		// Query for the Connector Interface
		hr = m_pParent->m_pSrc->QueryInterface(IID_ISDWConnector, (void **) &pCon );
		
		if (FAILED(hr))
			return E_FAIL;

		// Kill the connection of the Source
		hr = pCon->SDWKillConnection();

		// release the Connector interface
		pCon->Release();

		if (FAILED(hr))
			return E_FAIL;

		// release the Source interfacepointer
		m_pParent->m_pSrc->Release();
	}

	// release the SourceContainer interfacepointer
	if ( m_pParent->m_pMed ) 
		m_pParent->m_pMed->Release();

	return hr;
}

HRESULT __stdcall CSourceContainerComponent::SDWConnector::QueryInterface(const IID & iid, void ** ppv)
{
	return m_pParent->QueryInterface(iid, ppv);
}

ULONG __stdcall CSourceContainerComponent::SDWConnector::AddRef()
{
	return m_pParent->AddRef();
}

ULONG __stdcall CSourceContainerComponent::SDWConnector::Release()
{
	return m_pParent->Release();
}


