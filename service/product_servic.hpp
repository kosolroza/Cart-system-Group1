#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "../models/product.hpp"
#include "../repository/product_repo.hpp"

using namespace std;

vector<ListProduct> productRepositories;  

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
