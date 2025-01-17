//cart_service.hpp inside folder serivce
#include <iostream>
#include "../repository/product_repo.hpp"
#include "../service/fileio.hpp"

using namespace std;

void addProductToCart(int productId, int quantity) {
    // Load products from the file
    productRepositories = loadProductsFromFile("data.txt");

    for (auto& product : productRepositories) {
        if (product.getId() == productId) {
            // Check if the product is already in the cart
            int oldQtyInCart = 0;
            for (auto& item : cart) {
                if (item.first == productId) {
                    oldQtyInCart = item.second;
                    cart.erase(remove(cart.begin(), cart.end(), item), cart.end()); // Remove the old entry
                    break;
                }
            }
            // Calculate available stock
            int availableStock = product.getQty() - oldQtyInCart;

            if (quantity > availableStock) {
                cout << "Error: Not enough stock available for product ID " << productId
                     << ". Available quantity: " << availableStock << endl;
                return;
            }

            // Deduct the new quantity from the stock
            product.setQty(product.getQty() - quantity);

            cart.push_back(make_pair(productId, quantity));

            // Save the updated product stock and cart to files
            updateFile("data.txt", productRepositories);  
            saveCartToFile();                         

            cout << "Product " << product.getName() << " (ID: " << product.getId() 
                 << ") added to cart with quantity " << quantity << endl;
            return;
        }
    }

    cout << "Product with ID " << productId << " not found!" << endl;
}

void removeProductFromCart(int productId, int quantity) {
    // Iterate over the cart to find and remove the product
    for (auto& item : cart) {
        if (item.first == productId) {
            if (quantity > item.second) {
                cout << "Error: Not enough quantity in cart." << endl;
                return;
            }
            item.second -= quantity;
            if (item.second == 0) {
                cart.erase(remove(cart.begin(), cart.end(), item), cart.end());  
            }
            cout << "Product " << productId << " removed from cart." << endl;
            saveCartToFile(); 
            return;
        }
    }
    cout << "Product with ID " << productId << " not found in cart!" << endl;
}
void getTotalPrice(double &totalWithoutDiscount, double &totalWithDiscount) {
    totalWithoutDiscount = 0.0;
    totalWithDiscount = 0.0;
    productRepositories = loadProductsFromFile("data.txt");  // Load products

    for (const auto& item : cart) {
        int productId = item.first;
        int quantity = item.second;

        // Find the product by ID
        for (const auto& product : productRepositories) {
            if (product.getId() == productId) {
                double price = product.getPrice();
                double subtotal = price * quantity;
                double discountRate = 0.0;

                // Calculate discount based on quantity
                if (quantity > 10) {
                    discountRate = 20.0;
                } else if (quantity >= 5) {
                    discountRate = 15.0;
                } else if (quantity >= 3) {
                    discountRate = 10.0;
                }
                double discountAmount = subtotal * (discountRate / 100.0);
                double finalPrice = subtotal - discountAmount;

                totalWithoutDiscount += subtotal;
                totalWithDiscount += finalPrice;
                break;
            }
        }
    }
}
void checkout() {
    double totalWithoutDiscount, totalWithDiscount;

    // Get the total price of items in the cart
    getTotalPrice(totalWithoutDiscount, totalWithDiscount);

    cout << "Total Price without Discount: $" << fixed << setprecision(2) << totalWithoutDiscount << endl;
    cout << "Total Price with Discount: $" << fixed << setprecision(2) << totalWithDiscount << endl;

    cout << "Do you want to proceed with the checkout or cancel? (P/C) ";
    char choice;
    cin >> choice;

    if (choice == 'P' || choice == 'p') {
        double userMoney = 0.0;

        while (true) {
            cout << "\n[+] Enter the amount of money: $ ";
            string input;
            cin >> input;

            // Validate user input for payment
            bool isValidInput = true;
            for (char c : input) {
                if (!isdigit(c) && c != '.') {
                    isValidInput = false;
                    break;
                }
            }

            if (!isValidInput) {
                cout << "[-] Invalid input. Please try again.\n";
                continue;
            }

            userMoney = stod(input);

            if (userMoney >= totalWithDiscount) {
                double change = userMoney - totalWithDiscount;
                cout << "[+] Payment successful! Your change: $" << fixed << setprecision(2) << change << endl;

                // Cart cleared after successful payment
                cart.clear();
                saveCartToFile();

                cout << "\n~ Thank you for your purchase. Your order has been placed.\n";
                return;
            } else {
                cout << "[-] Insufficient funds. Please enter at least $" << fixed << setprecision(2)
                     << totalWithDiscount << ".\n";
            }
        }
    } else if (choice == 'C' || choice == 'c') {
        // Restore quantities from the cart back to the stock
        for (const auto& item : cart) {
            int productId = item.first;
            int qtyCart = item.second;

            for (auto& product : productRepositories) {
                if (product.getId() == productId) {
                    product.setQty(product.getQty() + qtyCart);  // Restore stock
                    break;
                }
            }
        }

        // Save the updated stock to file
        updateFile("data.txt", productRepositories);

        // Clear the cart
        cart.clear();
        saveCartToFile();

        cout << "\n~ Checkout cancelled. Stock has been restored and your cart has been cleared.\n";
    } else {
        cout << "[-] Invalid choice. Please try again.\n";
    }
}
//View Cart Contents
void viewCart() {
    if (cart.empty()) {
        cout << "\nCart is empty.\n";
        return;
    }
    
    cout << "Your Cart:\n";
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    cout << "| " << setw(12) << left << "ID"
         << setw(18) << left << "Name"
         << setw(8) << right << "Quantity"
         << setw(15) << right << "Price"
         << setw(18) << right << "Total"
         << setw(17) << right << "Discount (%)"
         << setw(15) << right << "Final Price"
         << setw(3) << right << " |\n";
    cout << "-----------------------------------------------------------------------------------------------------------\n";

    // Load products from the file to access the name and price
    productRepositories = loadProductsFromFile("data.txt");

    // Loop through the cart to get product details and calculate total
    for (auto& item : cart) {
        int productId = item.first;
        int quantity = item.second;

        // Find the product by ID
        for (const auto& product : productRepositories) {
            if (product.getId() == productId) {
                double total = product.getPrice() * quantity;
                double discountRate = 0.0;

                // Calculate discount based on quantity
                if (quantity > 10) {
                    discountRate = 20.0;
                } else if (quantity >= 5) {
                    discountRate = 15.0;
                } else if (quantity >= 3) {
                    discountRate = 10.0;
                }

                double discountAmount = total * (discountRate / 100.0);
                double finalPrice = total - discountAmount;

                // Display product details in a table format with '|' separator
                cout << "| " << setw(12) << left << product.getId()
                     << setw(18) << left << product.getName()
                     << setw(8) << right << quantity
                     << setw(15) << right << fixed << setprecision(2) << product.getPrice()
                     << setw(18) << right << fixed << setprecision(2) << total
                     << setw(15) << right << fixed << setprecision(2) << discountRate << " %"
                     << setw(15) << right << fixed << setprecision(2) << finalPrice
                     << setw(3) << right << " |\n";
            }
        }
    }
    cout << "-----------------------------------------------------------------------------------------------------------\n";
}
