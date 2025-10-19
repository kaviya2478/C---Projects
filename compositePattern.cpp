#include <iostream>
#include <string>
#include <vector>
using namespace std;

class CarItem{
    public:
       virtual double getPrice() const = 0;
       virtual void display(const string& indent) const =0;
       virtual ~CarItem() {}   
};

class Product : public CarItem{
    private:
        string name;
        double price;
    public:
        Product(const string& name, double price) : name(name), price(price) {}
        
        double getPrice() const override{
            return price;
        }

        void display(const string& indent) const override{
            cout << indent << "Product: " << name << ", Price: Rs." << price << endl;
        }
};

class ProductBundle : public CarItem{
    private:
        string bundleName;
        vector<CarItem*> items;
    public:
        ProductBundle(const string& bundleName) : bundleName(bundleName) {}

        void addItem(CarItem* item){
            items.push_back(item);
        }

        double getPrice() const override{
            double total = 0.0;
            for(const auto& item : items){
                total += item->getPrice();
            }
            return total;
        }

        void display(const string& indent) const override{
            cout << indent << "Product Bundle: " << bundleName << ", Total Price: Rs." << getPrice() << endl;
            for(const auto& item : items){
                item->display(indent + "  ");
            }
        }

        ~ProductBundle(){
            for(auto& item : items){
                delete item;
            }
        }
};

int main(){
    CarItem* book = new Product("C++ Programming Book", 500.0);
    CarItem* laptop = new Product("Laptop", 45000.0);
    CarItem* smartphone = new Product("Smartphone", 20000.0);
    ProductBundle* electronicsBundle = new ProductBundle("Electronics Bundle");
    electronicsBundle->addItem(laptop);
    electronicsBundle->addItem(smartphone);
    ProductBundle* holidayBundle = new ProductBundle("Holiday Bundle");
    holidayBundle->addItem(book);
    holidayBundle->addItem(electronicsBundle);
    holidayBundle->display("");
    cout << "Total Price of Holiday Bundle: Rs." << holidayBundle->getPrice() << endl;


    vector<CarItem*> cart;
    cart.push_back(book);
    cart.push_back(electronicsBundle);
    cart.push_back(holidayBundle);

    cout<<"Your Amazon Cart:"<<endl;
    double total =0;
    for(const auto& item : cart){
        item->display("  ");
        total += item->getPrice();
    }

    cout<<"Total Cart Value: Rs."<<total<<endl;

    for(auto& item : cart){
        delete item;
    }
    return 0;
}

