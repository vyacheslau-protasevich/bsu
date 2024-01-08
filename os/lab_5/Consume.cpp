#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>

using namespace std;

std::vector<char> identifyPunctuationMarks(char* inputArray, int length) {
    std::vector<char> res;
    for (int i = 0; i < length; ++i) {
        if (ispunct(inputArray[i])) {
            res.push_back(inputArray[i]);
        }
    }
    return res;
}

#ifndef TESTING
int main(int argc, char* argv[]) {
    // Retrieve handles and array length from command line arguments
    HANDLE hReadPipe, hWritePipe;

    sscanf(argv[0], "%p", &hWritePipe);
    sscanf(argv[1], "%p", &hReadPipe);
    cout << "hReadPipe: " << hReadPipe << endl;
    int arl;

    DWORD dwBytesWrite, dwBytesRead;

    // Read array data from the pipe
    if (!ReadFile(hReadPipe, &arl, sizeof(int), &dwBytesRead, NULL)) {
        cout << "array  read is failed " << endl;
        return GetLastError();
    }

    // Dynamic allocation of array
    char* str = new char[arl];
    if (!ReadFile(hReadPipe, str, sizeof(char) * arl, &dwBytesRead, NULL))
    {
        cout << "array  read is failed " << endl;
        return GetLastError();
    }

    cout << "Received Array from Server:" << endl;
    for (int i = 0; i < arl; ++i) {
        cout << str[i] << " ";
    }
    cout << endl;

    vector<char> res = identifyPunctuationMarks(str, arl);


    // Display and pass back the modified array
    cout << "Identified Punctuation Marks:" << endl;
    int new_size = res.size();
    char* str1;

    if (new_size == 0){
        str1 = new char[1];
        cout << "No punctuation marks found";
        new_size = 1;
        str1[0] = 'n';
    } else {
        str1 = new char[new_size];
        for (int i = 0; i < new_size; ++i) {
            cout << res[i] << " ";
            str1[i] = res[i];
        }
    }
    cout << endl;

//     Pass the modified array back to the server
    if (!WriteFile(hWritePipe, &new_size, sizeof(int), &dwBytesWrite, NULL)) {
        cout << "Write of new size failed\n";
        return GetLastError();
    }
    if (!WriteFile(hWritePipe, str1, new_size * sizeof(char), &dwBytesWrite, NULL)) {
        cout << "Write of new array failed\n";
        return GetLastError();
    }

    _cprintf("\nTo exit press any key ");
    _getch();

    delete[] str;
    delete[] str1;
    CloseHandle(hWritePipe);
    CloseHandle(hReadPipe);

    return 0;
}
#endif