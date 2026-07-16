#include <windows.h>

DWORD WINAPI MainThread(LPVOID lpParam)
{
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    // Mutable buffers (LPSTR)
    char exePath[] = "RAGEPluginHook.exe";
    char args[] = "-attach";

    CreateProcessA(
        exePath,
        args,
        nullptr,
        nullptr,
        FALSE,
        0,
        nullptr,
        nullptr,
        &si,
        &pi
    );

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    while (true)
    {
        Sleep(10);
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);
    }
    return TRUE;
}
