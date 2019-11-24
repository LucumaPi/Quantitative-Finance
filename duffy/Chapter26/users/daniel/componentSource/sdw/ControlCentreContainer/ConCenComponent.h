/////////////////////////////////////////////////////////
//
//   ConCenComponent.h
//
//   Henk van Es
//
//   30-5-99
//
/////////////////////////////////////////////////////////



#ifndef _CONCENCOMPONENT_H
#define _CONCENCOMPONENT_H

#include "ControlCentreContainer.h"
#include "SDWConnector.h"
#include "..\\Mediator\\Mediator.h"
#include "..\\ControlCentre\\ControlCentre.h"


static long g_cComponents = 0;
static long g_cServerLocks = 0;


// Friendly name of Component
const char g_szFriendlyName[]	=	"SDW ControlCentreContainer component";

// Version indepedend progID
const char g_szVerIndProgID[]	=	"SDW.ControlCentreContainer";

// ProgID
const char g_szProgID[]		=	"SDW.ControlCentreContainerComponent.1";


class CConCenComponent : public IUnknown
{
private:
	// The nested class that implements the ISDWControlCentreContainer interface
	class SDWControlCentreContainer : public ISDWControlCentreContainer
	{
	public:
		CConCenComponent * m_pParent;

		// ISDWControlCentreContainer
		HRESULT __stdcall SDWEnable();
		HRESULT __stdcall SDWDisable();
		HRESULT __stdcall SDWPush();
		HRESULT __stdcall SDWInitialise(/* [in]*/ long h, /* [in]*/ long m);
		HRESULT __stdcall SDWNotify(long h, long m);

		// IUnknown
		HRESULT __stdcall QueryInterface ( const IID& iid, void ** ppv);
		ULONG __stdcall AddRef();
		ULONG __stdcall Release();	


	} m_objSDWControlCentreContainer;

	// The nested class that implements the ISDWControlCentreContainer interface
	class SDWConnector	:	public ISDWConnector
	{
	public:
		CConCenComponent * m_pParent;

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
	ISDWControlCentre		* m_pCCen;

public:
	CConCenComponent();
	~CConCenComponent();

	// IUnknown
	HRESULT __stdcall QueryInterface ( const IID& iid, void ** ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();	

	friend class SDWControlCentreContainer;
	friend class SDWConnector;

};


#endif // _CONCENCOMPONENT_H
