//product.hpp inside model folder
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
    string getName() const { return this->name; }   
    int getQty() const { return this->qty; }
    double getPrice() const { return  this->price; }
    
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
    cout << "---------------------------------------------------------------------\n";
    cout << "| " << setw(12) << left << "ID"
         << setw(18) << left << "Name"      
         << setw(13) << right << "Quantity"
         << setw(18) << right << "Price"
         << setw(7) << right << " |\n";
    cout << "---------------------------------------------------------------------\n";

    for (auto& product : productList) {
        cout << "| " << setw(12) << left << product.getId()
             << setw(15) << left << product.getName()
             << setw(13) << right << product.getQty()
             << setw(21) << right << fixed << setprecision(2) << product.getPrice()
             << setw(7) << right << " |\n";
    }
    cout << "---------------------------------------------------------------------\n";
}