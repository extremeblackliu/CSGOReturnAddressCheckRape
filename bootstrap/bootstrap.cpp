#include "bootstrap.h"
#include "../minhook/include/MinHook.h"

namespace Hooks
{

	void Init(HMODULE mod)
	{
		while (!GetModuleHandleA("serverbrowser.dll"))
		{
			Sleep(2000);
		}
		//55 8B EC 56 8B F1 33 C0 57 8B 7D 08 8B 8E ? ? ? ? 85 C9 7E - client.dll + engine.dll + studiorender.dll
		HMODULE client, engine, studiorender, materialsystem;
		client = GetModuleHandleA("client.dll");
		engine = GetModuleHandleA("engine.dll");
		studiorender = GetModuleHandleA("studiorender.dll");
		materialsystem = GetModuleHandleA("materialsystem.dll");
		
		const char* sig = "55 8B EC 56 8B F1 33 C0 57 8B 7D 08 8B 8E ? ? ? ? 85 C9 7E";

		void* result = Utils::PatternScan(client, sig);
		void* result1 = Utils::PatternScan(engine, sig);
		void* result2 = Utils::PatternScan(studiorender, sig);
		void* result3 = Utils::PatternScan(materialsystem, sig);
		if (!result || !result1 || !result2 || !result3)
		{
			MessageBoxA(0, "Bypass was failed", "RACP", 0);
			FreeLibraryAndExitThread(mod, 0);
			return;
		}
		MH_Initialize();
		void* orig = nullptr;
		MH_CreateHook(result, &hk_VerifyReturnAddress, &orig);
		MH_CreateHook(result1, &hk_VerifyReturnAddress, &orig);
		MH_CreateHook(result2, &hk_VerifyReturnAddress, &orig);
		MH_CreateHook(result3, &hk_VerifyReturnAddress, &orig);
		MH_EnableHook(MH_ALL_HOOKS);
	}

	bool __fastcall hk_VerifyReturnAddress(void* ecx, void* rdx,const char* modulename)
	{
		return true;
	}


}
