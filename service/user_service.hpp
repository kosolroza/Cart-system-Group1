//user_service.hpp inside folder serivce
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <conio.h>
#include "../repository/product_repo.hpp"
#include "../service/fileio.hpp"



using namespace std;
User user;
void askUserChoice();
void loginSuccessful();
void saveUsersToFile();
void fileToVector();
void enterDetails();
void signup();
void login();
void logout();
void adminLogin();
void admin();
void menu();
void users();


string inputPassword() {
        string password;
        char ch;
        while ((ch = _getch()) != '\r') {  // Enter key stops input
            if (ch == '\b') {  // Handle backspace
                if (!password.empty()) {
                    cout << "\b \b";  // Erase character from console
                    password.pop_back();
                }
            } else {
                password += ch;
                cout << '*';  // Show '*' for each character
            }
        }
        cout << endl;
        return password;
    }


void loginSuccessful (const string & name) {
    cout << "\n\t\t\t\t== == == == == == == == == == == ==\n";
    cout << "\n\t\t\t\t\033[1;36m〈 ♥︎ WELCOME " << name <<". Enjoy shopping ♥︎ 〉\033[0m\n";
    cout << "\n\t\t\t\t== == == == == == == == == == == ==\n\n";
}

// Displaying user info
User getUserById(const int id){
    for( User& i: userRepository){ //use const so that it is safe, values can't be modifies as you are only going into repo to read and retrieve
        if(i.getId()==id){ //NEED TO USE GETTER METHOD
            return i;
        }
    }
    return User();
}
void enterDetails(User& user) { //need to pass by reference or else changes will only affect user in enter details, not sign up and log in
    string email, password;
    
    // Input for Email
    cout << "\033[1;33m✩ Enter your Email: \033[0m";
    cin >> email;
    
    // Input for Password
    cout << "\033[1;33m✩ Enter your Password: \033[0m";
    password = inputPassword();
    
    user.setEmail(email);
    user.setPassword(password);
}

// Sign up
void signup (){
    // Stylish "USER LOGIN" header with stars and key emoji, in red color
    cout << "\033[1;35m" << R"(
██╗   ██╗███████╗███████╗██████╗   ███████╗██╗ ██████╗ ███╗   ██╗ ██╗   ██╗██████╗
██║   ██║██╔════╝██╔════╝██╔══██╗  ██╔════╝██║██╔════╝ ████╗  ██║ ██║   ██║██╔══██╗
██║   ██║███████╗█████╗  ██████╔╝  ███████╗██║██║  ███╗██╔██╗ ██║ ██║   ██║██████╔╝
██║   ██║╚════██║██╔══╝  ██╔══██╗  ╚════██║██║██║   ██║██║╚██╗██║ ██║   ██║██╔═══╝
╚██████╔╝███████║███████╗██║  ██║  ███████║██║╚██████╔╝██║ ╚████║ ╚██████╔╝██║
 ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝  ╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝  ╚═════╝ ╚═╝
    )" << "\033[0m\n";
    cout << "\t\033[1;34m╔════════════════════════ ACCESS PORTAL ════════════════════════╗\n";
    cout << "\t║                                                               ║\n";
    cout << "\t║                      🔐 USER SIGN_UP 🔐                       ║\n";
    cout << "\t║                                                               ║\n";
    cout << "\t╚═══════════════════════════════════════════════════════════════╝\033[0m\n\n";
    enterDetails(user);

    // Ensure the vector is up-to-date with the file
    fileToVector();
    if(user.getEmail().length() < 10 || user.getEmail().substr(user.getEmail().length() - 10 )!= "@gmail.com"){
        cout << "\033[1;31mError: Only emails ending with '@gmail.com' are allowed.\033[0m\n";
        signup();
        return;
    }

    //check if user already existed
    for (User &i: userRepository) {
        if(i.getEmail() == user.getEmail()) {
            cout<< "\033[31m!! User with this email " << user.getEmail() <<" already exists !!"<<endl;
            cout << "\033[1mDo you want to LOG IN instead? (Y/N) \033[0m";
            char yesno;
            cin >> yesno;
            if(yesno=='Y' || yesno=='y') {
                login();
                return; //Exit the function and return to the main menu or previous step
            }
            signup();
            return;
        }
    }
    // Write the new user directly to the file
    saveUsersToFile();
    loginSuccessful(user.getEmail());
    askUserChoice();
}

void showLoadingLogin() {
    cout << "\n\033[1;35mVerifying credentials";
    for (int i = 0; i < 3; i++) {
        Sleep(300);
        cout << ".";
    }
    cout << "\n\n";
    
    cout << "\033[1;32mLoading: [";
    for (int i = 0; i <= 25; i++) {
        cout << "█";
        cout.flush();
        Sleep(50);
    }
    cout << "] 100%\033[0m\n\n";
}

void login() {
    system("cls");
    cout << "\033[1;35m" << R"(
██╗   ██╗███████╗███████╗██████╗   ██╗      ██████╗  ██████╗ ██╗███╗   ██╗
██║   ██║██╔════╝██╔════╝██╔══██╗  ██║     ██╔═══██╗██╔════╝ ██║████╗  ██║
██║   ██║███████╗█████╗  ██████╔╝  ██║     ██║   ██║██║  ███╗██║██╔██╗ ██║
██║   ██║╚════██║██╔══╝  ██╔══██╗  ██║     ██║   ██║██║   ██║██║██║╚██╗██║
╚██████╔╝███████║███████╗██║  ██║  ███████╗╚██████╔╝╚██████╔╝██║██║ ╚████║
 ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝  ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝╚═╝  ╚═══╝
    )" << "\033[0m\n";

    cout << "\t\033[1;34m╔════════════════════════ ACCESS PORTAL ════════════════════════╗\n";
    cout << "\t║                                                               ║\n";
    cout << "\t║                       🔐 USER LOGIN 🔐                        ║\n";
    cout << "\t║                                                               ║\n";
    cout << "\t╚═══════════════════════════════════════════════════════════════╝\033[0m\n\n";

    enterDetails(user);
    fileToVector();

    for (User &i : userRepository) {
        if (i.getEmail() == user.getEmail()) {
            if (i.getPassword() == user.getPassword()) {
                showLoadingLogin();  // Add loading animation before success message
                cout << "\033[1;32m" << R"(
    ╔═══════════════════════════════════════════════════════════════╗
    ║                    ✅ Login Successful! ✅                    ║
    ╚═══════════════════════════════════════════════════════════════╝
                )" << "\033[0m\n";
                users();
                return;
            } else {
                cout << "\033[1;31m" << R"(
    ╔═══════════════════════════════════════════════════════════════╗
    ║                 ❌ Invalid email or password! ❌              ║
    ╚═══════════════════════════════════════════════════════════════╝
                )" << "\033[0m\n";
                login();
                return;
            }
        }
    }

    cout << "\033[1;33m❓ User not found! Would you like to sign up? (Y/N): \033[0m";
    char choice;
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        signup();
    } else {
        login();
    }
}