#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    cout << "Enter the length of the array: ";
    int arrayLength;
    cin >> arrayLength;

    // Dynamic allocation of array
    char* str = new char[arrayLength];

    cout << "Enter the array elements: ";
    for (int i = 0; i < arrayLength; ++i) {
        cin >> str[i];
    }
    cout << "\nInputed array: ";
    for (int i = 0; i < arrayLength; ++i) {
        cout << str[i] << " ";
    }
    cout << endl;

    HANDLE hWritePipe, hReadPipe;


    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    // Create pipes
    if (!CreatePipe(&hReadPipe, &hWritePipe, &saAttr, 0)) {
        cout << "Create pipe failed" << endl;
        return GetLastError();
    }

    DWORD dwBytesWrite;
    // Write array data to the pipe
    if (!WriteFile(hWritePipe, &arrayLength, sizeof(int), &dwBytesWrite, NULL)) {
        cout << "Write of length failed\n" << GetLastError();
        return GetLastError();
    }


    if (!WriteFile(hWritePipe, str, arrayLength * sizeof(char), &dwBytesWrite, NULL)) {
        cout << "Write of array failed\n" << GetLastError();
        return GetLastError();
    }


    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char lpszComLine[80];
    wsprintf(lpszComLine, "%p %p", hWritePipe, hReadPipe);

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);

    // Create Consume process
    if (!CreateProcess("Consume.exe", lpszComLine,
                       NULL,NULL, TRUE,
                       CREATE_NEW_CONSOLE,
                       NULL, NULL,
                       &si, &pi))
    {
        cout << "Consume.exe was not launched.\n";
        return GetLastError();
    }


    WaitForSingleObject(pi.hProcess, INFINITE);

    int new_size;
    DWORD byteRwad;
    if (!ReadFile(hReadPipe, &new_size, sizeof(int), &byteRwad, NULL))
    {
        cout << "New size read is failed " << endl;
        return GetLastError();
    }
    char* str1 = new char[new_size];
    if (!ReadFile(hReadPipe, str1, sizeof(char) * new_size, &byteRwad, NULL))
    {
        cout << "New array read is failed " << endl;
        return GetLastError();
    }
    cout << "\nArray of punctuation mark:\n";
    if (str1[0] == 'n')
        cout << "No punctiation marks found\n";
    else {
        for (int i = 0; i < new_size; i++)
        {
            cout << str1[i] << " ";
        }
    }

    CloseHandle(hReadPipe);
    CloseHandle(hWritePipe);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Release the dynamically allocated memory
    delete[] str;
    delete[] str1;

    return 0;
}