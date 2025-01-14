#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "../models/product.hpp"
#include "../repository/product_repo.hpp"

using namespace std;

vector<ListProduct> productRepositories;  
//Udate by H
vector<pair<int, int>> cart; //Cart to hokld product ID and Quantity

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

// Add Product
void addProductInfo(ListProduct product, const string& filename) {
    // Load current products
    productRepositories = loadProductsFromFile(filename);

    // Check for duplicate product ID
    for (const auto& existingProduct : productRepositories) {
        if (existingProduct.getId() == product.getId()) {
            cout << "Error: Product with ID " << product.getId() << " already exists!" << endl;
            return;
        }
    }
    // Add product to list and update file
    productRepositories.push_back(product);
    updateFile(filename, productRepositories);
    cout << "Product added successfully and saved to file!" << endl;
}
// DeleteProduct
bool deleteProductById(int id, const string& filename) {
    productRepositories = loadProductsFromFile(filename);

    for (size_t i = 0; i < productRepositories.size(); ++i) {
        if (productRepositories[i].getId() == id) {
            productRepositories.erase(productRepositories.begin() + i);
            updateFile(filename, productRepositories);
            cout << "Product with ID " << id << " deleted successfully!" << endl;
            return true;
        }
    }
    cout << "Product with ID " << id << " not found!" << endl;
    return false;
}

// UpdateProduct
bool updateProductById(int id, int newId, const string& newName, int newQty, double newPrice, const string& filename) {
    productRepositories = loadProductsFromFile(filename);

    // Check if the new ID already exists
    for (const auto& existingProduct : productRepositories) {
        if (existingProduct.getId() == newId) {
            cout << "Error: Product with ID " << newId << " already exists!" << endl;
            return false;
        }
    }

    // Find and update the product
    for (auto& product : productRepositories) {
        if (product.getId() == id) {
            product.setId(newId);
            product.setName(newName);
            product.setQty(newQty);
            product.setPrice(newPrice);
            updateFile(filename, productRepositories);
            cout << "Product updated successfully!" << endl;
            return true;
        }
    }
    cout << "Product with ID " << id << " not found!" << endl;
    return false;
}

// Add Product to Cart (Product ID and Quantity)
void addProductToCart (int productId, int quantity){
    //Loat product from the file
    productRepositories = loadProductsFromFile("products.txt");
    for (const auto& product : productRepositories) {
        if (product.getId() == productId) {
            // Add product ID and Quantity to Cart
            cart.push_back({productID, quantity});
            cout << "Product " << product.getName() << "ID: " <<product.getId() << ") added to cart with quantity " << quantity <<endl;
            return;
        }
    }
    cout << "Product with ID " << productID << " not found! " << endl;
}
//View Cart Contents
void viewCart() {
    if (cart.empty()) {
        cout << "\nCart is empty.\n";
        return;
    }
    cout << "Your Cart:\n";
    cout << "Code\tName\tQuantity\tPrice\tTotal\n";

    //Load products from the file to access the name and price
    productRepositories = loadProductsFromFile ("products.txt");

    //Loop through the cart to get product details and calculate total
    for (const auto& item : cart) {
        int productId = item.first;
        int quantity = item.second;

        //Find the product by ID
        for (const auto& product : productRepositories) {
            if (product.getId() == productId) {
                double total = product.getPrice() * quantity;
                cout << product.getId() << "\t" << product.getName() << "\t" << product.getPrice() << "\t" << total << "\n";
            }
        }
    }
}