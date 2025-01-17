//repo.hpp inside folder repository
#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "../model/product.hpp"
#include "../model/user.hpp"

vector<User> userRepository;    //naiy
vector<ListProduct> productRepositories;
vector<pair<int, int>> cart; 

// Function declarations (no definitions here)
vector<ListProduct> loadProductsFromFile(const string& filename);
void updateFile(const string& filename, const vector<ListProduct>& productList);
void saveUsersToFile();
void fileToVector();