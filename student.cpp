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
void temp :: addStu(){
    cout<<"Enter Student Roll Number :: ";
    getline(cin,rollNum);
    cout<<"Enter Student Name :: ";
    getline(cin,name);
    cout<<"Enter Student Father's Name :: ";
    getline(cin,fName);
    cout<<"Enter Student Address :: ";
    getline(cin,address);

    file.open("stuData.txt", ios :: out | ios :: app);
    file<<rollNum<<"*";
    file<<name<<"*";
    file<<fName<<"*";
    file<<address<<endl;
    file.close();
}
void temp :: viewStu(){
    file.open("stuData.txt",ios::in);
    getline(file,rollNum,'*');
    getline(file,name,'*');
    getline(file,fName,'*');
    getline(file,address,'\n');
    while(!file.eof()){
        cout<<"\n";
        cout<<"Student Roll Number :: "<<rollNum;
        cout<<"Student Name :: "<<name;
        cout<<"Student Father Name :: "<<fName;
    }
}
