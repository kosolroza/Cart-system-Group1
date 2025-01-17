//fileio.hpp inside folder serivce
#pragma once
#ifndef FILEIO_HPP
#define FILEIO_HPP
// Your header content here
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "../repository/product_repo.hpp"

extern User user;

using namespace std;
#endif // FILEIO_HPP

// ====================================== Admin =================================================================
    vector<ListProduct> loadProductsFromFile(const string& filename) {
        ifstream ifs(filename);
        if (!ifs.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            return {};
        }

    vector<ListProduct> loadedProducts;
        string line;
        while (getline(ifs, line)) {
            stringstream ss(line);
            int id, qty;
            double price;
            string name;

            if (getline(ss, name, ',') && ss >> id && ss.ignore() && ss >> qty && ss.ignore() && ss >> price) {
                ListProduct product(id, name, qty, price);
                loadedProducts.push_back(product);
            } else {
                cout << "Error: Failed to parse line: " << line << endl;
            }
    }
    ifs.close();
    return loadedProducts;
}

void updateFile(const string& filename, const vector<ListProduct>& productList) {
        ofstream ofs(filename, ios::trunc);  // Overwrite file
        if (!ofs.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }
        
        for (const auto& product : productList) {
            ofs << product.getName() << "," << product.getId() << "," << product.getQty() << "," << product.getPrice() << "\n";
        }
        ofs.close();
        cout << "File has been updated!" << endl;
}

// ============================== loginout =============================

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
// ===================================== Cart =================================================================

// Function to save cart to file (cart.txt)
void saveCartToFile() {
    ofstream file("cart.txt");
    if (file.is_open()) {
        for (const auto& item : cart) {
            file << item.first << " " << item.second << "\n";
        }
        file.close();
    }
}

// Function to load cart from file (cart.txt)
void loadCartFromFile() {
    ifstream file("cart.txt");
    if (file.is_open()) {
        cart.clear();
        int code, quantity;
        while (file >> code >> quantity) {
            cart.emplace_back(code, quantity);
        }
        file.close();
    }
}





