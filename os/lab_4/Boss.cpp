#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;


int main(int argc, char* argv[]){
    // Initialize synchronization objects
    HANDLE hSemaphore = CreateSemaphore(NULL, 5, 5, "ParentSemaphore");
    if (hSemaphore == NULL) {
        return GetLastError();
    }
    HANDLE ParentEvents[4];
    for (int i = 0; i < 2; ++i) {
        ParentEvents[i] = CreateEvent(NULL, FALSE, FALSE, ("ParentEvent" + to_string(i)).c_str());
        if (ParentEvents[i] == NULL) {
            return GetLastError();
        }
    }
    ParentEvents[2] = CreateEvent(NULL, FALSE, FALSE, "ParentEndEvent");
    ParentEvents[3] = CreateEvent(NULL, FALSE, FALSE, "ChildEndEvent");

    HANDLE BossEvents[2];
    for (int i = 0; i < 2; ++i) {
        BossEvents[i] = CreateEvent(NULL, FALSE, FALSE, ("BossEvents" + to_string(i)).c_str());
        if (ParentEvents[i] == NULL) {
            cout << "eeeeeeee";
            return GetLastError();
        }
    }


    // User input
    int numParentProcesses, numChildProcesses, numMessages;
    std::cout << "Enter the number of Parent processes: ";
    std::cin >> numParentProcesses;


    do {
        std::cout << "Enter the number of Child processes (<=4): ";
        std::cin >> numChildProcesses;
    } while(numChildProcesses > 4 or numChildProcesses< 1);

    std::cout << "Enter the number of messages to be sent and received: ";
    std::cin >> numMessages;

    STARTUPINFO si;
    PROCESS_INFORMATION* parent_pi = new PROCESS_INFORMATION[numParentProcesses];
    PROCESS_INFORMATION* child_pi = new PROCESS_INFORMATION[numChildProcesses];
    string parentInfo = to_string(numMessages);

    for (int i = 0; i < numChildProcesses; ++i) {
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        if (CreateProcess("Child.exe", (char*)parentInfo.c_str(), NULL, NULL,
                          FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &child_pi[i])) {
        }
        else {
            std::cout << "not ok";
        }

    }

    for (int i = 0; i < numParentProcesses; ++i) {
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        if (CreateProcess("Parent.exe", (char*)parentInfo.c_str(), NULL, NULL,
                          FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &parent_pi[i])) {
        }
        else {
            std::cout << "not ok";
        }
    }




    int parent_count = numParentProcesses;
    int child_count = numChildProcesses;
    while (parent_count or child_count) {
        // Simulate receiving message from user
        DWORD message1 = WaitForMultipleObjects(4, ParentEvents, FALSE, INFINITE);
        switch (message1) {
            case 0:
                cout << "Message C\n";
                PulseEvent(BossEvents[0]);
                break;
            case 1:
                cout << "Message D\n";
                PulseEvent(BossEvents[1]);
                break;
            case 2:
                cout << "Parent Process end\n";
                parent_count--;
                break;
            case 3:
                cout << "Child Process end\n";
                child_count--;
                break;
        }
    }

    // Close synchronization objects
    CloseHandle(hSemaphore);

    // Close handles
    for (int i = 0; i < numParentProcesses; ++i) {
        CloseHandle(parent_pi[i].hProcess);
        CloseHandle(parent_pi[i].hThread);
    }

    for (int i = 0; i < numChildProcesses; ++i) {
        CloseHandle(child_pi[i].hProcess);
        CloseHandle(child_pi[i].hThread);
    }

    for (int i = 0; i < 4; ++i) {
        CloseHandle(ParentEvents[i]);
    }

    for (int i = 0; i < 2; ++i) {
        CloseHandle(BossEvents);
    }

    return 0;
}