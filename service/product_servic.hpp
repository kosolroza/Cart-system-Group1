#include <iostream>
#include <vector>
#include <../models/product.hpp>
#include <../repository/product_repo.hpp>

using namespace std;

vector<ListProduct> getAllProducts() {
    return productRepositories;
}

void addProductInfo(ListProduct product) {
    productRepositories.push_back(product);
    cout << "Product added successfully!" << endl;
}