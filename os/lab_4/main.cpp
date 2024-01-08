#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Create Boss thread
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    if (CreateProcess("Boss.exe", NULL, NULL, NULL,
                      FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
    }
    else {
        std::cout << "not ok";
    }

    // Wait for the Boss thread to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close handle
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return 0;
}
