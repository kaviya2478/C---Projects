#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class temp {
    string id, name, author, search;
    fstream file;
public:
    void addBook();
    void showAll();
    void extractBook();
} obj;

int main() {
    char choice;
    cout << "----------------------------\n";
    cout << "1 - Show All Books\n";
    cout << "2 - Extract Book\n";
    cout << "3 - Add Books (ADMIN)\n";
    cout << "4 - Exit\n";
    cout << "----------------------------\n";
    cout << "Enter Your Choice :: ";
    cin >> choice;
    cin.ignore(); 

    switch (choice) {
    case '1':
        obj.showAll();
        break;
    case '2':
        obj.extractBook();
        break;
    case '3':
        obj.addBook();
        break;
    case '4':
        return 0;
    default:
        cout << "Invalid Selection...!" << endl;
    }

    return 0;
}

void temp::addBook() {
    cout << "\nEnter Book ID :: ";
    getline(cin, id);
    cout << "Enter Book Name :: ";
    getline(cin, name);
    cout << "Enter Book's Author Name :: ";
    getline(cin, author);

    file.open("bookData.txt", ios::out | ios::app);
    file << id << "*" << name << "*" << author << "\n";
    file.close();

    cout << "\nBook Added Successfully!\n";
}

void temp::showAll() {
    file.open("bookData.txt", ios::in);
    if (!file) {
        cout << "File could not be opened.\n";
        return;
    }

    bool hasData = false;
    cout << "\n\n\t\t Book Id \t\t Book Name \t\t Author's Name\n";

    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, author)) {
        cout << "\t\t" << id << "\t\t" << name << "\t\t" << author << "\n";
        hasData = true;
    }

    if (!hasData) {
        cout << "No books available.\n";
    }

    file.close();
}

void temp::extractBook() {
    cout << "Enter Book Id to Extract :: ";
    getline(cin, search);

    file.open("bookData.txt", ios::in);
    if (!file) {
        cout << "File could not be opened.\n";
        return;
    }

    bool found = false;

    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, author)) {
        if (search == id) {
            cout << "\nBook Found:\n";
            cout << "\t\t Book Id \t\t Book Name \t\t Author's Name\n";
            cout << "\t\t" << id << "\t\t" << name << "\t\t" << author << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nBook with ID '" << search << "' not found.\n";
    }

    file.close();
}
