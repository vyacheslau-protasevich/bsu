#include <iostream>
#include <windows.h>
#include <string>
#include <chrono>
#include <random>

void startChild(int* arr, int size) {
    std::string args = "";
    for (int i = 0; i < size; ++i) {
        args += " " + std::to_string(arr[i]);
    }
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    si.lpTitle = (char*)"LAB 2 OS";
    if (CreateProcess("Child.exe",
                      (char*)args.c_str(),
                      NULL, NULL,
                      FALSE,
                      CREATE_NEW_CONSOLE,
                      NULL, NULL,
                      &si, &pi)) {
        std::cout << "second ok";
    }
    else std::cout << "second not ok";

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
}

#ifndef TESTING
int main(int argc, char* argv[])
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disForArraySize(10, 20);
    std::uniform_int_distribution<> disForArrayNumbers(-100, 100);
    int n;
    std::cout << "Enter size of array: ";
    std::cin >> n;
    int* arr = new int[n];
    std::cout << "Enter elements of array: ";
    for (int i = 0; i < n; i++) {
        arr[i] = (disForArrayNumbers(gen) * 10);
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
    startChild(arr, n);
    std::string temp;
    std::getline(std::cin, temp);
    return 0;
}
#endif