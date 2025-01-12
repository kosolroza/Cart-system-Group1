#include "../repository/user_repo.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
//CHORONAIY

// Declarations. This way, the compiler knows about these functions when they are used, or else it wouldn't work as they are used within each other.
User user;
void askUserChoice();
void loginSuccessful();

void saveUsersToFile();
void fileToVector();

void enterDetails();
void signup();
void login();
void logout();

//Ask user if they want to log in or sign up
void askUserChoice(){
    system("clear");
    cout <<"\033[1;35m╭⁺ ✿ . ⁺ ⵌ ⁺ . ⿻ . ⁺ ⵌ ⁺ . ✿ ⁺╮\n"; //bold magenta
    cout <<"✿ ✿ ✿\033[1;36m SHOPPING CART SYSTEM \033[1;35m✿ ✿ ✿\n";
    cout <<"╰⁺ ✿ . ⁺ ⵌ ⁺ . ⿻ . ⁺ ⵌ ⁺ . ✿ ⁺╯"<<endl;
    cout << "|\033[0m\033[34m1. Sign Up                    \033[35m|" << endl; //blue
    cout << "|\033[34m2. Log in                     \033[35m|" << endl;
    cout << "|\033[34m3. Back to menu               \033[35m|" << endl;
    cout<<"╰⁺ ✿ . ⁺ ⵌ ⁺ . ⿻ . ⁺ ⵌ ⁺ . ✿ ⁺╯\033[0m"<<endl;

    int userChoice;
    cout << "\nEnter your choice: ";
    cin >> userChoice;
    cout << "\n⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯ ⎯\n";

    switch(userChoice) {
        case 1:
            system("clear");
        signup();
        break;
        case 2:
            system("clear");
        login();
        break;
        case 3:
            system("clear");
        cout << "\n";
        menu();
        break;
        default:
            cout<<"\033[1;31mInvalid input!!\033[0m"<<endl;
    }
};

// Successful entry
void loginSuccessful (const string & name) {
    cout << "\n== == == == == == == == == == == ==\n";
    cout << "\n\033[1;36m〈 ♥︎ WELCOME " << name <<". Enjoy shopping ♥︎ 〉\033[0m\n";
    cout << "\n== == == == == == == == == == == ==\n\n";
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

// Write the new user directly to the file
void saveUsersToFile() {
    ofstream outFile("user.txt", ios::app);
    if (!outFile) {
        cerr << "\033[31mCould not open user.txt for appending.\033[0m\n";
        return;
    }
    outFile << user.getId() << " " << user.getName() << " " << user.getEmail() << " " << user.getPassword() << endl;
    outFile.close();

    // Reload the vector to reflect the new user
    fileToVector();

    cout << "\033[33m~ User with ID " << user.getId() << " signed up successfully.\033[0m\n";
}

//read users from file and push to vector
void fileToVector() {
    ifstream inFile("user.txt");
    if (!inFile) {
        cerr << "Could not open user.txt. Creating a new file." << endl;

        // Create the file if it doesn't exist
        ofstream outFile("user.txt");
        if (!outFile) {
            cerr << "Failed to create user.txt. Exiting..." << endl;
            exit(1); // Exit if file creation fails
        }
        outFile.close();
        return; // Exit this function since there's no data to read
    }

    string line;
    userRepository.clear(); // Ensure the vector is empty before reloading
    while (getline(inFile, line)) {
        istringstream iss(line);
        User user;
        int id;
        string name, email, password;

        // Extract user details from the line
        iss >> id >> name >> email >> password;
        user.setId(id);
        user.setName(name);
        user.setEmail(email);
        user.setPassword(password);

        userRepository.push_back(user);
    }
    inFile.close();
}

// Asking user's details
void enterDetails(User& user) { //need to pass by reference or else changes will only affect user in enter details, not sign up and log in
    int id;
    string name, email, password;
    cout<<"✩ Enter ID: ";
    cin>>id;
    cout<<"✩ Enter Username: ";
    cin.ignore();
    cin.clear();
    getline(cin, name);
    cout<<"✩ Enter Email: ";
    cin>>email;
    cout<<"✩ Enter Password: ";
    cin>>password;

    user.setId(id);
    user.setName(name);
    user.setEmail(email);
    user.setPassword(password);
}

// Sign up
void signup (){
    cout<<"\n\t\033[1;33m  ❒❒❒ User Sign Up ❒❒❒\033[0m\n"; //yellow
    enterDetails(user);

    // Ensure the vector is up-to-date with the file
    fileToVector();

    //check if user already existed
    for (User &i: userRepository) {
        if(i.getId() == user.getId()) {
            cout<< "\033[31m!! User with ID " << user.getId() <<" already exists !!"<<endl;
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
    loginSuccessful(user.getName());
    askUserChoice();
}

//log in
void login (){
    cout<<"\n\t\033[1;33m  ❒❒❒ User Log In ❒❒❒\033[0m\n"; //yellow
    enterDetails(user);

    // Ensure the vector is up-to-date with the file
    fileToVector();

    //check if user id already exists
    bool userFound = false;
    for (User &i: userRepository) {
        if( i.getId() == user.getId()) {
            userFound = true;

            //check if name, email and password is also right
            bool verify;
            while (!verify) {
                if(i.getEmail() != user.getEmail() || i.getPassword() != user.getPassword() || i.getName() != user.getName()) {
                    cout << "\033[31m!! Incorrect E-mail, Password or Username !!\n\033[1mTry Again\033[0m"<<endl;
                    enterDetails(user);
                }
                else {
                    cout << "\033[33m~ User with ID " << i.getId() << " logged in successfully.\033[0m\n";
                    loginSuccessful (i.getName()); //safer to use i instead of user
                    verify = true;
                }
            }
            return; // Exit the function once user is logged in successfully
        }
    }
    //user id does not exist
    if (!userFound) {
        cout <<"\033[31m!! Incorrect ID or User not found !!\n\033[1mDo you want to SIGN UP instead? (Y/N) \033[0m";
        char yesno;
        cin >> yesno;
        if(yesno=='Y' || yesno=='y') {
            signup();
            return;
        }
        login();
        return;
    }
}

//// ASSUMING VECTOR IS CALLED CART
//// Function to clear the cart vector and cart.txt
//void logout() {
//    // Clear the vector
//    cart.clear();
//
//    // Clear the cart.txt file
//    ofstream cartFile("cart.txt", ios::trunc); // `ios::trunc` ensures the file is emptied
//    if (!cartFile) {
//        cerr << "\033[31mError: Unable to open cart.txt for clearing.\033[0m\n";
//        return;
//    }
//    cartFile.close();
//
//    cout << "\033[32mCart cleared successfully. You have been logged out.\033[0m\n";
//    menu();
//}