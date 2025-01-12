#include <iostream>
#include "../service/admin_service.hpp"
#include "../service/user_service.hpp"
using namespace std;
//CHORONAIY


void menu() {
    cout <<"\t\033[1m~ M A I N   M E N U ~" << endl;
    cout << "\033[4;33mWhich one are you?\033[0m" << endl;
    cout << "\033[33m1. Admin\n2. User\n3. Exit." << endl;
    int choice;
    cout<<"Enter your choice: \033[0m";
    cin >> choice;
    cout << "\n⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯\n\n";
    switch(choice) {
        case 1:
            adminLogin();
        break;
        case 2:
            askUserChoice();
        break;
        case 3:
            //
            cout << "Thank you for visiting!\n";
        exit(0);
    }
}

