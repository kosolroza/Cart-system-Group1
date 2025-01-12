#include<iostream>
#include "../service/product_servic.hpp"
using namespace std;

class UI{
    private:
    static int insertOption(){
        int op;
        cout<<"Enter your option: ";
        cin>>op;
        return op;
    }
    static void option(){
        cout << "-------------------------------------------\n";
        cout << "   Welcome to Product Management System     \n";
        cout << "-------------------------------------------\n";
        cout << "1, Add Product\n";
        cout << "2, View Product\n";
        cout << "3, Update Product\n";
        cout << "4, Deleted Product \n";
        cout << "5, Exit\n";
        cout << "-------------------------------------------\n";  
    }
    public:
    static void home(){
        string filename = "data.txt";
        productRepositories = loadProductsFromFile(filename);
        while (true)
        {
            option();
            switch (insertOption()){
                case 1:{
                    int numProducts;
                    cout << "how many product do you want to add? ";
                    cin >> numProducts;
                    for(int i = 0 ; i < numProducts;i++){
                    ListProduct product;
                    cout << "||=============== Add Product " << i + 1 << " ===============||" <<endl;
                    product.addProduct();
                    addProductInfo(product, filename);
                    }       
                    break;
                }

                case 2:{
                     viewProduct(productRepositories);
                    break;
                }
                    
                case 3:{
                int id,newId,newQty;
                string newName;
                double newPrice;
                cout << "Enter ID of the product to update: ";
                cin >> id;

                cout << "Enter new ID: ";
                cin >> newId;
                cin.ignore(); 
                cout << "Enter new name: ";
                getline(cin, newName);
                cout << "Enter new quantity: ";
                cin >> newQty;
                cout << "Enter new price: ";
                cin >> newPrice;

                // Call the update function
                updateProductById(id, newId, newName, newQty, newPrice, filename);

                    break;
                }
                case 4:{
                    int id;
                    string filename = "data.txt";
                    cout<<"Enter product ID to deleted ";
                    cin>>id;
                    deleteProductById(id,filename);
                    break;
                }
                case 5:
                    exit(0);
                default:
                    cout << "Invalid option. Please try again.\n";
            }
        }
    }
};
