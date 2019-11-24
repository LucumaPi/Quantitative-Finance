/////////////////////////////////////////////////////////
//
//   Factory.h
//
//   Henk van Es
//
//   5/28/99
//
/////////////////////////////////////////////////////////


#ifndef _FACTORY_H
#define _FACTORY_H

#include <objbase.h>
#include "InterfaceContainerComponent.h"

class CFactory : public IUnknown
{
private:
	long m_nRefCnt;

public:
	CFactory();
	~CFactory();

	// IUnknown Interaface
	HRESULT __stdcall QueryInterface ( const IID& iid, void ** ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	// Derived class for the IFactory interface

	class Factory : public IClassFactory
	{
	public:
		CFactory * m_pParent;

		// IUnknown Interface
		HRESULT __stdcall QueryInterface ( const IID& iid, void ** ppv);
		ULONG __stdcall AddRef();
		ULONG __stdcall Release();

		// IClassFactory
		HRESULT __stdcall CreateInstance(	IUnknown * pUnkownOuter,
														const IID & iid,
														void ** ppv);
		HRESULT __stdcall LockServer(BOOL bLock);

	private:
		// these are al for creating the layer components
		
		// the class Id's we're going to create
		CLSID	clsidLayer1,
				clsidLayer2,
				clsidLayer3;

		HRESULT ReadFile();
		HRESULT CreateLayers(CInterfaceContainerComponent * pIntCon);

	} m_objFactory;

	static void CloseExe();
	static DWORD s_dwThreadID;
};

#endif // _FACTORY_H
