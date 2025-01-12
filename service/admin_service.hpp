#include <iostream>
using namespace std;
//CHORONAIY

// Declaration
void adminLogin();
void admin();
void menu();

void adminLogin() {
    string email, password;
    cout <<"\033[1;35m╭⁺ ✿ . ⁺ ⵌ ⁺ . ⿻ . ⁺ ⵌ ⁺ . ✿ ⁺╮\n"; //bold magenta
    cout <<"✿ ✿ ✿\033[1;36m SHOPPING CART SYSTEM \033[1;35m✿ ✿ ✿\n";
    cout <<"╰⁺ ✿ . ⁺ ⵌ ⁺ . ⿻ . ⁺ ⵌ ⁺ . ✿ ⁺╯\033[0m"<<endl;
    cout<<"\t\033[1;33m  ❒❒❒ Admin Log In ❒❒❒\033[0m\n"; //yellow

    cout << "✩ Enter email: ";
    cin >> email;
    cout << "✩ Enter password: ";
    cin >> password; //admin@gmail.com admin123

    if (email == "admin@gmail.com" && password == "admin123") {
        cout << "\t\033[33m   Log-in Successful.\033[0m";
        admin();
    }
    else {
        cout << "\nInvalid email or password.\n";
    }
}

void admin() {
    int choice;
    do {
        cout<<"\n\n  ⎽⎽ ⎽⎽ ⎽⎽ ⎽⎽ ⎽⎽ ⎽⎽ ⎽⎽ ⎽⎽ ⎽⎽ ⎽⎽ ";
        cout<<"\n⎧\t  \033[1;4;36mAdministrator's menu\033[0m\t\t⎫";
        cout<<"\n|  1. Add the product    \t\t|";
        cout<<"\n|                        \t\t|";
        cout<<"\n|  2. Edit the product   \t\t|";
        cout<<"\n|                        \t\t|";
        cout<<"\n|  3. Remove the product \t\t|";
        cout<<"\n|                        \t\t|";
        cout<<"\n|  4. List all products  \t\t|";
        cout<<"\n|                        \t\t|";
        cout<<"\n⎩  5. Return to menu     \t\t⎭";
        cout<<"\n  ⎺⎺ ⎺⎺ ⎺⎺ ⎺⎺ ⎺⎺ ⎺⎺ ⎺⎺ ⎺⎺ ⎺⎺ ⎺⎺"<<endl;
        cout <<"\033[33mEnter your choice: \033[0m";
        cin>>choice;
        cout << "\n⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯\n\n";
        switch (choice) {
            case 1:
                //addProduct();
                break;
            case 2:
                //editProduct();
                break;
            case 3:
                //removeProduct();
                break;
            case 4:
                //listProducts();
                break;
            case 5:
                menu();
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

