#include <string>
#include <iomanip>
#include <iostream>
#include <vector>

#pragma once
using namespace std;

class ListProduct {
private:
    int id;
    string name;
    int qty;
    double price;

public:

    ListProduct() : id(0), name(""), qty(0), price(0.0) {}
    // Constructor
    ListProduct(int id, string name, int qty, double price) {
        this->id = id;
        this->name = name;
        this->qty = qty;
        this->price = price;
    }
    void setId(int id) { this->id = id; }     
    void setName(string name) { this->name = name; }
    void setQty(int qty) { this->qty = qty; }
    void setPrice(double price) { this->price = price; }

    int getId() const { return this->id; }
    string getName() { return this->name; }   
    int getQty() { return this->qty; }
    double getPrice() { return  this->price; }
    
    // Calculate total price
    double getTotalPrice() { return qty * price; }

    // Calculate discount rate based on total price
    double getDiscountRate() {
        double grandTotal = getTotalPrice();
        if (grandTotal > 10) {
            return 20.0;
        } else if (grandTotal >= 5) {
            return 15.0;
        } else if (grandTotal >= 3) {
            return 10.0;
        }
        return 0.0;
    }

    double getFinalPayment() {
        double grandTotal = getTotalPrice();
        double discountRate = getDiscountRate();
        double discount = grandTotal * (discountRate / 100);
        return grandTotal - discount;
    }
    void addProduct() {
        cout << "[+] Product ID: "; cin >> id;
        cin.ignore();
        cout << "[+] Product Name: "; getline(cin, name);
        cout << "[+] Product Quantity: "; cin >> qty;
        cout << "[+] Product Price: "; cin >> price;
    }
};

void viewProduct(vector<ListProduct>& productList){
    cout << "------------------------------------------------------------------------------------------\n";
    cout << "| " << setw(12) << left << "ID"
         << setw(15) << left << "Name"      
         << setw(12) << right << "Quantity"
         << setw(12) << right << "Total"
         << setw(16) << right << "Discount (%)" 
         << setw(19) << right << "Total Price" << " |\n";
    cout << "------------------------------------------------------------------------------------------\n";

    double totalFinalPrice = 0.0;

    for (auto& product : productList) {
        double totalPrice = product.getTotalPrice();
        double discountRate = product.getDiscountRate();
        double finalPayment = product.getFinalPayment();
        totalFinalPrice += finalPayment;

        cout << "| " << setw(12) << left << product.getId()
             << setw(15) << left << product.getName()
             << setw(12) << right << product.getQty()
             << setw(12) << right << fixed << setprecision(2) << totalPrice
             << setw(14) << right << fixed << setprecision(2) << discountRate << " %"
             << setw(19) << right << fixed << setprecision(2) << finalPayment << " |\n";
    }

    cout << "------------------------------------------------------------------------------------------\n";
    cout << "\n[+] Total price for all products: $ " << fixed << setprecision(2) << totalFinalPrice << endl;
}