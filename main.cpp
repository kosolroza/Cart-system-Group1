#include <iostream>
#include "service/menu.hpp"
using namespace std;

//!!check cmake-build-debug to find user.txt!!

int main() {
    // Read users from file into the vector
    fileToVector();

    // Show menu to the user
    menu();

    return 0;
}
