#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
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
    string getName() const { return this->name; }   
    int getQty() const { return this->qty; }
    double getPrice() const { return  this->price; }
    
    // Calculate discount rate based on total price
    double getDiscountRate() {
        if (qty > 10) {
            return 20.0;
        } else if (qty >= 5) {
            return 15.0;
        } else if (qty >= 3) {
            return 10.0;
        }
        return 0.0;
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
    string filename = "data.txt";
    cout << "-------------------------------------------------------------------------------------\n";
    cout << "| " << setw(12) << left << "ID"
         << setw(15) << left << "Name"      
         << setw(12) << right << "Quantity"
         << setw(16) << right << "Price"
         << setw(23) << right << "Discount (%)" 
         << setw(6) << right << " |\n";
    cout << "-------------------------------------------------------------------------------------\n";

    for (auto& product : productList) {
        double discount = product.getDiscountRate();
        cout << "| " << setw(12) << left << product.getId()
             << setw(15) << left << product.getName()
             << setw(12) << right << product.getQty()
             << setw(16) << right << fixed << setprecision(2) << product.getPrice()
             << setw(20) << right << fixed << setprecision(2) << discount << " %"
             << setw(7) << right << " |\n";
    }
    cout << "-------------------------------------------------------------------------------------\n";
}
