//main.cpp
#include <iostream>
#include "view/ui.hpp"
#include <windows.h>
using namespace std;

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    User user;
    loadCartFromFile();
    fileToVector();
    showLoadingBar();
    menu();
    return 0;
}


