#include <iostream>
#include <windows.h>
#include "MyDictionary.h"

int main()
{
    SetConsoleOutputCP(65001);  // output encoding
    SetConsoleCP(65001);        // input encoding
    int secim2;
    int* secim2_p = &secim2;
    MyDictionary mydict;
    mydict.word_of_day();
    do
    {
        mydict.secim();
        std::cout << "Devam etmek için 1'e basınız: ";
        std::cin >> *secim2_p;
    }
    while (secim2 == 1);
}
