//===============================================================================================//
// This is a stub for the actuall functionality of the DLL.
//===============================================================================================//
#include "ReflectiveLoader.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>


// Note: REFLECTIVEDLLINJECTION_VIA_LOADREMOTELIBRARYR and REFLECTIVEDLLINJECTION_CUSTOM_DLLMAIN are
// defined in the project properties (Properties->C++->Preprocessor) so as we can specify our own 
// DllMain and use the LoadRemoteLibraryR() API to inject this DLL.

// You can use this value as a pseudo hinstDLL value (defined and set via ReflectiveLoader.c)
extern HINSTANCE hAppInstance;


BOOL GetTextFromClipboard()
{
	if (OpenClipboard(NULL))
	{
		std::string res;
		HGLOBAL hMem = ::GetClipboardData(CF_TEXT);
		if (NULL != hMem)
		{
			char* lpStr = (char*)::GlobalLock(hMem);
			if (NULL != lpStr)
			{
				res.append(lpStr);
				GlobalUnlock(hMem);
			}
		}
		std::cout << res << std::endl;
		::CloseClipboard();
		return TRUE;
	}
	return FALSE;
}
//===============================================================================================//
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved)
{
	BOOL bReturnValue = TRUE;

	switch (dwReason)
	{
	case DLL_QUERY_HMODULE:
		if (lpReserved != NULL)
			*(HMODULE*)lpReserved = hAppInstance;
		break;
	case DLL_PROCESS_ATTACH:
		hAppInstance = hinstDLL;
		GetTextFromClipboard();
		break;
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return bReturnValue;
}
