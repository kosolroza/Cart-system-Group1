#include <string>
#include <iostream>
#pragma once
using namespace std;

class User{
private:
    int id; //because these are private, you need to use setter and getter
    string name, email, password;
public:
    void setId(const int id){
        this->id = id;
    }
    int getId(){
        return this->id;
    }
    //
    void setName(const string & name){
        this->name = name;
    }
    string getName(){
        return this->name;
    }
    //
    void setEmail(const string & email){
        this->email = email;
    }
    string getEmail(){
        return this->email;
    }
    //
    void setPassword(const string & password){
        this->password = password;
    }
    string getPassword(){
        return this->password;
    }
    //
    void getUserInfo() {
        cout<<"► ID: "<<id<<endl;
        cout<<"► Name: "<<name<<endl;
        cout<<"► Email: "<<this->email<<endl;
        cout<<"► Password: "<<this->password<<endl;
    }

    //
};