#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class temp {
    string userName, Email, password;
    fstream file;
public:
    void login();
    void signUP();
    void forgot();
} obj;

int main() {
    char choice;
    cout << "\n1- Login";
    cout << "\n2- Sign-Up";
    cout << "\n3- Forgot Password";
    cout << "\n4- Exit";
    cout << "\nEnter Your Choice :: ";
    cin >> choice;
    cin.ignore(); 

    switch (choice) {
    case '1':
        obj.login();
        break;
    case '2':
        obj.signUP();
        break;
    case '3':
        obj.forgot();
        break;
    case '4':
        return 0;
    default:
        cout << "Invalid Selection...!";
    }

    return 0;
}

void temp::signUP() {
    cout << "\nEnter Your User Name: ";
    getline(cin, userName);
    cout << "Enter Your Email Address: ";
    getline(cin, Email);
    cout << "Enter Your Password: ";
    getline(cin, password);

    file.open("loginData.txt", ios::out | ios::app);
    file << userName << "*" << Email << "*" << password << "\n";
    file.close();
    cout << "\nAccount Created Successfully!\n";
}

void temp::login() {
    string searchName, searchPass;
    bool found = false;

    cout << "-------------LOGIN---------------" << endl;
    cout << "Enter Your User Name: ";
    getline(cin, searchName);
    cout << "Enter Your Password: ";
    getline(cin, searchPass);

    file.open("loginData.txt", ios::in);
    while (getline(file, userName, '*') &&
           getline(file, Email, '*') &&
           getline(file, password)) {
        if (userName == searchName && password == searchPass) {
            cout << "\nAccount Login Successful!";
            cout << "\nUsername: " << userName;
            cout << "\nEmail: " << Email << "\n";
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "\nLogin Failed: Incorrect username or password.\n";
    }
}

void temp::forgot() {
    string inputName, inputEmail;
    bool found = false;

    cout << "\nEnter Your UserName: ";
    getline(cin, inputName);
    cout << "Enter Your Email Address: ";
    getline(cin, inputEmail);

    file.open("loginData.txt", ios::in);
    while (getline(file, userName, '*') &&
           getline(file, Email, '*') &&
           getline(file, password)) {
        if (userName == inputName && Email == inputEmail) {
            cout << "\nAccount Found!";
            cout << "\nYour Password is: " << password << "\n";
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "\nNo matching account found.\n";
    }
}
