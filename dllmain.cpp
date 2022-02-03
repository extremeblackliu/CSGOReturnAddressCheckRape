// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include <Windows.h>

HMODULE g_module = nullptr;

#include "bootstrap/bootstrap.h"


void Thread()
{
    Hooks::Init(g_module);
    
    return;

}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        g_module = hModule;
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread, 0, 0, 0);
        break;
    }
    return TRUE;
}

