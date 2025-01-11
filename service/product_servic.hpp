#include <iostream>
#include <vector>
#include "../models/product.hpp"
#include "../repository/product_repo.hpp"

using namespace std;

vector<ListProduct> getAllProducts() {
    return productRepositories;
}

void addProductInfo(ListProduct product) {
        for (const auto& existingProduct : productRepositories) {
        if (existingProduct.getId() == product.getId()) {
            cout << "Error: Product with ID " << product.getId() << " already exists!" << endl;
            return; // Do not add the product if the ID is duplicated
        }
    }

    productRepositories.push_back(product);
    cout << "Product added successfully!" << endl;
}


bool deleteProductById(int id) {
    for (size_t i = 0; i < productRepositories.size(); ++i) {
        if (productRepositories[i].getId() == id) {
            productRepositories.erase(productRepositories.begin() + i);
            cout << "\nProduct with ID " << id << " deleted successfully." << endl;
            return true;
        }
    }
    cout << "Product with ID " << id << " not found." << endl;
    return false;
}

bool updateProductById(int id, int newId, const std::string& newName, int newQty, double newPrice) {
    for ( auto& product : productRepositories) {
        if (product.getId() == newId) {
            cout << "Error: Product with ID " << newId << " already exists!" << endl;
            return false; 
        }
    }

    for (auto& product : productRepositories) {
        if (product.getId() == id) {
            product.setId(newId);
            product.setName(newName);
            product.setQty(newQty);
            product.setPrice(newPrice);

            cout << "\nProduct with ID " << id << " updated successfully." << endl;
            return true;
        }
    }

    cout << "Product with ID " << id << " not found." << endl;
    return false;
}
