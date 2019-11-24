/////////////////////////////////////////////////////////
//
//   SourceContainerComponent.h
//
//   Henk van Es
//
//   5/28/99
//
/////////////////////////////////////////////////////////


#ifndef _SOURCECONTAINERCOMPONENT_H
#define _SOURCECONTAINERCOMPONENT_H

#include "SourceContainer.h"
#include "SDWConnector.h"
#include "..\\Mediator\\Mediator.h"
#include "..\\Source\\Source.h"


static long g_cComponents = 0;
static long g_cServerLocks = 0;


// Friendly name of Component
const char g_szFriendlyName[]	=	"SDW SourceContainer component";

// Version indepedend progID
const char g_szVerIndProgID[]	=	"SDW.SourceContainer";

// ProgID
const char g_szProgID[]		=	"SDW.SourceContainerComponent.1";


class CSourceContainerComponent : public IUnknown
{
private:
	// The nested class that implements the ISDWSourceContainer interface
	class SDWSourceContainer : public ISDWSourceContainer
	{
	public:
		CSourceContainerComponent * m_pParent;

		// ISDWSourceContainer
		HRESULT __stdcall SDWEnable();
		HRESULT __stdcall SDWDisable();
		HRESULT __stdcall SDWPush();
		HRESULT __stdcall SDWInitialise();

		// IUnknown
		HRESULT __stdcall QueryInterface ( const IID& iid, void ** ppv);
		ULONG __stdcall AddRef();
		ULONG __stdcall Release();	


	} m_objSDWSourceContainer;

	// The nested class that implements the ISDWSourceContainer interface
	class SDWConnector	:	public ISDWConnector
	{
	public:
		CSourceContainerComponent * m_pParent;

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

	ISDWMediator	* m_pMed;
	ISDWSource		* m_pSrc;

public:
	CSourceContainerComponent();
	~CSourceContainerComponent();

	// IUnknown
	HRESULT __stdcall QueryInterface ( const IID& iid, void ** ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();	

	friend class SDWSourceContainer;
	friend class SDWConnector;

};


#endif // _SOURCECONTAINERCOMPONENT_H
