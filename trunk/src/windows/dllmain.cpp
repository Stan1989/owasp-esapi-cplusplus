// dllmain.cpp : Defines the entry point for the DLL application.

#include <windows.h>

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  dwReason, LPVOID lpReserved )
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
