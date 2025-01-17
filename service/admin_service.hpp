//admin_service.hpp inside folder service
#include <iostream>
#include "../repository/product_repo.hpp"
#include "../service/fileio.hpp"

using namespace std;

void addProductInfo(ListProduct product, const string& filename) {
    // Load current products
    productRepositories = loadProductsFromFile(filename);

    // Check for duplicate product ID
    for (const auto& existingProduct : productRepositories) {
        if (existingProduct.getId() == product.getId()) {
            cout << "\033[1;31mError: Product with ID " << product.getId() << " already exists!\033[0m" << endl;
            return;
        }
    }
    // Add product to list and update file
    productRepositories.push_back(product);
    updateFile(filename, productRepositories);
    cout << "\033[1;33mProduct added successfully and saved to file!\033[0m" << endl;
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
void viewProduct(const std::string& filename){
    productRepositories = loadProductsFromFile(filename);
    cout << "\n\t\033[1;35m  ������ Products List ������\033[0m\n"; //purple
    cout << "\t\t\t\tID\tName\tQuantity\tPrice\n";
    for (const auto& product : productRepositories) {
        cout << "\t\t\t\t" << product.getId() << "\t" << product.getName() << "\t" << product.getQty() << "\t" << product.getPrice() << "\n";
    }
}