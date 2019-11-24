/////////////////////////////////////////////////////////
//
//   InterfaceContainerComponent.h
//
//   Henk van Es
//
//   5/28/99
//
/////////////////////////////////////////////////////////


#ifndef _INTERFACECONTAINERCOMPONENT_H
#define _INTERFACECONTAINERCOMPONENT_H


#include "InterfaceContainer.h"
#include "SDWConnector.h"
#include "..\\Mediator\\Mediator.h"
#include "..\\Interface\\Interface.h"


static long g_cComponents = 0;
static long g_cServerLocks = 0;


// Friendly name of Component
const char g_szFriendlyName[]	=	"SDW InterfaceContainer component";

// Version indepedend progID
const char g_szVerIndProgID[]	=	"SDW.InterfaceContainer";

// ProgID
const char g_szProgID[]		=	"SDW.InterfaceContainerComponent.1";


class CInterfaceContainerComponent : public IUnknown
{
private:
	// The nested class that implements the ISDWInterfaceContainer interface
	class SDWInterfaceContainer : public ISDWInterfaceContainer
	{
	public:
		CInterfaceContainerComponent * m_pParent;

		// ISDWInterfaceContainer
		HRESULT __stdcall SDWNotify(/*[in]*/ long h, /*[in]*/ long m);
		HRESULT __stdcall SDWInitialise();

		// IUnknown
		HRESULT __stdcall QueryInterface ( const IID& iid, void ** ppv);
		ULONG __stdcall AddRef();
		ULONG __stdcall Release();	


	} m_objSDWInterfaceContainer;

	// The nested class that implements the ISDWInterfaceContainer interface
	class SDWConnector	:	public ISDWConnector
	{
	public:
		CInterfaceContainerComponent * m_pParent;

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
	ISDWInterface		* m_pInt;

public:
	CInterfaceContainerComponent();
	~CInterfaceContainerComponent();

	// IUnknown
	HRESULT __stdcall QueryInterface ( const IID& iid, void ** ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();	

	friend class SDWInterfaceContainer;
	friend class SDWConnector;

};


#endif // _INTERFACECONTAINERCOMPONENT_H
