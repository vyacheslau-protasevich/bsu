#include <iostream>
#include <windows.h>
#include <string>

void processNumber(int num) {
    if (num < 0 && num % 6 == 0) {
        std::cout << num << ' ';
    }
}
#ifndef TESTING1
int main(int argc, char* argv[])
{
    std::cout << "Negative number divided by 6: ";
    for (int i = 0; i < argc; ++i) {
        int num = atoi(argv[i]);
        processNumber(num);
        Sleep(5);
    }
    std::string temp;
    std::getline(std::cin, temp);
    return 0;
}
#endif