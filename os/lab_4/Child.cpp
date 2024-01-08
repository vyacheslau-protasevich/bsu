#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

int processChildMessage(DWORD message, int messageNum) {
    switch (message) {
            case 0:
                cout << "message C\n";
                messageNum--;
                break;
            case 1:
                cout << "message D\n";
                messageNum--;
                break;
        }
    return messageNum;
}

#ifndef TESTING1
int main(int argc, char* argv[]){
    HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ParentSemaphore");
    HANDLE ParentEvents[4];
    HANDLE BossEvents[4];

    for (int i = 0; i < 2; i++)
    {
        BossEvents[i] = OpenEvent(EVENT_ALL_ACCESS, FALSE, ("BossEvents" + to_string(i)).c_str());
        if (BossEvents[i] == NULL)
        {
            return GetLastError();
        }
    }

    ParentEvents[3] = OpenEvent(EVENT_MODIFY_STATE, FALSE, "ChildEndEvent");
    if (ParentEvents[3] == NULL || hSemaphore == NULL)
    {
        return GetLastError();
    }
    int massageNum = atoi(argv[0]);
    WaitForSingleObject(hSemaphore, INFINITE);
    cout << "active \n";

    while (massageNum > 0)
    {
        DWORD message = WaitForMultipleObjects(2, BossEvents, FALSE, INFINITE);
        massageNum = processChildMessage(message, massageNum);
    }
    ReleaseSemaphore(hSemaphore, 1, NULL);
    string temp;
    getline(cin, temp);
    PulseEvent(ParentEvents[3]);
    CloseHandle(hSemaphore);
    for (int i = 0; i < 2; i++)
    {
        CloseHandle(BossEvents[i]);
    }
    CloseHandle(ParentEvents[3]);
    return 0;
}
#endif
