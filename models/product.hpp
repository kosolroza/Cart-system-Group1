#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

#pragma once //
using namespace std;

class ListProduct{
    private:
    int id;
    string name;
    int qty;
    double price;

    public:
    ListProduct(int id, string name, int qty, double price){
        this->id = id;
        this->name = name;
        this->qty = qty;
        this->price = price;
    }
    ListProduct() : id(0), name (""), qty(0), price (0.0) {}
    int getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return qty; }
    double getPrice() const { return price; }
    
};
