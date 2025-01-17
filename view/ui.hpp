//ui.hpp inside folder view
#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
// #include <unistd.h>
#include <conio.h>
#include <cstdlib>
#include <vector>
#include <string>
#include "../service/admin_service.hpp"
#include "../service/fileio.hpp"
#include "../service/cart_service.hpp"
#include "../service/user_service.hpp"

using namespace std;


//-----------LOADING BAR------------
//color codes
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

void showLoadingBar() {
    const int barWidth = 50;
    vector<string> colors = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};
    
    vector<vector<string>> letters = {
        {   // I
            "██╗",
            "██║",
            "██║",
            "██║",
            "██║",
            "╚═╝"
        },
        {   // S
            "███████╗",
            "██╔════╝",
            "███████╗",
            "╚════██║",
            "███████║",
            "╚══════╝"
        },
        {   // T
            "████████╗",
            "╚══██╔══╝",
            "   ██║   ",
            "   ██║   ",
            "   ██║   ",
            "   ╚═╝   "
        },
        {   // A
            " █████╗ ",
            "██╔══██╗",
            "███████║",
            "██╔══██║",
            "██║  ██║",
            "╚═╝  ╚═╝"
        },
        {   // D
            "██████╗ ",
            "██╔══██╗",
            "██║  ██║",
            "██║  ██║",
            "██████╔╝",
            "╚═════╝ "
        },
        {   // -
            "     ",
            "     ",
            "████╗",
            "╚═══╝",
            "     ",
            "     "
        },
        {   // G
            " ██████╗ ",
            "██╔════╝ ",
            "██║  ███╗",
            "██║   ██║",
            "╚██████╔╝",
            " ╚═════╝ "
        },
        {   // 1
            " ██╗",
            "███║",
            "╚██║",
            " ██║",
            " ██║",
            " ╚═╝"
        }
    };
    
    cout << "\033[2J\033[H";  // Clear screen
    cout << "   Loading...\n\n";
    
    const int totalHeight = letters[0].size();
    const int totalSteps = barWidth;
    
    for (int step = 0; step <= totalSteps; ++step) {
        cout << "\033[H\033[2J";  // Clear screen
        cout << "   Loading...\n\n";
        
        float fillPercentage = static_cast<float>(step) / totalSteps;
        
        for (int row = 0; row < totalHeight; ++row) {
            cout << "   ";
            for (size_t letterIndex = 0; letterIndex < letters.size(); ++letterIndex) {
                string letterLine = letters[letterIndex][row];
                int fillChars = static_cast<int>(letterLine.length() * fillPercentage);
                
                // Change the color to blue for "ISTAD-" and yellow for "G1", red for "-"
                string currentColor;
                if (letterIndex == 6 || letterIndex == 7) {  // "G" and "1" (index 6 and 7)
                    currentColor = YELLOW;  // Set color to yellow for G and 1
                } else if (letterIndex == 5) {  // "-" (index 5)
                    currentColor = RED;  // Set color to red for -
                } else {
                    currentColor = BLUE;  // Keep color blue for the rest
                }
                
                cout << currentColor;
                
                for (size_t i = 0; i < letterLine.length(); ++i) {
                    if (i < fillChars) {
                        cout << letterLine[i];
                    } else {
                        cout << " ";
                    }
                }
                cout << RESET << " ";
            }
            cout << endl;
        }
        
        cout << "\n   ";
        string currentColor = colors[step % colors.size()];
        cout << currentColor << "[";
        for (int i = 0; i < barWidth; ++i) {
            if (i < step) cout << "=";
            else cout << " ";
        }
        cout << "] " << (step * 100 / barWidth) << "%" << RESET;
        cout.flush();
        
        // Increase speed by reducing the delay
        #ifdef _WIN32
            Sleep(50);  // Faster than before (50ms)
        #else
            usleep(50000);  // Faster than before (50ms)
        #endif
    }
    
    // Add a 2-second pause at the end
    #ifdef _WIN32
        Sleep(2000);
    #else
        usleep(2000000);
    #endif
    
    cout << RESET << endl;
    cout << "\n\033[1;34m══════════════════════════════════════════════════════════════════════════\033[0m\n\n";
}
//--------------------------------

void menu() {
    system("cls");
    cout << "\033[1;36m"; // Cyan color
    cout << R"(
    ███████╗ ██╗  ██╗  ██████╗  ██████╗  ██████╗  ██╗ ███╗   ██╗  ██████╗
    ██╔════╝ ██║  ██║ ██╔═══██╗ ██╔══██╗ ██╔══██╗ ██║ ████╗  ██║ ██╔════╝
    ███████╗ ███████║ ██║   ██║ ██████╔╝ ██████╔╝ ██║ ██╔██╗ ██║ ██║  ███╗
    ╚════██║ ██╔══██║ ██║   ██║ ██╔═══╝  ██╔═══╝  ██║ ██║╚██╗██║ ██║   ██║
    ███████║ ██║  ██║ ╚██████╔╝ ██║      ██║      ██║ ██║ ╚████║ ╚██████╔╝
    ╚══════╝ ╚═╝  ╚═╝  ╚═════╝  ╚═╝      ╚═╝      ╚═╝ ╚═╝  ╚═══╝  ╚═════╝
                     INVENTORY MANAGEMENT SYSTEM 2024
    )" << "\033[0m\n";

    cout << "\033[1;34m"; // Blue color
    cout << "\t╔══════════════════════════ MAIN MENU ══════════════════════════╗\n";
    cout << "\t║                                                               ║\n";
    cout << "\t║  [1] ⚡️ Administrator Access                                  ║\n";
    cout << "\t║      └── Manage products, inventory, and system settings      ║\n";
    cout << "\t║                                                               ║\n";
    cout << "\t║  [2] 👤 User Portal                                           ║\n";
    cout << "\t║      └── Shop products and manage your cart                   ║\n";
    cout << "\t║                                                               ║\n";
    cout << "\t║  [3] 🚪 Exit Application                                      ║\n";
    cout << "\t║      └── Save and close the system                            ║\n";
    cout << "\t║                                                               ║\n";
    cout << "\t╚═══════════════════════════════════════════════════════════════╝\n";
    cout << "\t\033[1;32m┌────────────────────────────────────────────────────────────────────────┐\n";
    cout << "\t│             Select an option by entering the number (1-3)              |\n";
    cout << "\t└────────────────────────────────────────────────────────────────────────┘\033[0m\n\n";
    cout << "\033[1;35mEnter your choice ▶️ \033[0m";

    int choice;
    cin >> choice;
    cout << "\n\033[1;34m══════════════════════════════════════════════════════════════════════════\033[0m\n\n";

    switch (choice) {
        case 1:
            adminLogin();
            break;
        case 2:
            askUserChoice();
            break;
        case 3:
            cout << "\033[1;33m" << R"(
        ╔════════════════════════════════════════════════════╗
        ║                                                    ║
        ║  ✨ Thank you for using our management system! ✨  ║
        ║                                                    ║
        ╚════════════════════════════════════════════════════╝
            )" << "\033[0m\n";
            exit(0);
        default:
            cout << "\033[1;31m❌ Invalid choice! Please try again.\033[0m\n";
            menu();
    }
}

void askUserChoice() {
    system("cls");
    cout << "\033[1;35m" << R"(
██╗   ██╗███████╗███████╗██████╗   ██████╗  ██████╗ ██████╗ ████████╗ █████╗ ██╗
██║   ██║██╔════╝██╔════╝██╔══██╗  ██╔══██╗██╔═══██╗██╔══██╗╚══██╔══╝██╔══██╗██║
██║   ██║███████╗█████╗  ██████╔╝  ██████╔╝██║   ██║██████╔╝   ██║   ███████║██║
██║   ██║╚════██║██╔══╝  ██╔══██╗  ██╔═══╝ ██║   ██║██╔══██╗   ██║   ██╔══██║██║
╚██████╔╝███████║███████╗██║  ██║  ██║     ╚██████╔╝██║  ██║   ██║   ██║  ██║███████╗
 ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝  ╚═╝      ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝
    )" << "\033[0m\n";
        cout << "\033[1;34m";
    cout << "\t╔════════════════════════ USER OPTIONS ═════════════════════════╗\n";
    cout << "\t║                                                               ║\n";
    cout << "\t║   [1] 📝 Create New Account                                   ║\n";
    cout << "\t║       └── Sign up for a new shopping account                  ║\n";
    cout << "\t║                                                               ║\n";
    cout << "\t║   [2] 🔑 Access Your Account                                  ║\n";
    cout << "\t║       └── Login to your existing account                      ║\n";
    cout << "\t║                                                               ║\n";
    cout << "\t║   [3] 🔙 Return to Main Menu                                  ║\n";
    cout << "\t║       └── Go back to system main menu                         ║\n";
    cout << "\t║                                                               ║\n";
    cout << "\t╚═══════════════════════════════════════════════════════════════╝\n";
    cout << "\033[1;32m┌────────────────────────────────────────────────────────────────────────┐\n";
    cout << "│                   Please select your preferred option                  │\n";
    cout << "└────────────────────────────────────────────────────────────────────────┘\033[0m\n\n";
    cout << "\033[1;35mEnter your choice ▶️ \033[0m";

    int userChoice;
    cin >> userChoice;
    cout << "\n\033[1;34m══════════════════════════════════════════════════════════════════════════\033[0m\n\n";

    switch (userChoice) {
        case 1:
            signup();
            break;
        case 2:
            login();
            break;
        case 3:
            menu();
            break;
        default:
            cout << "\033[1;31m❌ Invalid input! Please try again.\033[0m\n";
            askUserChoice();
    }
}

// Function to mask password input
    string getPassword() {
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

void adminLogin() {
    system("cls");
    cout << "\033[1;36m" << R"(
 █████╗ ██████╗ ███╗   ███╗██╗███╗   ██╗  ██████╗  █████╗ ███╗   ██╗███████╗██╗
██╔══██╗██╔══██╗████╗ ████║██║████╗  ██║  ██╔══██╗██╔══██╗████╗  ██║██╔════╝██║
███████║██║  ██║██╔████╔██║██║██╔██╗ ██║  ██████╔╝███████║██╔██╗ ██║█████╗  ██║
██╔══██║██║  ██║██║╚██╔╝██║██║██║╚██╗██║  ██╔═══╝ ██╔══██║██║╚██╗██║██╔══╝  ██║
██║  ██║██████╔╝██║ ╚═╝ ██║██║██║ ╚████║  ██║     ██║  ██║██║ ╚████║███████╗███████╗
╚═╝  ╚═╝╚═════╝ ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝  ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═══╝╚══════╝╚══════╝
    )" << "\033[0m\n";

    cout << "\t\033[1;34m╔══════════════════════════ SECURE LOGIN ═══════════════════════╗\n";
    cout << "\t║                                                               ║\n";
    cout << "\t║                   🔐 Administrator Access 🔐                  ║\n";
    cout << "\t║                                                               ║\n";
    cout << "\t╚═══════════════════════════════════════════════════════════════╝\033[0m\n\n";

    string email, password;
    cout << "\033[1;33m✩ Enter Administrator Email:    \033[0m";
    cin >> email;
    cout << "\033[1;33m✩ Enter Administrator Password: \033[0m";
    password = getPassword();

    if (email == "admin@gmail.com" && password == "admin123") {
        cout << "\033[1;32m" << R"(
    ╔═══════════════════════════════════════════════════════════════╗
    ║                    ✅ Login Successful! ✅                    ║
    ╚═══════════════════════════════════════════════════════════════╝
        )" << "\033[0m\n";
        admin();
    } else {
        cout << "\033[1;31m" << R"(
    ╔═══════════════════════════════════════════════════════════════╗
    ║                 ❌ Invalid email or password! ❌              ║
    ╚═══════════════════════════════════════════════════════════════╝
        )" << "\033[0m\n";
        menu();
    }
}

void admin() {
    string filename = "data.txt";
    productRepositories = loadProductsFromFile(filename);
    int choice;
        system("cls");

        do {
        cout <<"\n\n\n";
        cout << "\t\033[1;36m╔══════════════════════ MANAGEMENT MENU ════════════════════════╗\n";
        cout << "\t║                                                               ║\n";
        cout << "\t║  [1] ➕ Add New Product                                       ║\n";
        cout << "\t║      └── Add new items to inventory                           ║\n";
        cout << "\t║                                                               ║\n";
        cout << "\t║  [2] 📋 View Product Inventory                                ║\n";
        cout << "\t║      └── Display all current products                         ║\n";
        cout << "\t║                                                               ║\n";
        cout << "\t║  [3] 📝 Update Product Details                                ║\n";
        cout << "\t║      └── Modify existing product information                  ║\n";
        cout << "\t║                                                               ║\n";
        cout << "\t║  [4] 🗑 Remove Product                                         ║\n";
        cout << "\t║      └── Delete items from inventory                          ║\n";
        cout << "\t║                                                               ║\n";
        cout << "\t║  [5] 🔙 Return to Main Menu                                   ║\n";
        cout << "\t║      └── Exit administrator panel                             ║\n";
        cout << "\t║                                                               ║\n";
        cout << "\t╚═══════════════════════════════════════════════════════════════╝\033[0m\n";

        cout << "\033[1;32m┌────────────────────────────────────────────────────────────────────────┐\n";
        cout << "│              Select an option to manage inventory (1-5)                │\n";
        cout << "└────────────────────────────────────────────────────────────────────────┘\033[0m\n\n";
        cout << "\033[1;35mEnter your choice ▶️ \033[0m";
        cin >> choice;
                    switch (choice) {case 1: {
                        
                cout << "\033[1;36m" << R"(
        ╔════════════════════════════════════════════════════════╗
        ║                    ADD NEW PRODUCTS                    ║
        ╚════════════════════════════════════════════════════════╝
                )" << "\033[0m\n";

                int numProducts;
                cout << "\033[1;33m📦 Enter the number of products to add: \033[0m";
                cin >> numProducts;

                for (int i = 0; i < numProducts; ++i) {
                    ListProduct product;
                    cout << "\033[1;34m\n═══════ Adding Product " << i + 1 << " ═══════\033[0m\n";
                    product.addProduct();
                    addProductInfo(product, filename);
                }
                break;
            }
            case 2: {
                cout << "\033[1;36m" << R"(
        ╔════════════════════════════════════════════════════════╗
        ║                   PRODUCT INVENTORY                    ║
        ╚════════════════════════════════════════════════════════╝
                )" << "\033[0m\n";

                vector<ListProduct> productList = loadProductsFromFile("data.txt");
                viewProduct(productList);
                break;
            }
            case 3: {
                cout << "\033[1;36m" << R"(
        ╔════════════════════════════════════════════════════════╗
        ║                UPDATE PRODUCT DETAILS                  ║
        ╚════════════════════════════════════════════════════════╝
                )" << "\033[0m\n";

                int id, newId, newQty;
                string newName;
                double newPrice;

                cout << "\033[1;33m📝 Enter Product ID to update: \033[0m";
                cin >> id;
                cout << "\033[1;33m📝 Enter new ID: \033[0m";
                cin >> newId;
                cin.ignore();
                cout << "\033[1;33m📝 Enter new name: \033[0m";
                getline(cin, newName);
                cout << "\033[1;33m📝 Enter new quantity: \033[0m";
                cin >> newQty;
                cout << "\033[1;33m📝 Enter new price: \033[0m";
                cin >> newPrice;

                updateProductById(id, newId, newName, newQty, newPrice, filename);
                break;
            }
            case 4: {
                cout << "\033[1;36m" << R"(
    ╔════════════════════════════════════════════════════════╗
    ║                     REMOVE PRODUCT                     ║
    ╚════════════════════════════════════════════════════════╝
                )" << "\033[0m\n";

                int id;
                cout << "\033[1;33m❌ Enter Product ID to delete: \033[0m";
                cin >> id;
                deleteProductById(id, filename);
                break;
            }
            case 5:
                menu();
                break;
            default:
                cout << "\033[1;31m❌ Invalid choice! Please try again.\033[0m\n";
        }
    } while (choice != 5);
}

void users() {
    int choice;
        system("cls");
    do {
        cout << "\n\033[1;34m══════════════════════════════════════════════════════════════════════════\033[0m\n\n";
        cout << "\033[1;36m"; // Cyan color
        cout << R"(
    ███████╗ ██╗  ██╗  ██████╗  ██████╗  ██████╗  ██╗ ███╗   ██╗  ██████╗
    ██╔════╝ ██║  ██║ ██╔═══██╗ ██╔══██╗ ██╔══██╗ ██║ ████╗  ██║ ██╔════╝
    ███████╗ ███████║ ██║   ██║ ██████╔╝ ██████╔╝ ██║ ██╔██╗ ██║ ██║  ███╗
    ╚════██║ ██╔══██║ ██║   ██║ ██╔═══╝  ██╔═══╝  ██║ ██║╚██╗██║ ██║   ██║
    ███████║ ██║  ██║ ╚██████╔╝ ██║      ██║      ██║ ██║ ╚████║ ╚██████╔╝
    ╚══════╝ ╚═╝  ╚═╝  ╚═════╝  ╚═╝      ╚═╝      ╚═╝ ╚═╝  ╚═══╝  ╚═════╝
    )" << "\033[0m\n";

        cout << "\t\033[1;34m╔════════════════════════ SHOPPING MENU ════════════════════════╗\n";
        cout << "\t║                                                               ║\n";
        cout << "\t║  [1] 📦 Browse Products                                       ║\n";
        cout << "\t║      └── View available items                                 ║\n";
        cout << "\t║                                                               ║\n";
        cout << "\t║  [2] 🛒 Add to Cart                                           ║\n";
        cout << "\t║      └── Select items for purchase                            ║\n";
        cout << "\t║                                                               ║\n";
        cout << "\t║  [3] 🔍 View Cart                                             ║\n";
        cout << "\t║      └── Review selected items                                ║\n";
        cout << "\t║                                                               ║\n";
        cout << "\t║  [4] ❌ Remove from Cart                                      ║\n";
        cout << "\t║      └── Update cart contents                                 ║\n";
        cout << "\t║                                                               ║\n";
        cout << "\t║  [5] 💳 Proceed to Checkout                                   ║\n";
        cout << "\t║      └── Complete your purchase                               ║\n";
        cout << "\t║                                                               ║\n";
        cout << "\t║  [6] 🚪 Logout                                                ║\n";
        cout << "\t║      └── Return to main menu                                  ║\n";
        cout << "\t║                                                               ║\n";
        cout << "\t╚═══════════════════════════════════════════════════════════════╝\033[0m\n";

        cout << "\033[1;32m>>> Select an option (1-6) to continue <<<\033[0m\n\n";
        cout << "\033[1;35mEnter your choice ▶️ \033[0m";
        cin >> choice;

                switch (choice) {
            case 1: {
                cout << "\033[1;36m" << R"(
        ╔════════════════════════════════════════════════════════╗
        ║                    PRODUCT CATALOG                     ║
        ╚════════════════════════════════════════════════════════╝
                )" << "\033[0m\n";

                vector<ListProduct> productList = loadProductsFromFile("data.txt");
                viewProduct(productList);
                break;
            }
            case 2: {
                cout << "\033[1;36m" << R"(
        ╔════════════════════════════════════════════════════════╗
        ║                      ADD TO CART                       ║
        ╚════════════════════════════════════════════════════════╝
                )" << "\033[0m\n";

                int productId, quantity;
                cout << "\033[1;33m🛍 Enter Product ID to add: \033[0m";
                cin >> productId;
                cout << "\033[1;33m📦 Enter quantity: \033[0m";
                cin >> quantity;
                addProductToCart(productId, quantity);
                break;
            }
            case 3: {
                cout << "\033[1;36m" << R"(
        ╔════════════════════════════════════════════════════════╗
        ║                     SHOPPING CART                      ║
        ╚════════════════════════════════════════════════════════╝
                )" << "\033[0m\n";

                viewCart();
                break;
            }
            case 4: {
                cout << "\033[1;36m" << R"(
        ╔════════════════════════════════════════════════════════╗
        ║                    REMOVE FROM CART                    ║
        ╚════════════════════════════════════════════════════════╝
                )" << "\033[0m\n";

                int productId, quantity;
                cout << "\033[1;33m🗑 Enter Product ID to remove: \033[0m";
                cin >> productId;
                cout << "\033[1;33m📦 Enter quantity to remove: \033[0m";
                cin >> quantity;
                removeProductFromCart(productId, quantity);
                break;
            }
            case 5: {
                cout << "\033[1;36m" << R"(
        ╔════════════════════════════════════════════════════════╗
        ║                       CHECKOUT                         ║
        ╚════════════════════════════════════════════════════════╝
                )" << "\033[0m\n";

                checkout();
                break;
            }
            case 6:
                cout << "\033[1;32m" << R"(
        ╔════════════════════════════════════════════════════════╗
        ║              ✨ Successfully Logged Out! ✨            ║
        ╚════════════════════════════════════════════════════════╝
                )" << "\033[0m\n";
                menu();
                return;
            default:
                cout << "\033[1;31m❌ Invalid choice! Please try again.\033[0m\n";
        }
    } while (choice != 6);
}

