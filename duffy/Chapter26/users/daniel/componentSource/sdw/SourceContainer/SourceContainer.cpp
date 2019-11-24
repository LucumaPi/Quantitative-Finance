/////////////////////////////////////////////////////////
//
//   SourceContainer.cpp
//
//   Henk van Es
//
//   5/28/99
//
/////////////////////////////////////////////////////////

#include "Factory.h"
#include <windows.h>
#include <objbase.h>
#include "..\\Registry.h"

extern "C" CLSID CLSID_SDWSourceContainer;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	bool bExit = false;

	CoInitialize(NULL);

	// To know which thread has to receive the right message when closing
	CFactory::s_dwThreadID = ::GetCurrentThreadId();
		

	// Read the command line.
	// This commandline routine is straight from the Inside COM book

	char szTokens[] = "-/" ;

	char* szToken = strtok(lpCmdLine, szTokens) ; 
	while (szToken != NULL)
	{
		if (_stricmp(szToken, "UnregServer") == 0)
		{
			UnregisterServer(	CLSID_SDWSourceContainer,
									g_szVerIndProgID,
									g_szProgID) ;

			// We are done, so exit.
			bExit = TRUE ;
		}
		else if (_stricmp(szToken, "RegServer") == 0)
		{
			// thanks to the _OUTPROC_SERVER_ define in the settings
			// the Registerserver() function is creating a LocalServer32 key
			// instead of InprocServer32
			RegisterServer(	hInstance,
									CLSID_SDWSourceContainer, 
									g_szFriendlyName,
									g_szVerIndProgID,
									g_szProgID ) ;

			// We are done, so exit.
			bExit = TRUE ;
		}
		szToken = strtok(NULL, szTokens) ;
	}

	// Create the factory
	CFactory * pIFact = new CFactory();

	// A cookie to store the reg info
	DWORD dwRegCookie;

	// register the Factory, so COM knows how to create an SDWSourceContainer
	CoRegisterClassObject(	CLSID_SDWSourceContainer,
									static_cast<IUnknown*> (pIFact),
									CLSCTX_LOCAL_SERVER,
									REGCLS_SINGLEUSE,
									&dwRegCookie	);


	// start an messagepump
	if ( !bExit )
	{
		MSG msg ;
		// GetMessage only gives back a 0 if WM_QUIT is send
		while (::GetMessage(&msg, 0, 0, 0))
		{
			::DispatchMessage(&msg) ;
		}
	}
	// release the factory
	pIFact->Release();

	// Unregister the ClassFactory
	CoRevokeClassObject(dwRegCookie);


	CoUninitialize();
	return 0;
}


